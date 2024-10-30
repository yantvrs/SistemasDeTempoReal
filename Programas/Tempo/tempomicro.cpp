
// UFRN-CT-DCA
// Disciplina: Sistemas de Tempo Real
// Programa: tempomicro.cpp

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main() {
    int i, j;
    struct timeval tempo_inicial, tempo_final;
    int tmili;
    float tmili_final;

    gettimeofday(&tempo_inicial, NULL);  // início é uma struct com dois campos:tv_sec e tv_usec.
    
     /* Substitua o for a seguir pelo trecho de código
       cujo tempo de execução deverá ser medido. */
    
    for (j = 0; j < 10; j ++)
        for (i = 0; i < 1387634340; i ++);
    
    gettimeofday(&tempo_final, NULL);
    tmili = (int) (1000 * (tempo_final.tv_sec - tempo_inicial.tv_sec) + (tempo_final.tv_usec - tempo_inicial.tv_usec) / 1000); // para transformar em milissegundos
    tmili_final = tmili/1000;
    
    printf("tempo decorrido: %d milissegundos\n", tmili_final);
   
    return (0);
}
