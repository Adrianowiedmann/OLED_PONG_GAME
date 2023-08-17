// Timer.c

#include <msp430.h>
#include "Defines.h"
#include "Timer.h"
#include "Gpio.h"
#include "Oled.h"

// Esperar um múltiplo de 10 mseg
void espera_10ms(int x){
    while(x>0){
        while(flag_10ms==FALSE);
        flag_10ms=FALSE;
        x--;
    }
}

// ISR TA2.0, a cada 1 mseg (1 kHz)
#pragma vector = 44
__interrupt void isr_ta2_ccr0(void){
    static char c1=0,c2=0,c3=0;
    static int oled_refresh=0;

    TA2CCR0 += TA2_PASSO_1ms;

    // OLED - refresh
    oled_refresh++;
    if (oled_refresh==OLED_TAXA){
        oled_refresh=0;
        if (oled_flag==TRUE){   //Tem alteração no Oled?
            // Refresh do OLED
            oled_flag=FALSE;
            dma2_flag=TRUE;
            oled_fase=0;
            oled_dma2_prep();
            DMA2CTL |= DMAIFG;  //Forçar uma interrupção do DMA2
        }
    }

    // 1 mseg
    flag_1ms=TRUE;          //1 mseg
    c1++;
    if (c1==10){            //10 mseg
        flag_10ms=TRUE;
        c1=0;
        c2++;
        if (c2==10){        //100 mseg
            flag_100ms=TRUE;
            c2=0;
            c3++;
            if (c3==10){        //100 mseg
                flag_1seg=TRUE;
                c3=0;
            }
        }
    }
    // Monitorar chaves
    sw_monitorar();
}



// TA2 --> Base de tempo
// TA2.0 --> Interrompe a cada 1 mseg (1 kHz)
// SMCLK/1000 = 20.971 contagens = 1 mseg
void ta2_config(void){
    TA2CTL = TASSEL_2 | MC_2;
    TA2CCTL0 = CCIE;
    TA2CCR0 = TA2_PASSO_1ms;
}


////////////////////////////////////////////////////
///////////////// UCS: 20 MHz  /////////////////////
////////////////////////////////////////////////////

// Configurar relógios da CPU
// MCLK = SMCLK = 20 MHz
// ACLK = 32.768 Hz
void clk_20mhz(void){

    // Configure crystal ports
    P5SEL |= BIT2 | BIT3 | BIT4 | BIT5;     // Configure P5 to use Crystals

    // This should make XT1 startup in 500ms and XT2 in less than 1ms
    UCSCTL6 = XT2DRIVE_3 |    // Turn up crystal drive to
              XT1DRIVE_3 |    // speed up oscillator startup
              XCAP_3     |    // Use maximum capacitance (12pF)
//            XT1OFF     |    // Make sure XT1 and XT2
//            XT2OFF     |    // oscillators are active
//            SMCLKOFF   |    // Leave SMCLK ON
//            XT1BYPASS  |    // Not using external clock source
//            XT2BYPASS  |    // Not using external clock source
//            XTS        |    // XT1 low-frequency mode, which
              0;              // means XCAP bits will be used

    UCSCTL0 = 0x00;           // Let FLL manage DCO and MOD

    UCSCTL1 = DCORSEL_6 |      // Select DCO range to around 20MHz
//            DISMOD    |      // Enable modulator
                        0;

    UCSCTL2 = FLLD_0 |         // (D=1) Set FLL dividers
              FLLN(5);         // DCOCLK = 1 * 5 * FLLREF = 20 MHz

    UCSCTL3 = SELREF_5 |       // Use XT2 (4 MHz) Oscillator for FLLREF
              FLLREFDIV_0;     // divided by 1

    UCSCTL5 = DIVPA_0 |        // Output dividers to 1
              DIVA_0  |        // ACLK  divided by 1
              DIVS_0  |        // SMCLK divided by 4
              DIVM_0;          // MCLK  divided by 1

    UCSCTL7 = 0;               // Clear XT2,XT1,DCO fault flags

    UCSCTL8 = SMCLKREQEN |     // Enable conditional requests for
              MCLKREQEN  |     // SMCLK, MCLK and ACLK. In case one
              ACLKREQEN;       // fails, another takes over

    do {                                                // Check if all clocks are oscillating
          UCSCTL7 &= ~( XT2OFFG   |  // Try to clear XT2,XT1,DCO fault flags,
                        XT1LFOFFG |  // system fault flags and check if
                        DCOFFG );    // oscillators are still faulty
          SFRIFG1 &= ~OFIFG;         //
    } while (SFRIFG1 & OFIFG);       // Exit only when everything is ok

    UCSCTL6 &= ~(XT1DRIVE_3 |        // Xtal is now stable,
                 XT2DRIVE_3);        // reduce drive strength (to save power)

    UCSCTL4 = SELA__XT1CLK |   // ACLK  = XT1 =>     32.768 Hz
              SELS__DCOCLK |   // SMCLK = DCO => 20.000.000 Hz
              SELM__DCOCLK;    // MCLK  = DCO => 20.000.000 Hz
}
