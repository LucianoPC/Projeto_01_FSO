#ifndef CRIANCA_H
#define CRIANCA_H

#include <stdlib.h>

#define ESQUERDA 0
#define DIREITA 1

typedef struct _Crianca{
	int numero;
	int tempoDecisao;
	int lado;
	int numeroTravessias;
}Crianca;

Crianca * crianca_create(int numero, int tempoDecisao, int lado, int numeroTravessias)
{
	Crianca *crianca = malloc(sizeof(Crianca));
	crianca->numero = numero;
	crianca->tempoDecisao = tempoDecisao;
	crianca->lado = lado;
	crianca->numeroTravessias = numeroTravessias;
	
	return crianca;
}

void crianca_delete(Crianca *crianca)
{
	free(crianca);
}

void crianca_gerarTempoDeDecisao(Crianca *crianca, int tempoMaximo)
{
	crianca->tempoDecisao = rand() % (tempoMaximo + 1);
}

char * crianca_getLado(Crianca *crianca)
{
	//printf("\n\n LADO: %d\n\n", crianca->lado);

	if(crianca->lado == ESQUERDA)
		return "Esquerdo";
	else
		return "Direito";
}

int crianca_ESQUERDA()
{
	return ESQUERDA;
}

int crianca_DIREITA()
{
	return DIREITA;
}

#endif
