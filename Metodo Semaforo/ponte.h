#ifndef PONTE_H
#define PONTE_H

#include <stdlib.h>
#include "semaforo.h"
#include "pessoa.h"

typedef struct _Ponte{
	Semaforo *semaforo;
}Ponte;

Ponte * ponte_create(){
	Ponte *ponte = malloc(sizeof(Ponte));
	ponte->semaforo = semaforo_create('P');
	
	semaforo_up(ponte->semaforo);
	
	return ponte;
}

void ponte_delete(Ponte *ponte)
{
	semaforo_delete(ponte->semaforo);
	free(ponte);
}

void ponte_atravessar(Ponte *ponte, Pessoa *pessoa, int tempo_travessia)
{
	iniciar_Travessia(ponte, pessoa);
	sleep(tempo_travessia);
	terminar_Travessia(ponte, pessoa);
}

void iniciar_Travessia(Ponte *ponte, Pessoa *pessoa)
{
	semaforo_down(ponte->semaforo);
	pessoa->atravessando = ATRAVESSANDO;
}

void terminar_Travessia(Ponte *ponte, Pessoa *pessoa)
{
	semaforo_up(ponte->semaforo);
	pessoa->atravessando = NAO_ATRAVESSANDO;
}




#endif
