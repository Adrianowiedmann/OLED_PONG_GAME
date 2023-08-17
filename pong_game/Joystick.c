#include <msp430.h>

#include <Joystick.h>

int read_pos(void){

//    ADC12CTL0 |= ADC12ENC; // Enable ADC12
//    while ((ADC12IFG&ADC12IFG1) == 0); // Esperar conversão
//    ADC12CTL0 &= ~ADC12ENC; // Disable ADC12
    volatile int adc0, adc1, pos_x;
    adc0  = ADC12MEM0;
    adc1  = ADC12MEM1;
    pos_x = (adc0 + adc1)/2;

    // DEBUG: imprimir valor na porta serial
//    ser_print_joystick_pos(pos_x);

    // Converte a posição em 0, 1, 2
    //  0: Move a nave para cima
    //  1: Deixa ela parada
    //  2: Move a nave para b
    if      (pos_x <= 80)  return 0;
    else if (pos_x <= 175) return 1;
    else                   return 2;
}

int read_pos2(void){
    volatile int adc2, adc3, pos_x;
    adc2  = ADC12MEM2;
    adc3  = ADC12MEM3;
    pos_x = (adc2 + adc3)/2;

    // DEBUG: imprimir valor na porta serial
//    ser_print_joystick_pos(pos_x);

    // Converte a posição em 0, 1, 2
    //  0: Move a nave para cima
    //  1: Deixa ela parada
    //  2: Move a nave para b
    if      (pos_x <= 80)  return 0;
    else if (pos_x <= 175) return 1;
    else                   return 2;
}


// Configurar o ADC, com disparo por TB0.1
void adc_config(void){
    ADC12CTL0 &= ~ADC12ENC; // Disable para configurar

    ADC12CTL0 = ADC12ON;      // Ligar ADC

    ADC12CTL1 = ADC12SHS_3       | // Disparo por TB0.1
                ADC12SSEL_3      | // Clock ADC = SMCLK
                ADC12DIV_0       | // Clock ADC Divisor = 1
                ADC12CSTARTADD_0 | // Resultado inicia em ADC12MEM0
                ADC12CONSEQ_3;     // Modo Canais REPETIÇÃO

    ADC12CTL2 = ADC12TCOFF | // Desligar sensor de temperatura (optativo para poupar energia)
                ADC12RES_0;  // Resolução 8-bit

    ADC12MCTL0  = ADC12SREF_0 | ADC12INCH_1;  // (P6.1) A1 = Canal 1
    ADC12MCTL1  = ADC12SREF_0 | ADC12INCH_1;  // (P6.1) A1 = Canal 1
    ADC12MCTL2  = ADC12SREF_0 | ADC12INCH_3;  // (P6.3) A1 = Canal 1
    ADC12MCTL3  = ADC12SREF_0 | ADC12INCH_3;  // (P6.3) A1 = Canal 1
    ADC12MCTL3 |= ADC12EOS; // EOS

    ADC12CTL0 |= ADC12ENC; // Enable
}

// TB0.1 ==> Gerar PWM para disparar ADC
void tb0_config(void){
    TB0CTL = TBSSEL_2 | MC_1; // SMCLK - Modo Up
    TB0CCR0 = 1024;   // Modo 1
    TB0CCTL1 = OUTMOD_6;   // PWM
    TB0CCR1 = TB0CCR0 / 2; // 50%
}
