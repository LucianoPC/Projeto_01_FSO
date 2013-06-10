#ifndef CRIANCA_H
#define CRIANCA_H

#include <stdlib.h>

#define ATRAVESSANDO 1
#define NAO_ATRAVESSANDO 0

typedef struct _Crianca{
	int numeroProcesso;
}Crianca;

Crianca * crianca_create(int numeroProcesso)
{
	Crianca *crianca = malloc(sizeof(Crianca));
	crianca->numeroProcesso = numeroProcesso;
	return crianca;
}

#endif
