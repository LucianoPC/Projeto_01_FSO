#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "ponte.h"
#include "crianca.h"

void criarPonteComMemoriaCompartilhada(Ponte *ponte_shared_memory, int *segment_id)
{
	struct shmid_ds shmbuffer;
	int segment_size;
	const int shared_segment_size = 0x6400;
	
	(*segment_id) = shmget ( IPC_PRIVATE, shared_segment_size, IPC_CREAT |IPC_EXCL |
	S_IRUSR |S_IWUSR );
	printf("segment_id: %d\n", (*segment_id));
	
	ponte_shared_memory = shmat ( (*segment_id), 0, 0 );
	printf ( "Memoria compartilhada conectada no endereco: %p\n", ponte_shared_memory );
	
	shmctl ( (*segment_id), IPC_STAT, &shmbuffer );
	segment_size = shmbuffer.shm_segsz;
	printf ( "Tamanho do segmento: %d bytes\n", segment_size );
	
	ponte_shared_memory = ponte_create();
}

void encerrarPonteComMemoriaCompartilhada(Ponte *ponte_shared_memory, int segment_id)
{
	shmdt ( ponte_shared_memory );
	
	shmctl ( segment_id, IPC_RMID, NULL );
}

int main()
{
	int numeroCriancas;
	Ponte *ponte_shared_memory;
	int segment_id;
	pid_t *filho_pid;
	
	int indice = 0;
	filho_pid = malloc(numeroCriancas * sizeof(pid_t));
	
	scanf("%d", &numeroCriancas);
	
	
	criarPonteComMemoriaCompartilhada(ponte_shared_memory, &segment_id);
	
	if(numeroCriancas <= 0)
	{
		printf("\nO numero de criancas deve ser maior que zero\n\n");
		encerrarPonteComMemoriaCompartilhada(ponte_shared_memory, segment_id);
		return -1;
	}
	
	filho_pid[0] = fork();
	if(filho_pid[0] == 0)
		printf("Processo filho numero: %d\n", indice+1);
	for(indice = 1; indice < numeroCriancas; indice++)
	{
		if(filho_pid[indice-1] != 0)
		{
			filho_pid[indice] = fork();
		}else{
			printf("Processo filho numero: %d\n", indice+1);
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	printf("\nOk!\n\n");
	
	return 0;
}
