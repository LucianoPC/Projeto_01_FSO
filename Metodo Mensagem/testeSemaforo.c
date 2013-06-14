#include <stdio.h>

#include "semaforo.h"

int main()
{
	Semaforo *semaforo = semaforo_create();
	
	int value;
	
	semaforo_up(semaforo);
	semaforo_down(semaforo);
	
	value = semaforo_getValue(semaforo);
	
	printf("\n value: %d\n\n", value);
	
	semaforo_delete(semaforo);
	
	printf("\nOk!\n\n");
	
	return 0;
}
