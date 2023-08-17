// gpio.c

#include <msp430.h>
#include "Defines.h"
#include "Gpio.h"

void led_VM(void){  P1OUT |=  BIT0; } //VM aceso
void led_vm(void){  P1OUT &= ~BIT0; } //VM apagado
void led_Vm(void){  P1OUT ^=  BIT0; } //VM Invertido
void led_VD(void){  P4OUT |=  BIT7; } //VD aceso
void led_vd(void){  P4OUT &= ~BIT7; } //VD apagado
void led_Vd(void){  P4OUT ^=  BIT7; } //VD Invertido
void scp1(void)  {  P2OUT &= ~BIT5; }     //Scope1 Baixo
void SCP1(void)  {  P2OUT |=  BIT5; }     //Scope1 Alto
void Scp1(void)  {  P2OUT ^=  BIT5; }     //Scope1 Invertido
void scp2(void)  {  P2OUT &= ~BIT4; }     //Scope2 Baixo
void SCP2(void)  {  P2OUT |=  BIT4; }     //Scope2 Alto
void Scp2(void)  {  P2OUT ^=  BIT4; }     //Scope2 Invertido


// Monitorar SW1 e SW2, Chamada a cada 10 mseg.
// sw1_estado e sw2_estado indicam o valor atual da chave
// sw1 e sw2 indicam se a chave passou de aberta para fechada
void sw_monitorar(void){
    static char sw1_cont=0; //Contador para evitar rebotes em SW1 (0, 1, ..., SW_CONT_MAX)
    static char sw2_cont=0; //Contador para evitar rebotes em SW2 (0, 1, ..., SW_CONT_MAX)

    //SW1 - Evitar rebotes
    if ( (P2IN&BIT1)==0){
        sw1_cont++; //Fechada
        if (sw1_cont>SW_CONT_MAX)   sw1_cont=SW_CONT_MAX;
    }
    else{
        sw1_cont--; //Aberta
        if (sw1_cont==255)          sw1_cont=0;
    }

    //SW1 - Decidir A-->F ou F-->A
    if (sw1_estado==ABERTA){
        if (sw1_cont==SW_CONT_MAX){
            sw1_estado=FECHADA;
            sw1=TRUE;
        }
    }
    else{
        if (sw1_cont==0)
            sw1_estado=ABERTA;
    }

    //SW2 - Evitar rebotes
    if ( (P1IN&BIT1)==0){
        sw2_cont++; //Fechada
        if (sw2_cont>SW_CONT_MAX)   sw2_cont=SW_CONT_MAX;
    }
    else{
        sw2_cont--; //Aberta
        if (sw2_cont==255)          sw2_cont=0;
    }

    //SW2 - Decidir A-->F ou F-->A
    if (sw2_estado==ABERTA){
        if (sw2_cont==SW_CONT_MAX){
            sw2_estado=FECHADA;
            sw2=TRUE;
        }
    }
    else{
        if (sw2_cont==0)
            sw2_estado=ABERTA;
    }
}


// Configurar GPIO
void gpio_config(void){
    P1DIR |= BIT0; //Led1 = P1.0 = saída
    P1OUT &= ~BIT0; //Led1 apagado

    P4DIR |= BIT7; //Led2 = P4.7 = saída
    P4OUT &= ~BIT7; //Led1 apagado

    P2DIR &= ~BIT1; //S1 = P2.1 = entrada
    P2REN |= BIT1; //Habilitar resistor
    P2OUT |= BIT1; //Habilitar pullup

    P1DIR &= ~BIT1; //S2 = P1.1 = entrada
    P1REN |= BIT1; //Habilitar resistor
    P1OUT = BIT1; //Habilitar pullup

    P2DIR |= BIT5 | BIT4;      //Scope, P2.5=Scope1 e P2.4=Scope2
    P2OUT &= ~(BIT5 | BIT4);   //Scope, P2.5=Scope1 e P2.4=Scope2


}



