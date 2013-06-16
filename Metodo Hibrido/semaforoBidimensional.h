#ifndef SEMAFOROBIDIMENSIONAL_H
#define SEMAFOROBIDIMENSIONAL_H

#include <stdlib.h>
#include "semaforoSemop.h"
#include "semaforoMensagem.h"

#define SEMAFORO_SEMOP 0
#define SEMAFORO_MENSAGEM 1

class SemaforoBidimensional
{
public:
	SemaforoBidimensional(int tipoDeSemaforo);
	~SemaforoBidimensional();
	
	void semaforoEsquerda_utilize();
	void semaforoDireita_utilize();
	
	void semaforoEsquerda_terminate();
	void semaforoDireita_terminate();
	
	int semaforoEsquerda_getValue();
	int semaforoDireita_getValue();
	int semaforoMediador_getValue();
	
private:
	void criar_semaforos(int tipoDeSemaforo);
	void criar_semaforos_semop();
	void criar_semaforos_mensagem();
	
	Semaforo *semaforoEsquerda;
	Semaforo *semaforoDireita;
	Semaforo *semaforoMediador;
};

SemaforoBidimensional::SemaforoBidimensional(int tipoDeSemaforo)
{
	criar_semaforos(tipoDeSemaforo);
	semaforoMediador->up();
}

SemaforoBidimensional::~SemaforoBidimensional()
{
	delete semaforoEsquerda;
	delete semaforoDireita;
	delete semaforoMediador;
}


void 
SemaforoBidimensional::semaforoEsquerda_utilize()
{
	if(semaforoEsquerda->getValue() == 0)
		semaforoMediador->down();
	
	semaforoEsquerda->up();
}

void 
SemaforoBidimensional::semaforoDireita_utilize()
{
	if(semaforoDireita->getValue() == 0)
		semaforoMediador->down();
	
	semaforoDireita->up();
}

void 
SemaforoBidimensional::semaforoEsquerda_terminate()
{
	semaforoEsquerda->down();
	
	if(semaforoEsquerda->getValue() == 0)
		semaforoMediador->up();
}

void 
SemaforoBidimensional::semaforoDireita_terminate()
{
	semaforoDireita->down();
	
	if(semaforoDireita->getValue() == 0)
		semaforoMediador->up();
}

int
SemaforoBidimensional::semaforoEsquerda_getValue()
{
	return semaforoEsquerda->getValue();
}

int
SemaforoBidimensional::semaforoDireita_getValue()
{
	return semaforoDireita->getValue();
}

int
SemaforoBidimensional::semaforoMediador_getValue()
{
	return semaforoMediador->getValue();
}



void 
SemaforoBidimensional::criar_semaforos(int tipoDeSemaforo)
{
	if(tipoDeSemaforo == SEMAFORO_SEMOP)
		criar_semaforos_semop();
	else
		criar_semaforos_mensagem();
}

void 
SemaforoBidimensional::criar_semaforos_semop()
{
	semaforoEsquerda = new SemaforoSemop('A');
	semaforoDireita = new SemaforoSemop('B');
	semaforoMediador = new SemaforoSemop('C');
}

void 
SemaforoBidimensional::criar_semaforos_mensagem()
{
	semaforoEsquerda = new SemaforoMensagem('A');
	semaforoDireita = new SemaforoMensagem('B');
	semaforoMediador = new SemaforoMensagem('C');
}


#endif


















