// Timer.h

#ifndef TIMER_H_
#define TIMER_H_

#define FLLN(x) ((x)-1)

#define TA2_PASSO_1ms   20971   // SMCLK/1000 = 20.971, passo de 1 mseg

// Variáveis do timer
extern volatile char flag_1ms;
extern volatile char flag_10ms;
extern volatile char flag_100ms;
extern volatile char flag_1seg;

// Varoáveis para o Oled
extern volatile char dma2_flag;         //Indica que DMA2 está em uso (refresh Oled ou apagando buffer)
extern volatile char oled_flag;         //Indica que houve atualização no buffer --> fazer refresh
extern volatile char oled_fase;          //Flag que indica uso de DMA

void espera_10ms(int x);
void ta2_config(void);
void clk_20mhz(void);

#endif /* TIMER_H_ */
