#include <stdio.h>
#include <stdlib.h>

#include <stdlib.h>
#include "ponte.h"
#include "pessoa.h"
#include "semaforo.h"

int main()
{
	Ponte *ponte = ponte_create();
	
	Pessoa *pessoa = pessoa_create("Luciano");
	
	printf("\nNome: %s\n", pessoa->nome);
	
	
	
	
	
	printf("\nOk\n\n");

	return 0;
}
