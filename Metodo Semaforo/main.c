#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ponte.h"
#include "crianca.h"
#include "semaforo.h"

int main()
{
	Ponte *ponte = ponte_create();
	
	Crianca *crianca = crianca_create(getpid());
	
	printf("\nNome: %d\n", crianca->numeroProcesso);
	
	
	
	ponte_delete(ponte);
	
	free(crianca);
	
	printf("\nOk\n\n");

	return 0;
}
