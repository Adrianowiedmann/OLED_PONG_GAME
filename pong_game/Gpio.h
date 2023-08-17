// gpio.h

#ifndef GPIO_H_
#define GPIO_H_

#define SW_CONT_MAX 30      //SW: Máx contagens para garantir chave estável

extern volatile char sw1_estado;   //ABERTA, TRANSITO, FECHADA
extern volatile char sw1;          //TRUE se chave acionada
extern volatile char sw2_estado;   //ABERTA, TRANSITO, FECHADA
extern volatile char sw2;          //TRUE se chave acionada

void led_VM(void);
void led_vm(void);
void led_Vm(void);
void led_VD(void);
void led_vd(void);
void led_Vd(void);
void scp1(void);
void SCP1(void);
void Scp1(void);
void scp2(void);
void SCP2(void);
void Scp2(void);
void sw_monitorar(void);

void gpio_config(void);




#endif /* GPIO_H_ */
