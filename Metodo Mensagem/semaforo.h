#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <stdlib.h>
#include "filaDeMensagem.h"

#define CAPACIDADE 4

typedef struct _Semaforo
{
	FilaDeMensagem *filaDeMensagem;
	int aquisicoes;
}Semaforo;

Semaforo * semaforo_create()
{
	Semaforo *semaforo = malloc(sizeof(Semaforo));
	semaforo->filaDeMensagem = filaDeMensagem_create('B');
	semaforo->aquisicoes = 0;
	
	return semaforo;
}


void semaforo_delete(Semaforo *semaforo)
{
	filaDeMensagem_delete(semaforo->filaDeMensagem);
	free(semaforo);
}


void enviarMensagem(Semaforo *semaforo)
{
	filaDeMensagem_enviarMensagem(semaforo->filaDeMensagem, "mensagem");
}


void esperarMensagem(Semaforo *semaforo)
{
	filaDeMensagem_receberMensagem(semaforo->filaDeMensagem);
}


void semaforo_up(Semaforo *semaforo)
{
	enviarMensagem(semaforo);
}


void semaforo_down(Semaforo *semaforo)
{
	esperarMensagem(semaforo);
}


int semaforo_getValue(Semaforo *semaforo)
{
	int value;
	
    value = filaDeMensagem_getNumeroMensagens(semaforo->filaDeMensagem);
	
	return value;
}


#endif




































