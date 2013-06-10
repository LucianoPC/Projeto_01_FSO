#include <stdio.h>
#include "semaforoBidimensional.h"

void imprimirIdentificadores(SemaforoBidimensional *semaforo)
{
	int id_semaforoEsquerda;
	int id_semaforoDireita;
	int id_semaforoMediador;
	
	id_semaforoEsquerda = semaforo->semaforoEsquerda->identificador;
	id_semaforoDireita = semaforo->semaforoDireita->identificador;
	id_semaforoMediador = semaforo->semaforoMediador->identificador;
	
	printf("ID semaforoEsquerda: %d\n", id_semaforoEsquerda);
	printf("ID semaforoDireita: %d\n", id_semaforoDireita);
	printf("ID semaforoMediador: %d\n", id_semaforoMediador);
}

void imprimirValores(SemaforoBidimensional *semaforo)
{
	int valor_semaforoEsquerda;
	int valor_semaforoDireita;
	int valor_semaforoMediador;
	
	valor_semaforoEsquerda = semaforoBidimensional_semaforoEsquerda_getValue(semaforo);
	valor_semaforoDireita = semaforoBidimensional_semaforoDireita_getValue(semaforo);
	valor_semaforoMediador = semaforoBidimensional_semaforoMediador_getValue(semaforo);
	
	printf("valor_semaforoEsquerda: %d\n", valor_semaforoEsquerda);
	printf("valor_semaforoDireita: %d\n", valor_semaforoDireita);
	printf("valor_semaforoMediador: %d\n", valor_semaforoMediador);
}

int main()
{
	SemaforoBidimensional *semaforo = semaforoBidimensional_create();
	
	imprimirIdentificadores(semaforo);
	printf("\n");
	imprimirValores(semaforo);
	
	
	semaforoBidimensional_semaforoEsquerda_utilize(semaforo);
	semaforoBidimensional_semaforoEsquerda_terminate(semaforo);
	semaforoBidimensional_semaforoDireita_utilize(semaforo);
	printf("\n");
	imprimirValores(semaforo);
	
	
	semaforoBidimensional_delete(semaforo);
	
	
	
	printf("\nOk!\n\n");
	
	return 0;
}
