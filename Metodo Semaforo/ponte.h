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
	printf("%d \t\t %s \t %s \t %d \t\t %d\n", crianca->numero, crianca_getLado(crianca), "Esperando", crianca->numeroTravessias, crianca->tempoDecisao);

	sleep(crianca->tempoDecisao);
	semaforoBidimensional_semaforoEsquerda_utilize(ponte->semaforo);
	
	printf("%d \t\t %s \t %s \t %d \t\t %d\n", crianca->numero, crianca_getLado(crianca), "Atravessando", crianca->numeroTravessias, crianca->tempoDecisao);
	
	sleep(tempoTravessia);
		
	semaforoBidimensional_semaforoEsquerda_terminate(ponte->semaforo);
	
	printf("%d \t\t %s \t %s \t %d \t\t %d\n", crianca->numero, crianca_getLado(crianca), "Terminou", crianca->numeroTravessias, crianca->tempoDecisao);
	
	crianca->lado = DIREITA;
}

void ponte_atravessar_direitaParaEsquerda(Ponte *ponte, Crianca *crianca, int tempoTravessia)
{
	printf("%d \t\t %s \t %s \t %d \t\t %d\n", crianca->numero, crianca_getLado(crianca), "Esperando", crianca->numeroTravessias, crianca->tempoDecisao);
	
	sleep(crianca->tempoDecisao);
	semaforoBidimensional_semaforoDireita_utilize(ponte->semaforo);
	
	printf("%d \t\t %s \t %s \t %d \t\t %d\n", crianca->numero, crianca_getLado(crianca), "Atravessando", crianca->numeroTravessias, crianca->tempoDecisao);
	
	sleep(tempoTravessia);
	
	semaforoBidimensional_semaforoDireita_terminate(ponte->semaforo);
	
	printf("%d \t\t %s \t %s \t %d \t\t %d\n", crianca->numero, crianca_getLado(crianca), "Terminou", crianca->numeroTravessias, crianca->tempoDecisao);
	
	crianca->lado = ESQUERDA;
}

#endif
