// oled.c

#include <msp430.h>
#include <Defines.h>
#include <Oled.h>



// Usar DMA2 para preencher buffer do Oled com zeros
// Modo BLOCO: Demora 2xMCLK*520 = 49, microseg
void oled_buf_apaga_dma(void){
    int aux=0;
    while (dma2_flag==TRUE);    //Refresh do oled, esperar
    DMACTL1 = DMA2TSEL_0;       //Trigger = DMAREQ (software)
    DMA2CTL = DMAEN        |    //Habilitar DMA2
              DMADT_1      |    //Bloco sem repetição
              DMASRCINCR_0 |    //Adr fonte fixo
              DMADSTINCR_3;     //Adr destino incrementa
    DMA2SA = &aux;              //aux = 0
    DMA2DA = oled_buf;          //Buffer Oled
    DMA2SZ = 520;               //Buffer Oled 1.024 + 16 bytes = 520 words
    DMA2CTL |= DMAREQ;          //Habilitar DMA2
    while ((DMA2CTL&DMAIFG)==0);
    for (aux=0; aux<8; aux++)
        oled_buf [aux] [0] = 0x40;    //Restaurar 0x40 no início de cada linha
    oled_flag=TRUE;             //Avisar para fazer refresh
}

void oled_buf_apaga(void){
    char i,j;
    for (i=0; i<8; i++){
        oled_buf[i][0]=0x40;        //Indicar que são dados
        for (j=1; j<130; j++){
            oled_buf[i][j]=0;
        }
    }
    oled_flag=TRUE;             //Avisar para fazer refresh
}



////////////////////////////////////////////////////////////////////////




void oled_retg(char x1, char y1, char x2, char y2, char oque){
    ;
}

void oled_linha(char x1, char y1, char x2, char y2, char oque){
    int alfa;
    char x,y,aux;

    // Só um ponto
    if (x1==x2 && y1==y2)   oled_pix(x1,y1,oque);

    // Linha horizontal
    else if (y1 == y2){
        for (x=x1; x<x2+1; x++){
            oled_pix(x,y1,oque);
        }
    }

    // Linha vertical
    else if (x1 == x2){
        for (y=y1; y<y2+1; y++){
            oled_pix(x1,y,oque);
        }
    }

    else{
        // é preciso x1 < x2
        if (x1>x2){
            aux=x1;  x1=x2;  x2=aux;
            aux=y1;  y1=y2;  y2=aux;
        }
        alfa=1000*((float)(y2-y1)/(float)(x2-x1));
        for (x=x1; x<x2+1; x++){
            y = y1 + ((x-x1)*alfa)/1000;
            oled_pix(x,y,oque);
        }
    }
}

void oled_pix(char x, char y, char oque){
    char lin, col, mask, aux;
    col = x+1;                  //Pular o primeiro byte que é o 0x40
    if (col>129)    col=129;    //Limitar em 129
    lin = (y>>3)&0x7;   //Limitar em 7
    mask = 1<<(y&7);    //Posição do bit

    aux = oled_buf[lin][col];
    if (oque == PX_ON)  aux |=  mask;
    else                aux &= ~mask;
    oled_buf[lin][col]=aux;
    oled_flag=TRUE;             //Avisar para fazer refresh
}

// Gerar um padrao para teste
void oled_padrao_2(void){
    char i,j,pad;
    pad=0x80;
    for (i=0; i<8; i++){
        for (j=0; j<128; j++){
            oled_buf[i][j]= pad>>(j&7);
            if (pad == 0)    pad=0x80;
        }
    }
}


// Gerar um padrao para teste
void oled_padrao_1(void){
    char i,j,pad;
    pad=1;
    for (i=0; i<8; i++){
        for (j=0; j<128; j++){
            oled_buf[i][j]= pad<<(j&7);
            if (pad == 0x80)    pad=1;
        }
    }
}


// Enviar todo o buffer
void oled_buf_vai(void){
    char i;
    for (i=0; i<8; i++){
        oled_pag[3]=0xB0+i; //Selecionar a página
        oled_wr_cmdo(oled_pag,4);
        oled_wr_cmdo(&oled_buf[i][0],129);

    }
}


// Envia o vetor, como está
void oled_wr_cmdo(char *vet, int qtd){
    int i=0;
    UCB1I2CSA = OLED_ADR;        //Endereço Escravo
    UCB1CTL1 |= UCTR    |       //Mestre TX
                UCTXSTT;        //Gerar START
    while ( (UCB1IFG & UCTXIFG) == 0)   ;          //Esperar TXIFG=1
    UCB1TXBUF = vet[i++];                              //Escrever dado
    while ( (UCB1CTL1 & UCTXSTT) == UCTXSTT)   ;   //Esperar STT=0
    if ( (UCB1IFG & UCNACKIFG) == UCNACKIFG)       //NACK?
        while(1);                          //Escravo gerou NACK
    while(i<qtd){
        while ( (UCB1IFG & UCTXIFG) == 0)   ;          //Esperar TXIFG=1
        UCB1TXBUF = vet[i];                              //Escrever dado
        i++;
    }
    while ( (UCB1IFG & UCTXIFG) == 0)   ;          //Esperar TXIFG=1
    UCB1CTL1 |= UCTXSTP;                        //Gerar STOP
    while ( (UCB1CTL1 & UCTXSTP) == UCTXSTP)   ;   //Esperar STOP
}

// Antes envia um 0x40 e depois todo o vetor
void oled_wr_dado(char *vet, int qtd){
    int i=0;
    UCB1I2CSA = OLED_ADR;        //Endereço Escravo
    UCB1CTL1 |= UCTR    |       //Mestre TX
                UCTXSTT;        //Gerar START
    while ( (UCB1IFG & UCTXIFG) == 0)   ;          //Esperar TXIFG=1
    UCB1TXBUF = 0x40;                              //Vai enviar dado
    while ( (UCB1CTL1 & UCTXSTT) == UCTXSTT)   ;   //Esperar STT=0
    if ( (UCB1IFG & UCNACKIFG) == UCNACKIFG)       //NACK?
        while(1);                          //Escravo gerou NACK
    while(i<qtd){
        while ( (UCB1IFG & UCTXIFG) == 0)   ;          //Esperar TXIFG=1
        UCB1TXBUF = vet[i];                              //Escrever dado
        i++;
    }
    while ( (UCB1IFG & UCTXIFG) == 0)   ;          //Esperar TXIFG=1
    UCB1CTL1 |= UCTXSTP;                        //Gerar STOP
    while ( (UCB1CTL1 & UCTXSTP) == UCTXSTP)   ;   //Esperar STOP
}



// Preparar DMA2 para refresh do OLED
void oled_dma2_prep(void){
    DMACTL1 = DMA2TSEL_23;      //Trigger = USCI_B1 (I2C)
    DMA2CTL = //DMAEN        |    //Habilitar DMA2
              DMAIE        |    //Hab interrupção
              DMADT_0      |    //Simples
              DMASRCBYTE   |    //source em bytes
              DMADSTBYTE   |    //destino em bytes
              DMASRCINCR_3 |    //Adr fonte incrementa
              DMADSTINCR_0;     //Adr destino fixo
    DMA2SA = &oled_pag[0];      //vetor
    DMA2DA = USCIB1_TXBUF_ADDR; //USCI_B1_TXFUB
    DMA2SZ = 4;                 //
    UCB1IFG = 0;                //Apagar TXIFG
}

// Interrupção do DMA2
// Refresh do OLED
// oled_fase = 0, 2, 4, 6, 8, 10, 12, 14 => enviar cmdo para nova linha
// oled_fase = 1, 3, 5, 7, 9, 11, 13, 15 => enviar linha de dados
#pragma vector = 50
__interrupt void isr_dma2(void){
    DMAIV;      //Apagar DMA2IFG

    if (oled_fase != 0){
        while ( (UCB1IFG & UCTXIFG) == 0);          //Esperar TXIFG=1
        usci_b1_stop();
    }

    if (oled_fase != 16){
        if ((oled_fase&1)==0){
            //ser_str("\nfase=");     ser_dec8(oled_fase);        ser_char(' ');
            oled_pag[3] = 0xB0 | (oled_fase>>1);
            DMA2SA = &oled_pag[0];
            DMA2DA = USCIB1_TXBUF_ADDR;
            DMA2SZ = 4;
        }
        else{
            //ser_str("\nfase=");     ser_dec8(oled_fase);        ser_char(' ');
            DMA2SA = &oled_buf[oled_fase>>1][0];
            DMA2DA = USCIB1_TXBUF_ADDR;
            DMA2SZ = 129;
        }
        UCB1IFG=0;
        DMA2CTL |= DMAEN;       //Habilitar DMA2
        usci_b1_start();    //Disparar nova transferência I2C
        oled_fase++;
    }
    else{
        dma2_flag=FALSE;
    }
}

// Iniciar uma transferência por DMA2
// Após a condição de START, vem TXIFG=1 e DMA entra em operação
void usci_b1_start(void){
    UCB1I2CSA = OLED_ADR;        //Endereço Escravo
    UCB1CTL1 |= UCTR    |       //Mestre TX
                UCTXSTT;        //Gerar START
}

// Esperar condição de STOP, e finalizar um ciclo de refresh do DMA2
// Acho que não precisa, vamos sempre usar o START repetido
void usci_b1_stop(void){
    UCB1CTL1 |= UCTXSTP;                        //Gerar STOP
    while ( (UCB1CTL1 & UCTXSTP) == UCTXSTP)   ;   //Esperar STOP

}
