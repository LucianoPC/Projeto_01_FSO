#ifndef PESSOA_H
#define PESSOA_H

#include <stdlib.h>

typedef struct _Pessoa{
	char *nome;
}Pessoa;

Pessoa * pessoa_create(char *nome)
{
	Pessoa *pessoa = malloc(sizeof(Pessoa));
	pessoa->nome = nome;
	return pessoa;
}

#endif
