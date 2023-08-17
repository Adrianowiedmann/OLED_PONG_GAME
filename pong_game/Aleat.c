// Aleat.c
//
// Gerador de números aleatórios

#include "aleat.h"

// Gerar um número aleatório (zero nunca é gerado)
// Faixa do número n gerado: 0 < n < rrand_d
unsigned int rrand(void){
    rrand_u= (rrand_m * rrand_u) % rrand_d;
    return rrand_u;
}



// Gerar um número aleatório dentro de 0 --> faixa
// Faixa do número n gerado: 0 <= n <= fx
unsigned int rrand_fx(unsigned int fx){
    do rrand_u= (rrand_m * rrand_u) % rrand_d;
    while (rrand_u>fx+1);
    return rrand_u-1;
}

// Inicializar os parâmetros por omissão
void rrand_inic(void){
    rrand_u = ALEAT_SUGEST_U;  //semente
    rrand_d = ALEAT_SUGEST_D;  //divisor
    rrand_m = ALEAT_SUGEST_M;  //multiplicador
}

// Inicializar a semente
void rrand_inic_seed(unsigned int semente){
    rrand_u = semente;         //semente
    rrand_d = ALEAT_SUGEST_D;  //divisor
    rrand_m = ALEAT_SUGEST_M;  //multiplicador
}

// Inicializar todos os parâmetros do gerador
void rrand_inic_tudo(unsigned int seed,
                     unsigned int div,
                     unsigned int mult){
    rrand_u = seed;   //semente
    rrand_d = div;    //divisor
    rrand_m = mult;   //multiplicador
}


