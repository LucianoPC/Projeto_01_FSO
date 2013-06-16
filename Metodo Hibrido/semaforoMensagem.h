#ifndef SEMAFOROMENSAGEM_H
#define SEMAFOROMENSAGEM_H

#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#include "semaforo.h"
#include "filaDeMensagem.h"

using namespace std;

class SemaforoMensagem : public Semaforo
{
public:
	SemaforoMensagem(int projeto_identificador);	
	~SemaforoMensagem();
	
	void up();
	void down();
	int getValue();

private:
	FilaDeMensagem *filaDeMensagem;
	void enviarMensagem();
	void receberMensagem();
};

SemaforoMensagem::SemaforoMensagem(int projeto_identificador)
{
	filaDeMensagem = new FilaDeMensagem(projeto_identificador);
}

SemaforoMensagem::~SemaforoMensagem()
{
	delete filaDeMensagem;
}

void
SemaforoMensagem::up()
{
	enviarMensagem();
}

void
SemaforoMensagem::down()
{
	receberMensagem();
}

int
SemaforoMensagem::getValue()
{
	int value;
    value = filaDeMensagem->getNumeroMensagens();
	return value;
}


void 
SemaforoMensagem::enviarMensagem()
{
	this->filaDeMensagem->enviarMensagem((char *)"mensagem");
}

void 
SemaforoMensagem::receberMensagem()
{
	this->filaDeMensagem->receberMensagem();
}

#endif












