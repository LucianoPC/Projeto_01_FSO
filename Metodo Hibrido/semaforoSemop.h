#ifndef SEMAFOROSEMOP_H
#define SEMAFOROSEMOP_H

#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#include "semaforo.h"

using namespace std;

class SemaforoSemop : public Semaforo
{
public:
	SemaforoSemop(int projeto_identificador);	
	~SemaforoSemop();
	
	void up();
	void down();
	int getValue();

private:
	key_t chave;
	int identificador;

	void criar_chave(int projeto_identificador);
	void criar_identificador();
	void excluir_identificador();
};

SemaforoSemop::SemaforoSemop(int projeto_identificador)
{
	criar_chave(projeto_identificador);
	criar_identificador();
}

SemaforoSemop::~SemaforoSemop()
{
	excluir_identificador();
}

void
SemaforoSemop::up()
{
	struct sembuf semaforo_buffer;
	semaforo_buffer.sem_num = 0;
	semaforo_buffer.sem_op = 1;
	semaforo_buffer.sem_flg = 0;
	
	if(semop(this->identificador, &semaforo_buffer, 1) == -1)
	{
		cout << "Erro ao fazer UP no Semaforo" << endl;
		exit(-1);
	}
}

void
SemaforoSemop::down()
{
	struct sembuf semaforo_buffer;
	semaforo_buffer.sem_num = 0;
	semaforo_buffer.sem_op = -1;
	semaforo_buffer.sem_flg = 0;
	
	if(semop(this->identificador, &semaforo_buffer, 1) == -1)
	{
		cout << "Erro ao fazer DOWN no Semaforo" << endl;
		exit(-1);
	}
}

int
SemaforoSemop::getValue()
{
	int valorSemaforo;
	valorSemaforo = semctl(this->identificador, 0, GETVAL, 0);
	return valorSemaforo;
}


void
SemaforoSemop::criar_chave(int projeto_identificador)
{	
	if( (this->chave = ftok("semaforoSemop.h", projeto_identificador)) == -1 )
	{
		cout << "Erro na Criacao da Chave do Semaforo" << endl;
		exit(-1);
	}
}

void
SemaforoSemop::criar_identificador()
{
	if( (this->identificador = semget(this->chave, 1, 0666 | IPC_CREAT)) == -1 )
	{
		cout << "Erro na Criacao do Identificador do Semaforo" << endl;
		exit(-1);
	}
	semctl(this->identificador, 0, SETVAL, 0);
}

void 
SemaforoSemop::excluir_identificador()
{
	if(semctl(this->identificador, 0, IPC_RMID, 0) == -1)
	{
		cout << "Erro na Exclusao do Identificador do Semaforo" << endl;
		exit(-1);
	}
}

#endif












