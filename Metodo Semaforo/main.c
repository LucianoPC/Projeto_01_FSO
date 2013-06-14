#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "ponte.h"
#include "crianca.h"


void entrarNaPonte(Ponte *ponte_shared, int segment_id, int numeroCrianca)
{
	int lado = rand() % NUMERO_LADOS_NA_PONTE;
	int numeroTravessias = 1 + rand() % LIMITE_DO_NUMERO_TRAVESSIAS;
		
	Crianca *crianca = crianca_create(numeroCrianca, lado, numeroTravessias);
	
	while(crianca_possuiTravessias(crianca))
		ponte_atravessar_crianca(ponte_shared, crianca);
}

void gerarNumerosRandomicosParaOProcesso(int numeroVariavel)
{
	srand((numeroVariavel+1) * 13 * time(NULL));
}

int processoEhFilho(pid_t child_pid)
{
	if(child_pid == 0)
		return 1;
	else
		return 0;
}

pid_t gerarProcessosFilhos(int numeroProcessosFilhos, Ponte *ponte_shared, int segment_id)
{
	int indice;
	pid_t child_pid;
	for(indice = 0; indice < numeroProcessosFilhos; indice++)
	{
		if( (indice == 0) || (!processoEhFilho(child_pid)) )
		{
			child_pid = fork();
			gerarNumerosRandomicosParaOProcesso(indice);
			if(processoEhFilho(child_pid))
				entrarNaPonte(ponte_shared, segment_id, indice+1);
		}	
	}
	
	return child_pid;
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
	Ponte *ponte_shared;
	int segment_id;
	pid_t child_pid;
	int indice;
	int child_status;
	
	printf("\n Digite o Numero de Criancas para atravessar a Ponte: ");
	scanf("%d", &numeroProcessosFilhos);
	
	if(numeroProcessosFilhos <= 0)
	{
		printf("\nO numero de criancas deve ser maior que zero\n\n");
		ponte_delete(ponte_shared);
		return -1;
	}
	
	printf("\nCrianca \t Lado \t\t Estado \t NumTravessias \t tempoDecisao\n\n");
	
	ponte_shared = ponte_create();
	child_pid = gerarProcessosFilhos(numeroProcessosFilhos, ponte_shared, segment_id);	
	
	if(!processoEhFilho(child_pid))
	{
		esperarProcessosFilhosTerminarem(numeroProcessosFilhos);
		ponte_delete(ponte_shared);
	}
	
	
	return 0;
}
