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

void imprimirMensagem_estadoCriancaNaPonte(Crianca *crianca, char *estado)
{
	printf("%d \t\t %s \t %s \t %d \t\t %d\n", crianca->numero, crianca_getLado(crianca), estado, crianca->numeroTravessias, crianca->tempoDecisao);
}

void ponte_atravessarCrianca_daEsquerdaParaDireita(Ponte *ponte, Crianca *crianca, int tempoTravessia)
{
	imprimirMensagem_estadoCriancaNaPonte(crianca, "Esperando");

	usleep(crianca->tempoDecisao);
	semaforoBidimensional_semaforoEsquerda_utilize(ponte->semaforo);
	
	imprimirMensagem_estadoCriancaNaPonte(crianca, "Atravessando");
	
	usleep(tempoTravessia);
	semaforoBidimensional_semaforoEsquerda_terminate(ponte->semaforo);
	
	imprimirMensagem_estadoCriancaNaPonte(crianca, "Terminou");
	
	crianca_mudarLado(crianca);
}

void ponte_atravessarCrianca_daDireitaParaEsquerda(Ponte *ponte, Crianca *crianca, int tempoTravessia)
{
	imprimirMensagem_estadoCriancaNaPonte(crianca, "Esperando");
	usleep(crianca->tempoDecisao);
	
	semaforoBidimensional_semaforoDireita_utilize(ponte->semaforo);
	
	imprimirMensagem_estadoCriancaNaPonte(crianca, "Atravessando");
	usleep(tempoTravessia);
	
	semaforoBidimensional_semaforoDireita_terminate(ponte->semaforo);
	
	imprimirMensagem_estadoCriancaNaPonte(crianca, "Terminou");
	
	crianca_mudarLado(crianca);
}

#endif
