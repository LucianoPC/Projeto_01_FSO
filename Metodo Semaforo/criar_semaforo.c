#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>

#include "semaforo.h"

int main()
{
	int valor;
	Semaforo *semaforo = semaforo_create('B');
	
	semaforo_up(semaforo);
	
	valor = semaforo_getValue(semaforo);
	
	printf("semaforo->identificador: %d\n", semaforo->identificador);
	printf("valor: %d\n", valor);
	
	
	semaforo_delete(semaforo);
	
	printf("\nOk!\n\n");

	return 0;
}
