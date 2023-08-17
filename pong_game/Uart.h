// uart.h

#ifndef UART_H_
#define UART_H_

void ser_vet(char *vx, char *vy);
void ser_hex8(char x);
void ser_dec8(char x);
void ser_str(char *pt);
void ser_spc(char x);
void ser_crlf(char x);
void ser_char(char x);
void uart_config(void);




#endif /* UART_H_ */
