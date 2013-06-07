#ifndef PESSOA_H
#define PESSOA_H

#include <stdlib.h>

#define ATRAVESSANDO 1
#define NAO_ATRAVESSANDO 0

typedef struct _Pessoa{
	char *nome;
	int atravessando;
}Pessoa;

Pessoa * pessoa_create(char *nome)
{
	Pessoa *pessoa = malloc(sizeof(Pessoa));
	pessoa->nome = nome;
	pessoa->atravessando = ATRAVESSANDO;
	return pessoa;
}

#endif
