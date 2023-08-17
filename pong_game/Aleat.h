// Aleat.h

#ifndef ALEAT_H_
#define ALEAT_H_

#define ALEAT_SUGEST_M   53  //m sugerido
#define ALEAT_SUGEST_D   109 //d sugerido
#define ALEAT_SUGEST_U   13  //u sugerido (semente)

unsigned int rrand(void);
unsigned int rrand_fx(unsigned int faixa);
void rrand_inic(void);
void rrand_inic_seed (unsigned int seed);
void rrand_inic_tudo(unsigned int seed, unsigned int div, unsigned int mult);

unsigned int rrand_m ;  //multiplicador
unsigned int rrand_d;   //divisor
unsigned int rrand_u;   //semente


#endif /* ALEAT_H_ */
