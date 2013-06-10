#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <stdlib.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

typedef struct _Semaforo{
	int identificador;
	key_t chave;
}Semaforo;

Semaforo * semaforo_create(int projeto_identificador){
	Semaforo *semaforo = malloc(sizeof(Semaforo));
	
	semaforo->chave = criar_chave(projeto_identificador);
	semaforo->identificador = criar_identificador(semaforo->chave);
	
	return semaforo;
}

void semaforo_delete(Semaforo *semaforo)
{
	if(semctl(semaforo->identificador, 0, IPC_RMID, 0) == -1)
	{
		perror("semctl");
		exit(-1);
	}
	
	free(semaforo);
}

void semaforo_up(Semaforo *semaforo)
{
	struct sembuf semaforo_buffer;
	semaforo_buffer.sem_num = 0;
	semaforo_buffer.sem_op = 1;
	semaforo_buffer.sem_flg = 0;
	
	if(semop(semaforo->identificador, &semaforo_buffer, 1) == -1)
	{
		perror("semop");
		exit(-1);
	}
}

void semaforo_down(Semaforo *semaforo)
{
	struct sembuf semaforo_buffer;
	semaforo_buffer.sem_num = 0;
	semaforo_buffer.sem_op = -1;
	semaforo_buffer.sem_flg = 0;
	
	if(semop(semaforo->identificador, &semaforo_buffer, 1) == -1)
	{
		perror("semop");
		exit(-1);
	}
}

int semaforo_getValue(Semaforo *semaforo)
{
	int valorSemaforo;
	valorSemaforo = semctl(semaforo->identificador, 0, GETVAL, 0);
	return valorSemaforo;
}

key_t criar_chave(int projeto_identificador)
{
	key_t chave;
	
	if( (chave = ftok("semaforo.h", projeto_identificador)) == -1 )
	{
		perror("ftok");
		exit(-1);
	}
	
	return chave;
}

int criar_identificador(key_t chave)
{
	int semaforo_id;
	
	if( (semaforo_id = semget(chave, 1, 0666 | IPC_CREAT)) == -1 )
	{
		perror("semget");
		exit(-1);
	}
	
	return semaforo_id;
}





#endif
