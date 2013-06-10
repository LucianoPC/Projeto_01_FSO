#ifndef CRIANCA_H
#define CRIANCA_H

#include <stdlib.h>

#define ESQUERDA 0
#define DIREITA 1

typedef struct _Crianca{
	int numeroProcesso;
	int tempoDecisao;
	int lado;
}Crianca;

Crianca * crianca_create(int numeroProcesso, int tempoDecisao, int lado)
{
	Crianca *crianca = malloc(sizeof(Crianca));
	crianca->numeroProcesso = numeroProcesso;
	crianca->tempoDecisao = tempoDecisao;
	crianca->lado = lado;
	
	return crianca;
}

crianca_delete(Crianca *crianca)
{
	free(crianca);
}

crianca_ESQUERDA()
{
	return ESQUERDA;
}

crianca_DIREITA()
{
	return DIREITA;
}

#endif
