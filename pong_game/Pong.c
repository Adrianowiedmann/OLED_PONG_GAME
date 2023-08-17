//202014824 - Adriano Ulrich do Prado Wiedmann

// P4.1 = SDA e P4.2 = SCL


//Joystick - Sw  = P6.5
//           VRy = P6.2
//           VRx = P6.1
//
//Joystick - Sw  = P6.6
//           VRy = P6.4
//           VRx = P6.3
//

#include <msp430.h> 
#include "Defines.h"
#include "Globais.h"
#include "Gpio.h"
#include "I2c.h"
#include "Oled.h"
#include "Oled_Letras.h"
#include "Uart.h"
#include "Timer.h"
#include "Aleat.h"
#include "Joystick.h"

//void config_adc(void);
//void ta0_config(void);
void gerar_bola();
void mover_bola();
void apagar_bola();
void raquete_touch();
void raquete_touch_cima();
void raquete_touchj2();
void raquete_touch_cimaj2();
void gerar_placar();

volatile int bola_col[] = {63,64,65};
volatile int bola_lin[] = {94,95,96};
volatile int linha,linha2,lado,direcao,casa=0,visitante=0;

int main(void){
    char i,vx[10],vy[10];
    char x,y;
    char lin,col;
    volatile int move,move2,bola,random=10;
    int linha_max;
    int linha_min;

    //volatile int adc,adc1,teste=0;

    int raqMax_d=97,raqMin_d=90,dif;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    clk_20mhz();            //<<<=== SMCLK = 20 MHz
    ta2_config();
    gpio_config();
    uart_config();
    usci_b1_config();
    rrand_inic();
    adc_config();
    tb0_config();

    __enable_interrupt();
    espera_10ms(10);

    oled_buf_apaga();
    oled_wr_cmdo(vet_cmdo1,27);
    oled_wr_cmdo(vet_cmdo2,4);

    oled_linha(0,64,125,64,PX_ON);//LINHA HORIZONTAL SUPERIOR
    oled_linha(0,127,125,127,PX_ON);//LINHA HORIZONTAL INFERIOR
    oled_linha(125,0,125,125,PX_ON);//LINHA VERTICAL LADO DIREITO
    oled_linha(0,0,0,125,PX_ON);//LINHA VERTICAL LADO ESQUERDO

    //Desenha raquete lado esquerdo
    oled_linha(5,90,5,90,PX_ON);//Raquete lado esquerdo
    oled_linha(5,91,5,91,PX_ON);//Raquete lado esquerdo
    oled_linha(5,92,5,92,PX_ON);//Raquete lado esquerdo
    oled_linha(5,93,5,93,PX_ON);//Raquete lado esquerdo
    oled_linha(5,94,5,94,PX_ON);//Raquete lado esquerdo
    oled_linha(5,95,5,95,PX_ON);//Raquete lado esquerdo
    oled_linha(5,96,5,96,PX_ON);//Raquete lado esquerdo
    oled_linha(5,97,5,97,PX_ON);//Raquete lado esquerdo

    //Desenha raquete lado direito
    oled_linha(120,90,120,90,PX_ON);//Raquete lado direito
    oled_linha(120,91,120,91,PX_ON);//Raquete lado direito
    oled_linha(120,92,120,92,PX_ON);//Raquete lado direito
    oled_linha(120,93,120,93,PX_ON);//Raquete lado direito
    oled_linha(120,94,120,94,PX_ON);//Raquete lado direito
    oled_linha(120,95,120,95,PX_ON);//Raquete lado direito
    oled_linha(120,96,120,96,PX_ON);//Raquete lado direito
    oled_linha(120,97,120,97,PX_ON);//Raquete lado direito

    /*//Desenha linha central
    while (linha < 126){
        oled_linha(64,linha,64,linha,PX_ON);
        linha=linha+8;
    }*/

    while(sw1_estado == ABERTA){   //Esperar acionar SW1
        //oled_frase("PONG",55,8,PX_ON);
        oled_frase_delay10ms("PONG",55,8,PX_ON,10000);
        oled_frase_delay10ms("PONG",55,8,PX_OFF,10000);
        oled_frase("HOLD SW1 TO PLAY",31,33,PX_ON);
        espera_10ms(80);
        oled_frase("HOLD SW1 TO PLAY",31,33,PX_OFF);
        espera_10ms(40);
    }
    oled_frase("PONG",55,8,PX_OFF);
    oled_frase("PRESS SW1 TO PLAY",25,33,PX_OFF);
    oled_frase_delay10ms("START",52,28,PX_ON,7500);
    oled_frase("START",52,28,PX_OFF);
    linha=90;
    linha2=90;

    gerar_bola();
    espera_10ms(100);
    direcao = rrand_fx(random);
    lado = rrand_fx(random);
    while(1){
        move = read_pos();
        move2 = read_pos2();


        if(bola_col[1]==2){
            random++;
            visitante++;
            apagar_bola();
            bola_lin[0]=94;
            bola_lin[1]=95;
            bola_lin[2]=96;
            bola_col[0]=63;
            bola_col[1]=64;
            bola_col[2]=65;
            mover_bola();
            direcao = rrand_fx(random);
            lado = rrand_fx(random);
        }
        else if(bola_col[1]==123){
            random++;
            casa++;
            apagar_bola();
            bola_lin[0]=94;
            bola_lin[1]=95;
            bola_lin[2]=96;
            bola_col[0]=63;
            bola_col[1]=64;
            bola_col[2]=65;
            mover_bola();
            direcao = rrand_fx(random);
            lado = rrand_fx(random);
        }

        if(bola_lin[2] == 126){
            direcao=1;
        }
        else if(bola_lin[0] == 65){
            direcao=0;
        }

        //BOLA
        //espera_10ms(5);
        if(direcao%2==0){
            apagar_bola();
            bola_lin[0]=bola_lin[0]+1;
            bola_lin[1]=bola_lin[1]+1;
            bola_lin[2]=bola_lin[2]+1;
            if(lado%2!=0){
                bola_col[0]=bola_col[0]+1;
                bola_col[1]=bola_col[1]+1;
                bola_col[2]=bola_col[2]+1;
            }
            else{
                bola_col[0]=bola_col[0]-1;
                bola_col[1]=bola_col[1]-1;
                bola_col[2]=bola_col[2]-1;
            }
            mover_bola();
        }
        else{
            apagar_bola();
            bola_lin[0]=bola_lin[0]-1;
            bola_lin[1]=bola_lin[1]-1;
            bola_lin[2]=bola_lin[2]-1;
            if(lado%2!=0){
                bola_col[0]=bola_col[0]+1;
                bola_col[1]=bola_col[1]+1;
                bola_col[2]=bola_col[2]+1;
            }
            else{
                bola_col[0]=bola_col[0]-1;
                bola_col[1]=bola_col[1]-1;
                bola_col[2]=bola_col[2]-1;
            }
            mover_bola();
        }

        gerar_bola();

        if(move==0){//mover para baixo

            oled_linha(5,linha,5,linha,PX_OFF);    //Raquete lado esquerdo
            oled_linha(5,linha+1,5,linha+1,PX_OFF);//Raquete lado esquerdo
            oled_linha(5,linha+2,5,linha+2,PX_OFF);//Raquete lado esquerdo
            oled_linha(5,linha+3,5,linha+3,PX_OFF);//Raquete lado esquerdo
            oled_linha(5,linha+4,5,linha+4,PX_OFF);//Raquete lado esquerdo
            oled_linha(5,linha+5,5,linha+5,PX_OFF);//Raquete lado esquerdo
            oled_linha(5,linha+6,5,linha+6,PX_OFF);//Raquete lado esquerdo
            oled_linha(5,linha+7,5,linha+7,PX_OFF);//Raquete lado esquerdo

            linha=linha-7;

            if(linha<=64){
                dif=64-linha;
                linha=linha+(1+dif);
                //linha=linha-8;
            }

            oled_linha(5,linha,5,linha,PX_ON);    //Raquete lado esquerdo
            oled_linha(5,linha+1,5,linha+1,PX_ON);//Raquete lado esquerdo
            oled_linha(5,linha+2,5,linha+2,PX_ON);//Raquete lado esquerdo
            oled_linha(5,linha+3,5,linha+3,PX_ON);//Raquete lado esquerdo
            oled_linha(5,linha+4,5,linha+4,PX_ON);//Raquete lado esquerdo
            oled_linha(5,linha+5,5,linha+5,PX_ON);//Raquete lado esquerdo
            oled_linha(5,linha+6,5,linha+6,PX_ON);//Raquete lado esquerdo
            oled_linha(5,linha+7,5,linha+7,PX_ON);//Raquete lado esquerdo
            raquete_touch();
            //espera_10ms(25);

        }
        else if(move==2){//mover para cima

            oled_linha(5,linha,5,linha,PX_OFF);    //Raquete lado esquerdo
            oled_linha(5,linha-1,5,linha-1,PX_OFF);//Raquete lado esquerdo
            oled_linha(5,linha-2,5,linha-2,PX_OFF);//Raquete lado esquerdo
            oled_linha(5,linha-3,5,linha-3,PX_OFF);//Raquete lado esquerdo
            oled_linha(5,linha-4,5,linha-4,PX_OFF);//Raquete lado esquerdo
            oled_linha(5,linha-5,5,linha-5,PX_OFF);//Raquete lado esquerdo
            oled_linha(5,linha-6,5,linha-6,PX_OFF);//Raquete lado esquerdo
            oled_linha(5,linha-7,5,linha-7,PX_OFF);//Raquete lado esquerdo

            linha=linha+7;

            if(linha>=127){
                dif=linha-127;
                linha=linha-2-dif;
                //linha=linha-8;
            }

            oled_linha(5,linha,5,linha,PX_ON);    //Raquete lado esquerdo
            oled_linha(5,linha-1,5,linha-1,PX_ON);//Raquete lado esquerdo
            oled_linha(5,linha-2,5,linha-2,PX_ON);//Raquete lado esquerdo
            oled_linha(5,linha-3,5,linha-3,PX_ON);//Raquete lado esquerdo
            oled_linha(5,linha-4,5,linha-4,PX_ON);//Raquete lado esquerdo
            oled_linha(5,linha-5,5,linha-5,PX_ON);//Raquete lado esquerdo
            oled_linha(5,linha-6,5,linha-6,PX_ON);//Raquete lado esquerdo
            oled_linha(5,linha-7,5,linha-7,PX_ON);//Raquete lado esquerdo
            raquete_touch_cima();
            //espera_10ms(25);
        }
        else{
            raquete_touch();///first one
        }

        if(move2==0){//mover para baixo

            oled_linha(120,linha2,120,linha2,PX_OFF);    //Raquete lado direito
            oled_linha(120,linha2+1,120,linha2+1,PX_OFF);//Raquete lado direito
            oled_linha(120,linha2+2,120,linha2+2,PX_OFF);//Raquete lado direito
            oled_linha(120,linha2+3,120,linha2+3,PX_OFF);//Raquete lado direito
            oled_linha(120,linha2+4,120,linha2+4,PX_OFF);//Raquete lado direito
            oled_linha(120,linha2+5,120,linha2+5,PX_OFF);//Raquete lado direito
            oled_linha(120,linha2+6,120,linha2+6,PX_OFF);//Raquete lado direito
            oled_linha(120,linha2+7,120,linha2+7,PX_OFF);//Raquete lado direito
            linha2=linha2-7;

            if(linha2<=64){
                dif=64-linha2;
                linha2=linha2+(1+dif);
                //linha=linha-8;
            }

            oled_linha(120,linha2,120,linha2,PX_ON);    //Raquete lado direito
            oled_linha(120,linha2+1,120,linha2+1,PX_ON);//Raquete lado direito
            oled_linha(120,linha2+2,120,linha2+2,PX_ON);//Raquete lado direito
            oled_linha(120,linha2+3,120,linha2+3,PX_ON);//Raquete lado direito
            oled_linha(120,linha2+4,120,linha2+4,PX_ON);//Raquete lado direito
            oled_linha(120,linha2+5,120,linha2+5,PX_ON);//Raquete lado direito
            oled_linha(120,linha2+6,120,linha2+6,PX_ON);//Raquete lado direito
            oled_linha(120,linha2+7,120,linha2+7,PX_ON);//Raquete lado direito
            raquete_touchj2();
            //espera_10ms(12);
        }
        else if(move2==2){//mover para cima

            oled_linha(120,linha2,120,linha2,PX_OFF);    //Raquete lado direito
            oled_linha(120,linha2-1,120,linha2-1,PX_OFF);//Raquete lado direito
            oled_linha(120,linha2-2,120,linha2-2,PX_OFF);//Raquete lado direito
            oled_linha(120,linha2-3,120,linha2-3,PX_OFF);//Raquete lado direito
            oled_linha(120,linha2-4,120,linha2-4,PX_OFF);//Raquete lado direito
            oled_linha(120,linha2-5,120,linha2-5,PX_OFF);//Raquete lado direito
            oled_linha(120,linha2-6,120,linha2-6,PX_OFF);//Raquete lado direito
            oled_linha(120,linha2-7,120,linha2-7,PX_OFF);//Raquete lado direito

            linha2=linha2+7;

            if(linha2>=127){
                dif=linha2-127;
                linha2=linha2-2-dif;
                //linha=linha-8;
            }

            oled_linha(120,linha2,120,linha2,PX_ON);    //Raquete lado direito
            oled_linha(120,linha2-1,120,linha2-1,PX_ON);//Raquete lado direito
            oled_linha(120,linha2-2,120,linha2-2,PX_ON);//Raquete lado direito
            oled_linha(120,linha2-3,120,linha2-3,PX_ON);//Raquete lado direito
            oled_linha(120,linha2-4,120,linha2-4,PX_ON);//Raquete lado direito
            oled_linha(120,linha2-5,120,linha2-5,PX_ON);//Raquete lado direito
            oled_linha(120,linha2-6,120,linha2-6,PX_ON);//Raquete lado direito
            oled_linha(120,linha2-7,120,linha2-7,PX_ON);//Raquete lado direito
            raquete_touch_cimaj2();
            //espera_10ms(12);



        }

        else{
            raquete_touchj2();
        }

        if(casa==3 || visitante==3){
            //Apagar a raquete do lado direito
            oled_linha(120,0,120,125,PX_OFF);
            //Apagar a raquete do lado esquerdo
            oled_linha(5,0,5,125,PX_OFF);
            apagar_bola();
            gerar_placar();
            casa=0;
            visitante=0;
            bola_col[0]=63;bola_col[1]=64;bola_col[2]=65;
            bola_lin[0]=94;bola_lin[1]=95;bola_lin[2]=96;
            linha=90;
            linha2=90;

            oled_linha(0,64,125,64,PX_ON);//LINHA HORIZONTAL SUPERIOR
            oled_linha(0,127,125,127,PX_ON);//LINHA HORIZONTAL INFERIOR
            oled_linha(125,0,125,125,PX_ON);//LINHA VERTICAL LADO DIREITO
            oled_linha(0,0,0,125,PX_ON);//LINHA VERTICAL LADO ESQUERDO

            oled_linha(5,90,5,90,PX_ON);//Raquete lado esquerdo
            oled_linha(5,91,5,91,PX_ON);//Raquete lado esquerdo
            oled_linha(5,92,5,92,PX_ON);//Raquete lado esquerdo
            oled_linha(5,93,5,93,PX_ON);//Raquete lado esquerdo
            oled_linha(5,94,5,94,PX_ON);//Raquete lado esquerdo
            oled_linha(5,95,5,95,PX_ON);//Raquete lado esquerdo
            oled_linha(5,96,5,96,PX_ON);//Raquete lado esquerdo
            oled_linha(5,97,5,97,PX_ON);//Raquete lado esquerdo

            oled_linha(120,90,120,90,PX_ON);//Raquete lado direito
            oled_linha(120,91,120,91,PX_ON);//Raquete lado direito
            oled_linha(120,92,120,92,PX_ON);//Raquete lado direito
            oled_linha(120,93,120,93,PX_ON);//Raquete lado direito
            oled_linha(120,94,120,94,PX_ON);//Raquete lado direito
            oled_linha(120,95,120,95,PX_ON);//Raquete lado direito
            oled_linha(120,96,120,96,PX_ON);//Raquete lado direito
            oled_linha(120,97,120,97,PX_ON);//Raquete lado direito

            gerar_bola();
            espera_10ms(100);
        }
        espera_10ms(4);

    }

    return 0;
}

void gerar_placar(){
    if(casa==0){
        oled_frase("0",54,74,PX_ON);
        oled_frase("X",64,74,PX_ON);
    }
    else if(casa==1){
        oled_frase("1",54,74,PX_ON);
        oled_frase("X",64,74,PX_ON);
    }
    else if(casa==2){
        oled_frase("2",54,74,PX_ON);
        oled_frase("X",64,74,PX_ON);
    }
    else{
        oled_frase("3",54,74,PX_ON);
        oled_frase("X",64,74,PX_ON);
        oled_frase("PLAYER 1 WINS!",36,94,PX_ON);
    }

    if(visitante==0){
        oled_frase("0",74,74,PX_ON);
    }
    else if(visitante==1){
        oled_frase("1",74,74,PX_ON);
    }
    else if(visitante==2){
        oled_frase("2",74,74,PX_ON);
    }
    else{
        oled_frase("3",74,74,PX_ON);
        oled_frase("PLAYER 2 WINS!",36,94,PX_ON);
    }

    while(sw1_estado == ABERTA){   //Esperar acionar SW1
        oled_frase("*HOLD SW1 TO PLAY",28,104,PX_ON);
        espera_10ms(80);
        oled_frase("*HOLD SW1 TO PLAY",28,104,PX_OFF);
        espera_10ms(40);
    }

    if(casa==0){
        oled_frase("0",54,74,PX_OFF);
        oled_frase("X",64,74,PX_OFF);
    }
    else if(casa==1){
        oled_frase("1",54,74,PX_OFF);
        oled_frase("X",64,74,PX_OFF);
    }
    else if(casa==2){
        oled_frase("2",54,74,PX_OFF);
        oled_frase("X",64,74,PX_OFF);
    }
    else{
        oled_frase("3",54,74,PX_OFF);
        oled_frase("X",64,74,PX_OFF);
        oled_frase("PLAYER 2 WINS!",36,94,PX_OFF);
    }

    if(visitante==0){
        oled_frase("0",74,74,PX_OFF);
    }
    else if(visitante==1){
        oled_frase("1",74,74,PX_OFF);
    }
    else if(visitante==2){
        oled_frase("2",74,74,PX_OFF);
    }
    else{
        oled_frase("3",74,74,PX_OFF);
        oled_frase("PLAYER 2 WINS!",36,94,PX_OFF);
    }

}

void raquete_touchj2(){
    if((bola_lin[0] == linha-2) ||
            (bola_lin[0] == linha2-1) ||
            (bola_lin[0] == linha2  ) ||
            (bola_lin[0] == linha2+1) ||
            (bola_lin[0] == linha2+2) ||
            (bola_lin[0] == linha2+3) ||
            (bola_lin[0] == linha2+4) ||
            (bola_lin[0] == linha2+5) ||
            (bola_lin[0] == linha2+6) ||
            (bola_lin[0] == linha2+7)
    ){
        if(bola_col[2] >= 121){
            lado=2;
        }
        /*else if(bola_col[2] == 9){
            lado=3;
        }*/
    }
}

void raquete_touch_cimaj2(){
    if((bola_lin[0] == linha2+2) ||
            (bola_lin[0] == linha2+1) ||
            (bola_lin[0] == linha2  ) ||
            (bola_lin[0] == linha2-1) ||
            (bola_lin[0] == linha2-2) ||
            (bola_lin[0] == linha2-3) ||
            (bola_lin[0] == linha2-4) ||
            (bola_lin[0] == linha2-5) ||
            (bola_lin[0] == linha2-6) ||
            (bola_lin[0] == linha2-7)
    ){
        if(bola_col[2] >= 121){
            lado=2;
        }
    }
}

void raquete_touch(){
    if((bola_lin[0] == linha-2) ||
            (bola_lin[0] == linha-1) ||
            (bola_lin[0] == linha  ) ||
            (bola_lin[0] == linha+1) ||
            (bola_lin[0] == linha+2) ||
            (bola_lin[0] == linha+3) ||
            (bola_lin[0] == linha+4) ||
            (bola_lin[0] == linha+5) ||
            (bola_lin[0] == linha+6) ||
            (bola_lin[0] == linha+7)
    ){
        if(bola_col[0] <= 9){
            lado=3;
        }
        else if(bola_col[2] == 9){
            lado=3;
        }
    }
}

void raquete_touch_cima(){
    if((bola_lin[0] == linha+2) ||
            (bola_lin[0] == linha+1) ||
            (bola_lin[0] == linha  ) ||
            (bola_lin[0] == linha-1) ||
            (bola_lin[0] == linha-2) ||
            (bola_lin[0] == linha-3) ||
            (bola_lin[0] == linha-4) ||
            (bola_lin[0] == linha-5) ||
            (bola_lin[0] == linha-6) ||
            (bola_lin[0] == linha-7)
    ){
        if(bola_col[0] <= 9){
            lado=3;
        }
        else if(bola_col[2] == 9){
            lado=3;
        }
    }
}

void gerar_bola(){

    oled_linha(bola_col[0],bola_lin[0],bola_col[0],bola_lin[0],PX_ON);
    oled_linha(bola_col[1],bola_lin[0],bola_col[1],bola_lin[0],PX_ON);//lado e
    oled_linha(bola_col[2],bola_lin[0],bola_col[2],bola_lin[0],PX_ON);//lado d

    oled_linha(bola_col[0],bola_lin[1],bola_col[0],bola_lin[1],PX_ON);
    oled_linha(bola_col[1],bola_lin[1],bola_col[1],bola_lin[1],PX_ON);//lado e
    oled_linha(bola_col[2],bola_lin[1],bola_col[2],bola_lin[1],PX_ON);//lado d

    oled_linha(bola_col[0],bola_lin[2],bola_col[0],bola_lin[2],PX_ON);
    oled_linha(bola_col[1],bola_lin[2],bola_col[1],bola_lin[2],PX_ON);//lado e
    oled_linha(bola_col[2],bola_lin[2],bola_col[2],bola_lin[2],PX_ON);//lado d

}

void mover_bola(){
    oled_linha(bola_col[0],bola_lin[0],bola_col[0],bola_lin[0],PX_ON);
    oled_linha(bola_col[1],bola_lin[0],bola_col[1],bola_lin[0],PX_ON);//lado e
    oled_linha(bola_col[2],bola_lin[0],bola_col[2],bola_lin[0],PX_ON);//lado d

    oled_linha(bola_col[0],bola_lin[1],bola_col[0],bola_lin[1],PX_ON);
    oled_linha(bola_col[1],bola_lin[1],bola_col[1],bola_lin[1],PX_ON);//lado e
    oled_linha(bola_col[2],bola_lin[1],bola_col[2],bola_lin[1],PX_ON);//lado d

    oled_linha(bola_col[0],bola_lin[2],bola_col[0],bola_lin[2],PX_ON);
    oled_linha(bola_col[1],bola_lin[2],bola_col[1],bola_lin[2],PX_ON);//lado e
    oled_linha(bola_col[2],bola_lin[2],bola_col[2],bola_lin[2],PX_ON);//lado d
}

void apagar_bola(){

    oled_linha(bola_col[0],bola_lin[0],bola_col[0],bola_lin[0],PX_OFF);
    oled_linha(bola_col[1],bola_lin[0],bola_col[1],bola_lin[0],PX_OFF);//lado e
    oled_linha(bola_col[2],bola_lin[0],bola_col[2],bola_lin[0],PX_OFF);//lado d

    oled_linha(bola_col[0],bola_lin[1],bola_col[0],bola_lin[1],PX_OFF);
    oled_linha(bola_col[1],bola_lin[1],bola_col[1],bola_lin[1],PX_OFF);//lado e
    oled_linha(bola_col[2],bola_lin[1],bola_col[2],bola_lin[1],PX_OFF);//lado d

    oled_linha(bola_col[0],bola_lin[2],bola_col[0],bola_lin[2],PX_OFF);
    oled_linha(bola_col[1],bola_lin[2],bola_col[1],bola_lin[2],PX_OFF);//lado e
    oled_linha(bola_col[2],bola_lin[2],bola_col[2],bola_lin[2],PX_OFF);//lado d

}


