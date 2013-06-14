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

Crianca * crianca_create(int numero, int lado, int numeroTravessias)
{
	Crianca *crianca = malloc(sizeof(Crianca));
	crianca->numero = numero;
	crianca->lado = lado;
	crianca->numeroTravessias = numeroTravessias;
	crianca->tempoDecisao = 0;
	
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
	if(crianca->lado == ESQUERDA)
		return "Esquerdo";
	else
		return "Direito";
}

int crianca_possuiTravessias(Crianca *crianca)
{
	if(crianca->numeroTravessias > 0)
		return 1;
	else
		return 0;
}

void crianca_mudarLado(Crianca *crianca)
{
	if(crianca->lado == ESQUERDA)
		crianca->lado = DIREITA;
	else
		crianca->lado = ESQUERDA;
}

void crianca_decrementarNumeroTravessias(Crianca *crianca)
{
	if(crianca->numeroTravessias > 0)
		crianca->numeroTravessias--;
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
