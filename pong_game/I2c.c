// i2c.c

#include <msp430.h>
#include "Defines.h"
#include <I2c.h>

// Testar endereço I2C
// TRUE se recebeu ACK
int i2c_adr_check(char adr){
    UCB1I2CSA = adr;                            //Endereço do PCF
    UCB1CTL1 |= UCTR | UCTXSTT;                 //Gerar START, Mestre transmissor
    while ( (UCB1IFG & UCTXIFG) == 0);          //Esperar pelo START
    UCB1CTL1 |= UCTXSTP;                        //Gerar STOP
    while ( (UCB1CTL1 & UCTXSTP) == UCTXSTP);   //Esperar pelo STOP
    if ((UCB1IFG & UCNACKIFG) == 0)     return TRUE;
    else                                return FALSE;
}


void usci_b1_config(void){
    UCB1CTL1 = UCSWRST;     //Resetar USCI_B1
    UCB1CTL0 = UCMODE_3 |   //Modo I2C
               UCMST    |   //Mestre
               UCSYNC;      //Síncrono
    //UCB1BRW = 210;            //SCL=100kHz
    UCB1BRW = 53;             //SCL=400kHz (53 ~= 52,43)

    P4SEL |= BIT2 | BIT1;   //Função alternativa
    P4REN |= BIT2 | BIT1;   //Hab resistor
    P4OUT |= BIT2 | BIT1;   //Pullup
    PMAPKEYID = 0X02D52;    //Liberar mapeamento
    P4MAP1 = PM_UCB1SDA;    //P4.1 = SDA
    P4MAP2 = PM_UCB1SCL;    //P4.2 = SCL
    UCB1CTL1 = UCSSEL_2;    //RST=0, SMCLK
}

