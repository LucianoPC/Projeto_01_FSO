#include <stdio.h>
#include "semaforoBidimensional.h"

void imprimirIdentificadores(SemaforoBidimensional *semaforo)
{
	int id_semaforoUm;
	int id_semaforoDois;
	int id_semaforoMediador;
	
	id_semaforoUm = semaforo->semaforoUm->identificador;
	id_semaforoDois = semaforo->semaforoDois->identificador;
	id_semaforoMediador = semaforo->semaforoMediador->identificador;
	
	printf("ID semaforoUm: %d\n", id_semaforoUm);
	printf("ID semaforoDois: %d\n", id_semaforoDois);
	printf("ID semaforoMediador: %d\n", id_semaforoMediador);
}

void imprimirValores(SemaforoBidimensional *semaforo)
{
	int valor_semaforoUm;
	int valor_semaforoDois;
	int valor_semaforoMediador;
	
	valor_semaforoUm = semaforoBidimensional_semaforoUm_getValue(semaforo);
	valor_semaforoDois = semaforoBidimensional_semaforoDois_getValue(semaforo);
	valor_semaforoMediador = semaforoBidimensional_semaforoMediador_getValue(semaforo);
	
	printf("valor_semaforoUm: %d\n", valor_semaforoUm);
	printf("valor_semaforoDois: %d\n", valor_semaforoDois);
	printf("valor_semaforoMediador: %d\n", valor_semaforoMediador);
}

int main()
{
	SemaforoBidimensional *semaforo = semaforoBidimensional_create();
	
	imprimirIdentificadores(semaforo);
	printf("\n");
	imprimirValores(semaforo);
	
	
	semaforoBidimensional_semaforoUm_utilize(semaforo);
	semaforoBidimensional_semaforoUm_terminate(semaforo);
	semaforoBidimensional_semaforoDois_utilize(semaforo);
	printf("\n");
	imprimirValores(semaforo);
	
	
	semaforoBidimensional_delete(semaforo);
	
	
	
	printf("\nOk!\n\n");
	
	return 0;
}
