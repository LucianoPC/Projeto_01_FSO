#ifndef SEMAFOROBIDIMENSIONAL_H
#define SEMAFOROBIDIMENSIONAL_H

#include <stdlib.h>
#include <sys/sem.h>
#include "semaforo.h"

typedef struct _SemaforoBidimensional
{
	Semaforo *semaforoEsquerda;
	Semaforo *semaforoDireita;
	
	Semaforo *semaforoMediador;

}SemaforoBidimensional;

SemaforoBidimensional * semaforoBidimensional_create()
{
	SemaforoBidimensional *semaforoBidimensional = malloc(sizeof(SemaforoBidimensional));
	
	semaforoBidimensional->semaforoEsquerda = semaforo_create('U');
	semaforoBidimensional->semaforoDireita = semaforo_create('D');
	semaforoBidimensional->semaforoMediador = semaforo_create('M');
	
	semaforo_up(semaforoBidimensional->semaforoMediador);
	
	return semaforoBidimensional;
}

void semaforoBidimensional_delete(SemaforoBidimensional *semaforoBidimensional)
{
	semaforo_delete(semaforoBidimensional->semaforoEsquerda);
	semaforo_delete(semaforoBidimensional->semaforoDireita);
	semaforo_delete(semaforoBidimensional->semaforoMediador);
	
	free(semaforoBidimensional);
}


void semaforoBidimensional_semaforoEsquerda_utilize(SemaforoBidimensional *semaforoBidimensional)
{
	int valor_semaforoEsquerda;
	
	valor_semaforoEsquerda = semaforo_getValue(semaforoBidimensional->semaforoEsquerda);
	
	if(valor_semaforoEsquerda == 0)
		semaforo_down(semaforoBidimensional->semaforoMediador);
	
	semaforo_up(semaforoBidimensional->semaforoEsquerda);
}

void semaforoBidimensional_semaforoDireita_utilize(SemaforoBidimensional *semaforoBidimensional)
{
	int valor_semaforoDireita;
	
	valor_semaforoDireita = semaforo_getValue(semaforoBidimensional->semaforoDireita);
	
	if(valor_semaforoDireita == 0)
		semaforo_down(semaforoBidimensional->semaforoMediador);
	
	semaforo_up(semaforoBidimensional->semaforoDireita);
}

void semaforoBidimensional_semaforoEsquerda_terminate(SemaforoBidimensional *semaforoBidimensional)
{
	int valor_semaforoEsquerda;
	
	semaforo_down(semaforoBidimensional->semaforoEsquerda);
	
	valor_semaforoEsquerda = semaforo_getValue(semaforoBidimensional->semaforoEsquerda);
	
	if(valor_semaforoEsquerda == 0)
		semaforo_up(semaforoBidimensional->semaforoMediador);
}

void semaforoBidimensional_semaforoDireita_terminate(SemaforoBidimensional *semaforoBidimensional)
{
	int valor_semaforoDireita;
	
	semaforo_down(semaforoBidimensional->semaforoDireita);
	
	valor_semaforoDireita = semaforo_getValue(semaforoBidimensional->semaforoDireita);
	
	if(valor_semaforoDireita == 0)
		semaforo_up(semaforoBidimensional->semaforoMediador);
}

int semaforoBidimensional_semaforoEsquerda_getValue(SemaforoBidimensional *semaforoBidimensional)
{
	int valor_semaforoEsquerda;
	
	valor_semaforoEsquerda = semaforo_getValue(semaforoBidimensional->semaforoEsquerda);
	
	return valor_semaforoEsquerda;
}

int semaforoBidimensional_semaforoDireita_getValue(SemaforoBidimensional *semaforoBidimensional)
{
	int valor_semaforoDireita;
	
	valor_semaforoDireita = semaforo_getValue(semaforoBidimensional->semaforoDireita);
	
	return valor_semaforoDireita;
}

int semaforoBidimensional_semaforoMediador_getValue(SemaforoBidimensional *semaforoBidimensional)
{
	int valor_semaforoMediador;
	
	valor_semaforoMediador = semaforo_getValue(semaforoBidimensional->semaforoMediador);
	
	return valor_semaforoMediador;
}




#endif















