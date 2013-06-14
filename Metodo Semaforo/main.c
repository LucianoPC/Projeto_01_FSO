#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "ponte.h"
#include "crianca.h"

void entrarNaPonte(Ponte *ponte_shared_memory, int segment_id, int numeroCrianca)
{
	int lado = rand() % 2;
	int numeroTravessias = 1 + rand() % 4;
	
	int tempoDecisao = 0;
	
	Crianca *crianca = crianca_create(numeroCrianca, tempoDecisao, lado, numeroTravessias);
	
	while(crianca->numeroTravessias > 0)
	{
		crianca_gerarTempoDeDecisao(crianca, 10);
			
		if(crianca->lado == ESQUERDA)
			ponte_atravessar_esquerdaParaDireita(ponte_shared_memory, crianca, 10);
		else
			ponte_atravessar_direitaParaEsquerda(ponte_shared_memory, crianca, 10);
		
		crianca->numeroTravessias--;
	}
	
}

void gerarProcessosFilhos(int numeroProcessosFilhos, Ponte *ponte_shared_memory, int segment_id)
{
	int indice;
	pid_t child_pid;
	for(indice = 0; indice < numeroProcessosFilhos; indice++)
	{
		if(indice == 0)
		{
			child_pid = fork();
			srand((indice+1) * 13 * time(NULL));
			if(child_pid == 0)
				entrarNaPonte(ponte_shared_memory, segment_id, indice+1);
		}else{
			if(child_pid != 0)
			{
				child_pid = fork();
				srand((indice+1) * 13 * time(NULL));
				if(child_pid == 0)
					entrarNaPonte(ponte_shared_memory, segment_id, indice+1);
			}
		}		
	}
}

void esperarProcessosFilhosTerminarem(int numeroProcessosFilhos)
{
	int indice;
	int child_status;
	for(indice = 0; indice < numeroProcessosFilhos; indice++)
		wait(&child_status);
}

int main()
{
	int numeroProcessosFilhos;
	Ponte *ponte_shared_memory;
	int segment_id;
	pid_t child_pid;
		
	printf("\n Digite o Numero de Criancas para atravessar a Ponte: ");
	scanf("%d", &numeroProcessosFilhos);
	
	if(numeroProcessosFilhos <= 0)
	{
		printf("\nO numero de criancas deve ser maior que zero\n\n");
		ponte_encerrarPonteComMemoriaCompartilhada(ponte_shared_memory, segment_id);
		return -1;
	}
	
	printf("\nCrianca \t NumTravessias \t tempoDecisao \t Lado \t\t Estado\n\n");
	
	ponte_shared_memory = ponte_criarPonteComMemoriaCompartilhada(&segment_id);
	gerarProcessosFilhos(numeroProcessosFilhos, ponte_shared_memory, segment_id);	
	
	if(child_pid != 0)
	{
		esperarProcessosFilhosTerminarem(numeroProcessosFilhos);
		ponte_encerrarPonteComMemoriaCompartilhada(ponte_shared_memory, segment_id);
	}
	
	
	return 0;
}
