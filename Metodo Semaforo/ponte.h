#ifndef PONTE_H
#define PONTE_H

#include <stdlib.h>
#include "semaforoBidimensional.h"
#include "crianca.h"

typedef struct _Ponte{
	SemaforoBidimensional *semaforo;
}Ponte;

Ponte * ponte_create(){
	Ponte *ponte = malloc(sizeof(Ponte));
	ponte->semaforo = semaforoBidimensional_create();
	
	return ponte;
}

void ponte_delete(Ponte *ponte)
{
	semaforoBidimensional_delete(ponte->semaforo);
	free(ponte);
}

void ponte_atravessar_esquerdaParaDireita(Ponte *ponte, Crianca *crianca, int tempoTravessia)
{
	semaforoBidimensional_semaforoEsquerda_utilize(ponte->semaforo);
	printf("\nCrianca: %d. ATRAVESSANDO a ponte da ESQUERDA para DIREITA\n", crianca->numeroProcesso);
	usleep(tempoTravessia);
	printf("\nCrianca: %d TERMINOU DE ATRAVESSAR a ponte da ESQUERDA para DIREITA\n", crianca->numeroProcesso);
	semaforoBidimensional_semaforoEsquerda_terminate(ponte->semaforo);
}

void ponte_atravessar_direitaParaEsquerda(Ponte *ponte, Crianca *crianca, int tempoTravessia)
{
	semaforoBidimensional_semaforoDireita_utilize(ponte->semaforo);
	printf("\nCrianca %d. ATRAVESSANDO a ponte da DIREITA para ESQUERDA\n", crianca->numeroProcesso);
	usleep(tempoTravessia);
	semaforoBidimensional_semaforoDireita_terminate(ponte->semaforo);
	printf("\nCrianca %d. TERMINOU DE ATRAVESSAR a ponte da DIREITA para ESQUERDA\n", crianca->numeroProcesso);
}



#endif
