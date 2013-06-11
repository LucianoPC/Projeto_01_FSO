#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "ponte.h"
#include "crianca.h"

Ponte * criarPonteComMemoriaCompartilhada(Ponte *ponte_shared_memory, int *segment_id)
{
	struct shmid_ds shmbuffer;
	int segment_size;
	const int shared_segment_size = 0x6400;
	
	(*segment_id) = shmget ( IPC_PRIVATE, shared_segment_size, IPC_CREAT |IPC_EXCL |
	S_IRUSR |S_IWUSR );
	//printf("segment_id: %d\n", (*segment_id));
	
	ponte_shared_memory = shmat ( (*segment_id), 0, 0 );
	//printf ( "Memoria compartilhada conectada no endereco: %p\n", ponte_shared_memory );
	
	shmctl ( (*segment_id), IPC_STAT, &shmbuffer );
	segment_size = shmbuffer.shm_segsz;
	//printf ( "Tamanho do segmento: %d bytes\n", segment_size );
	
	ponte_shared_memory = ponte_create();
	
	return ponte_shared_memory;
}

void encerrarPonteComMemoriaCompartilhada(Ponte *ponte_shared_memory, int segment_id)
{
	shmdt ( ponte_shared_memory );
	
	shmctl ( segment_id, IPC_RMID, NULL );
}

void entrarNaPonte(Ponte *ponte_shared_memory, int segment_id)
{
	//printf ( "\nSegment_ID da Ponte: %d\n", segment_id );
	//printf("\n *****Endereco da Ponte: %p\n", ponte_shared_memory );
	//printf(" *****Valor semaforoEsquerda: %d\n", semaforoBidimensional_semaforoEsquerda_getValue(ponte_shared_memory->semaforo));
	//printf(" *****Valor semaforoDireita: %d\n", semaforoBidimensional_semaforoDireita_getValue(ponte_shared_memory->semaforo));
	//printf(" *****Valor semaforoMediador: %d\n", semaforoBidimensional_semaforoMediador_getValue(ponte_shared_memory->semaforo));
	
	//srand(time(NULL));
	int lado = rand() % 2;
	//srand(time(NULL));
	int numeroTravessias = 1 + rand() % 4;
	
	int tempoDecisao = 0;
	
	Crianca *crianca = crianca_create(getpid(), tempoDecisao, lado, numeroTravessias);
	
	printf("\nCrianca: %d; Lado: %d; Numero de Travessias = %d\n", getpid(), lado, numeroTravessias);
	
	while(crianca->numeroTravessias > 0)
	{
		crianca->tempoDecisao = rand() % 1000;
		
		printf("\nCrianca: %d; Tempo de Decisao: %d\n", getpid(), crianca->tempoDecisao);
		
		usleep(crianca->tempoDecisao);
	
		if(crianca->lado == ESQUERDA)
		{
			//printf("\nCrianca: %d TENTANDO ATRAVESSAR a ponte da Esquerda para Direita\n", getpid());
			ponte_atravessar_esquerdaParaDireita(ponte_shared_memory, crianca, 70);
			crianca->lado = DIREITA;
		}else{
			//printf("\nCrianca: %d TENTANDO ATRAVESSAR a ponte da Direita para Esquerda\n", getpid());
			ponte_atravessar_direitaParaEsquerda(ponte_shared_memory, crianca, 70);
			crianca->lado = ESQUERDA;
		}
		crianca->numeroTravessias--;
	}
	
}

int main()
{
	int numeroCriancas;
	Ponte *ponte_shared_memory;
	int segment_id;
	pid_t child_pid;
	
	int indice = 0;
	
	printf("\n Digite o Numero de Criancas para atravessar a Ponte: ");
	scanf("%d", &numeroCriancas);
		
	ponte_shared_memory = criarPonteComMemoriaCompartilhada(ponte_shared_memory, &segment_id);
	
	//printf("\nponte_shared_memory: %p\n", ponte_shared_memory);
	
	if(numeroCriancas <= 0)
	{
		printf("\nO numero de criancas deve ser maior que zero\n\n");
		encerrarPonteComMemoriaCompartilhada(ponte_shared_memory, segment_id);
		return -1;
	}
	
	printf("Lado = 0: Esquerda;\n");
	printf("Lado = 1: Direita;\n");
		
	for(indice = 0; indice < numeroCriancas; indice++)
	{
		if(indice == 0)
		{
			child_pid = fork();
			srand((indice+1) * 13 * time(NULL));
			//sleep(1);
			if(child_pid == 0)
				entrarNaPonte(ponte_shared_memory, segment_id);
		}else{
			if(child_pid != 0)
			{
				child_pid = fork();
				srand((indice+1) * 13 * time(NULL));
				//sleep(1);
				if(child_pid == 0)
					entrarNaPonte(ponte_shared_memory, segment_id);
			}
		}		
	}
	
	
	if(child_pid != 0)
	{
		int child_status;
		for(indice = 0; indice < numeroCriancas; indice++)
		{
			wait(&child_status);
		}
		
		encerrarPonteComMemoriaCompartilhada(ponte_shared_memory, segment_id);
		
		printf("\n\nOk!\n\n");
	}
	
	
	return 0;
}
