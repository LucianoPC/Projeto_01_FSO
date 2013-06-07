#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <stdlib.h>
#include <sys/types.h>
#include <sys/sem.h>


typedef struct _Semaforo{
	int semid;
	key_t key;
}Semaforo;

Semaforo * semaforo_create(){
	Semaforo *semaforo = malloc(sizeof(Semaforo));
}


void criar_semaforo(key_t *key, int *semid)
{
	if( ((*key) = ftok("semaforo.h", 'B')) == -1 )
	{
		perror("ftok");
		exit(-1);
	}
	
	if( ((*semid) = semget((*key), 1, 0666 | IPC_CREAT)) == -1 )
	{
		perror("semget");
		exit(-1);
	}
}

#endif
