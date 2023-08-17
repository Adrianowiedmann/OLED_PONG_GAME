// Globais.h

#ifndef GLOBAIS_H_
#define GLOBAIS_H_

// Vari�veis do timer
volatile char flag_1ms   = FALSE;
volatile char flag_10ms  = FALSE;
volatile char flag_100ms = FALSE;
volatile char flag_1seg  = FALSE;

// Vari�veis para monitorar as chaves
volatile char sw1_estado;   //ABERTA, TRANSITO, FECHADA
volatile char sw1;          //TRUE se chave acionada
volatile char sw2_estado;   //ABERTA, TRANSITO, FECHADA
volatile char sw2;          //TRUE se chave acionada

// Vari�veis para o OLED
volatile char oled_fase;    //Indicar fase do refresh do Oled quando se usa DMA2
volatile char dma2_flag=FALSE;    //Indica que DMA2 est� em uso (refresh Oled ou apagando buffer)
volatile char oled_flag;    //Indica que houve atualiza��o no buffer --> fazer refresh
char oled_buf[8][130];      //Buffer para o Oled


// 27 elementos
char vet_cmdo1[]={0x00, 0xAE, 0xD5, 0x80, 0xA8, 0x3F, 0xD3, 0x00, 0x40, 0x8D,
                  0x14, 0x20, 0x00, 0xA1, 0xC8, 0xDA, 0x12, 0x81, 0xCF, 0xD9,
                  0xF1, 0xDB, 0x40, 0x2E, 0xA4, 0xA6, 0xAF};

char oled_pag[5]={0x00, 0x10, 0x00, 0xB0, 0x55};    //O �ltimo byte sobra
char vet_cmdo2[]={0x00, 0x10, 0x00, 0xB0};

// 129
char vet_dado1[]={0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0x20, 0x20, 0x20, 0xE0, 0xC0, 0x00, 0x20, 0x20,
                  0x20, 0x20, 0xA0, 0xE0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40,
                  0x80, 0x00, 0x00, 0xC0, 0xE0, 0x60, 0x20, 0x20, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0xF0, 0xF0, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x08, 0xE8, 0xE8, 0xE8, 0xE8,
                  0x08, 0x08, 0x08, 0xE8, 0xE8, 0xE8, 0xE8, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0xF8, 0xC0, 0xC0, 0x00};





#endif /* GLOBAIS_H_ */
