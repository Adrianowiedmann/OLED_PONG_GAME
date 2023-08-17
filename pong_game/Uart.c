// uart.c

#include <msp430.h>
#include "Defines.h"
#include "Uart.h"

// Imprimir um vetor de pontos
void ser_vet(char *vx, char *vy){
    char i;
    for (i=0; i<10; i++){
        ser_char ('(');
        ser_dec8(vx[i]);
        ser_char (',');
        ser_dec8(vy[i]);
        ser_str(") ");
    }
    ser_crlf(1);
}

// Imprimir Hexa 8 bits
void ser_hex8(char x){
    char aux;
    aux=(x>>4)&0xF;
    if (aux>9)  aux += 7;
    ser_char(0x30 + aux);

    aux=x&0xF;
    if (aux>9)  aux += 7;
    ser_char(0x30 + aux);
}

// Imprimir decimal 8 bits ( 0, 1, ..., 255)
void ser_dec8(char x){
    char aux;

    // centena
    aux=x/100;
    ser_char(0x30 + aux);

    // dezena
    x=x-aux*100;
    aux=x/10;
    ser_char(0x30 + aux);

    // unidade
    x=x-aux*10;
    ser_char(0x30 + x);
}

// Imprimir uma string na serial
void ser_str(char *pt){
    int i=0;
    while (pt[i] != 0){
        ser_char(pt[i]);
        i++;
    }
}

// espaços em branco
void ser_spc(char x){
    char i=0;
    while (i<x){
        ser_char(' ');
        i++;
    }
}

// CR LF
void ser_crlf(char x){
    char i=0;
    while (i<x){
        ser_char(CR);
        ser_char(LF);
        i++;
    }
}

// Imprime x na porta serial
void ser_char(char x){
    while ( (UCA1IFG & UCTXIFG) == 0 );  //Esperar Tx
    UCA1TXBUF=x;
}

// Prog 115.200 bps com SMCLK=20 MHz (115.200 é o max do CCS)
void uart_config(void){
    UCA1CTL1 = UCSWRST;  //RST=1
    UCA1CTL0 = 0;
    UCA1BRW = 173;
    UCA1MCTL = UCBRS_5;

    P4DIR |=  BIT4;         //P4.4 saída
    P4DIR &= ~BIT5;         //P4.5 entrada
    P4SEL |= BIT5 | BIT4;   //Selecionar UART

    UCA1CTL1 = UCSSEL_2;     //RST=0 e SMCLK

}



