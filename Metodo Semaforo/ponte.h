#ifndef PONTE_H
#define PONTE_H

#include <stdlib.h>
#include "semaforoBidimensional.h"
#include "crianca.h"

typedef struct _Ponte{
	SemaforoBidimensional *semaforo;
}Ponte;

Ponte * ponte_create(){
	Ponte *ponte = malloc(sizeof(Ponte));
	ponte->semaforo = semaforoBidimensional_create();
	
	return ponte;
}

void ponte_delete(Ponte *ponte)
{
	semaforoBidimensional_delete(ponte->semaforo);
	free(ponte);
}

void ponte_atravessar_esquerdaParaDireita(Ponte *ponte, Crianca *crianca, int tempoTravessia)
{
	printf("%d \t\t %d \t\t %d \t\t %s \t %s\n", crianca->numero, crianca->numeroTravessias, crianca->tempoDecisao, crianca_getLado(crianca), "Esperando");

	sleep(crianca->tempoDecisao);
	semaforoBidimensional_semaforoEsquerda_utilize(ponte->semaforo);
	
	printf("%d \t\t %d \t\t %d \t\t %s \t %s\n", crianca->numero, crianca->numeroTravessias, crianca->tempoDecisao, crianca_getLado(crianca), "Atravessando");
	sleep(tempoTravessia);
		
	semaforoBidimensional_semaforoEsquerda_terminate(ponte->semaforo);
	printf("%d \t\t %d \t\t %d \t\t %s \t %s\n", crianca->numero, crianca->numeroTravessias, crianca->tempoDecisao, crianca_getLado(crianca), "Terminou");
	
	crianca->lado = DIREITA;
}

void ponte_atravessar_direitaParaEsquerda(Ponte *ponte, Crianca *crianca, int tempoTravessia)
{
	printf("%d \t\t %d \t\t %d \t\t %s \t %s\n", crianca->numero, crianca->numeroTravessias, crianca->tempoDecisao, crianca_getLado(crianca), "Esperando");
	
	sleep(crianca->tempoDecisao);
	semaforoBidimensional_semaforoDireita_utilize(ponte->semaforo);
	
	printf("%d \t\t %d \t\t %d \t\t %s \t %s\n", crianca->numero, crianca->numeroTravessias, crianca->tempoDecisao, crianca_getLado(crianca), "Atravessando");
	sleep(tempoTravessia);
	
	
	semaforoBidimensional_semaforoDireita_terminate(ponte->semaforo);
	printf("%d \t\t %d \t\t %d \t\t %s \t %s\n", crianca->numero, crianca->numeroTravessias, crianca->tempoDecisao, crianca_getLado(crianca), "Terminou");
	
	crianca->lado = ESQUERDA;
}

Ponte * ponte_criarPonteComMemoriaCompartilhada(int *segment_id)
{
	Ponte *ponte_shared_memory;
	struct shmid_ds shmbuffer;
	int segment_size;
	const int shared_segment_size = 0x6400;
	
	(*segment_id) = shmget ( IPC_PRIVATE, shared_segment_size, IPC_CREAT |IPC_EXCL |
	S_IRUSR |S_IWUSR );
	
	ponte_shared_memory = shmat ( (*segment_id), 0, 0 );
	
	shmctl ( (*segment_id), IPC_STAT, &shmbuffer );
	segment_size = shmbuffer.shm_segsz;
	
	ponte_shared_memory = ponte_create();
	
	return ponte_shared_memory;
}

void ponte_encerrarPonteComMemoriaCompartilhada(Ponte *ponte_shared_memory, int segment_id)
{
	shmdt ( ponte_shared_memory );
	shmctl ( segment_id, IPC_RMID, NULL );
}


#endif
