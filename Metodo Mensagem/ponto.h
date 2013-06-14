#ifndef PONTO_H
#define PONTO_H

#include <stdlib.h>
#include "filaDeMensagem.h"

#define CAPACIDADE 4

typedef struct _Ponto
{
	FilaDeMensagem *filaDeMensagem;
	int aquisicoes;
}Ponto;

Ponto * ponto_create()
{
	Ponto *ponto = malloc(sizeof(Ponto));
	ponto->filaDeMensagem = filaDeMensagem_create('B');
	ponto->aquisicoes = 0;
	
	return ponto;
}


void ponto_delete(Ponto *ponto)
{
	filaDeMensagem_delete(ponto->filaDeMensagem);
	free(ponto);
}


void enviarMensagem(Ponto *ponto)
{
	filaDeMensagem_enviarMensagem(ponto->filaDeMensagem, "mensagem");
}


void esperarMensagem(Ponto *ponto)
{
	filaDeMensagem_receberMensagem(ponto->filaDeMensagem);
}


void ponto_up(Ponto *ponto)
{
	enviarMensagem(ponto);
}


void ponto_down(Ponto *ponto)
{
	esperarMensagem(ponto);
}


int ponto_getValue(Ponto *ponto)
{
	int value;
	
    value = filaDeMensagem_getNumeroMensagens(ponto->filaDeMensagem);
	
	return value;
}


#endif




































