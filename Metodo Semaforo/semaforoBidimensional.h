#ifndef SEMAFOROBIDIMENSIONAL_H
#define SEMAFOROBIDIMENSIONAL_H

#include <stdlib.h>
#include <sys/sem.h>
#include "semaforo.h"

typedef struct _SemaforoBidimensional
{
	Semaforo *semaforoUm;
	Semaforo *semaforoDois;
	
	Semaforo *semaforoMediador;

}SemaforoBidimensional;

SemaforoBidimensional * semaforoBidimensional_create()
{
	SemaforoBidimensional *semaforoBidimensional = malloc(sizeof(SemaforoBidimensional));
	
	semaforoBidimensional->semaforoUm = semaforo_create('U');
	semaforoBidimensional->semaforoDois = semaforo_create('D');
	semaforoBidimensional->semaforoMediador = semaforo_create('M');
	
	semaforo_up(semaforoBidimensional->semaforoMediador);
	
	return semaforoBidimensional;
}

void semaforoBidimensional_delete(SemaforoBidimensional *semaforoBidimensional)
{
	semaforo_delete(semaforoBidimensional->semaforoUm);
	semaforo_delete(semaforoBidimensional->semaforoDois);
	semaforo_delete(semaforoBidimensional->semaforoMediador);
	
	free(semaforoBidimensional);
}


void semaforoBidimensional_semaforoUm_utilize(SemaforoBidimensional *semaforoBidimensional)
{
	int valor_semaforoUm;
	
	valor_semaforoUm = semaforo_getValue(semaforoBidimensional->semaforoUm);
	
	if(valor_semaforoUm == 0)
		semaforo_down(semaforoBidimensional->semaforoMediador);
	
	semaforo_up(semaforoBidimensional->semaforoUm);
}

void semaforoBidimensional_semaforoDois_utilize(SemaforoBidimensional *semaforoBidimensional)
{
	int valor_semaforoDois;
	
	valor_semaforoDois = semaforo_getValue(semaforoBidimensional->semaforoDois);
	
	if(valor_semaforoDois == 0)
		semaforo_down(semaforoBidimensional->semaforoMediador);
	
	semaforo_up(semaforoBidimensional->semaforoDois);
}

void semaforoBidimensional_semaforoUm_terminate(SemaforoBidimensional *semaforoBidimensional)
{
	int valor_semaforoUm;
	
	semaforo_down(semaforoBidimensional->semaforoUm);
	
	valor_semaforoUm = semaforo_getValue(semaforoBidimensional->semaforoUm);
	
	if(valor_semaforoUm == 0)
		semaforo_up(semaforoBidimensional->semaforoMediador);
}

void semaforoBidimensional_semaforoDois_terminate(SemaforoBidimensional *semaforoBidimensional)
{
	int valor_semaforoDois;
	
	semaforo_down(semaforoBidimensional->semaforoDois);
	
	valor_semaforoDois = semaforo_getValue(semaforoBidimensional->semaforoDois);
	
	if(valor_semaforoDois == 0)
		semaforo_up(semaforoBidimensional->semaforoMediador);
}

int semaforoBidimensional_semaforoUm_getValue(SemaforoBidimensional *semaforoBidimensional)
{
	int valor_semaforoUm;
	
	valor_semaforoUm = semaforo_getValue(semaforoBidimensional->semaforoUm);
	
	return valor_semaforoUm;
}

int semaforoBidimensional_semaforoDois_getValue(SemaforoBidimensional *semaforoBidimensional)
{
	int valor_semaforoDois;
	
	valor_semaforoDois = semaforo_getValue(semaforoBidimensional->semaforoDois);
	
	return valor_semaforoDois;
}

int semaforoBidimensional_semaforoMediador_getValue(SemaforoBidimensional *semaforoBidimensional)
{
	int valor_semaforoMediador;
	
	valor_semaforoMediador = semaforo_getValue(semaforoBidimensional->semaforoMediador);
	
	return valor_semaforoMediador;
}




#endif















