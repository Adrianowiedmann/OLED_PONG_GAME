/*
 * oled.h
 *
 *  Created on: 26 de mar de 2022
 *      Author: zelen
 */

#ifndef OLED_H_
#define OLED_H_

#define OLED_ADR    0x3C    //60 decimal
#define USCIB1_TXBUF_ADDR   (__SFR_FARPTR) 0x062E

extern volatile char dma2_flag;          //Flag que indica uso de DMA
extern volatile char oled_flag;          //Flag que indica uso de DMA
extern volatile char oled_fase;          //Flag que indica uso de DMA
extern char oled_buf[8][130];            //Buffer para todo o OLED
extern char oled_pag[5];
extern char vet_cmdo1[];        // 27 elementos
extern char vet_cmdo2[];
extern char vet_dado1[];        // 129 elementos

void oled_retg(char x1, char y1, char x2, char y2, char oque);
void oled_linha(char x1, char y1, char x2, char y2, char oque);
void oled_pix(char x, char y, char oque);
void oled_padrao_2(void);
void oled_padrao_1(void);
void oled_buf_vai(void);
void oled_wr_cmdo(char *vet, int qtd);
void oled_wr_dado(char *vet, int qtd);
void oled_buf_apaga(void);
void oled_buf_apaga_dma(void);
void oled_dma2_prep(void);
void usci_b1_start(void);
void usci_b1_stop(void);







#endif /* OLED_H_ */
