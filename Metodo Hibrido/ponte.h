#ifndef PONTE_H
#define PONTE_H

#include <stdio.h>
#include <unistd.h>
#include "semaforoBidimensional.h"
#include "crianca.h"


class Ponte
{
public:
	Ponte(int tipoDeSemaforo);
	~Ponte();
	
	void imprimirMensagem_estadoCriancaNaPonte(Crianca *crianca, char *estado);
	void atravessarCrianca_daEsquerdaParaDireita(Crianca *crianca, int tempoTravessia);
	void atravessarCrianca_daDireitaParaEsquerda(Crianca *crianca, int tempoTravessia);
	
private:
	SemaforoBidimensional *semaforoBidimensional;
};


Ponte::Ponte(int tipoDeSemaforo)
{
	semaforoBidimensional = new SemaforoBidimensional(tipoDeSemaforo);
}

Ponte::~Ponte()
{
	delete semaforoBidimensional;
}



void 
Ponte::imprimirMensagem_estadoCriancaNaPonte(Crianca *crianca, char *estado)
{
	printf("%d \t\t %s \t %s \t %d \t\t %d\n", crianca->getNumero(), crianca->getLado(), estado, crianca->getNumeroTravessias(), crianca->getTempoDecisao());
}


void 
Ponte::atravessarCrianca_daEsquerdaParaDireita(Crianca *crianca, int tempoTravessia)
{
	imprimirMensagem_estadoCriancaNaPonte(crianca, (char *)"Esperando");

	usleep(crianca->getTempoDecisao());
	semaforoBidimensional->semaforoEsquerda_utilize();
	
	imprimirMensagem_estadoCriancaNaPonte(crianca, (char *)"Atravessando");
	
	usleep(tempoTravessia);
	semaforoBidimensional->semaforoEsquerda_terminate();
	
	imprimirMensagem_estadoCriancaNaPonte(crianca, (char *)"Terminou");
	
	crianca->mudarLado();
}


void 
Ponte::atravessarCrianca_daDireitaParaEsquerda(Crianca *crianca, int tempoTravessia)
{
	imprimirMensagem_estadoCriancaNaPonte(crianca, (char *)"Esperando");
	usleep(crianca->getTempoDecisao());
	
	semaforoBidimensional->semaforoDireita_utilize();
	
	imprimirMensagem_estadoCriancaNaPonte(crianca, (char *)"Atravessando");
	usleep(tempoTravessia);
	
	semaforoBidimensional->semaforoDireita_terminate();
	
	imprimirMensagem_estadoCriancaNaPonte(crianca, (char *)"Terminou");
	
	crianca->mudarLado();
}








#endif



















































