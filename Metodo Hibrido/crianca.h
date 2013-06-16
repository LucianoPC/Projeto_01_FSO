#ifndef CRIANCA_H
#define CRIANCA_H

#define ESQUERDA 0
#define DIREITA 1

class Crianca
{
public:
	Crianca(int numero, int lado, int numeroTravessias);
	
	int getNumero();
	int getTempoDecisao();
	char * getLado();
	int getLadoInt();
	int getNumeroTravessias();
	
	void mudarLado();
	
	void gerarTempoDeDecisao(int tempoMaximo);
	
	int possuiTravessias();
	void decrementarNumeroTravessias();

private:
	int numero;
	int tempoDecisao;
	int lado;
	int numeroTravessias;
};


Crianca::Crianca(int numero, int lado, int numeroTravessias)
{
	this->numero = numero;
	this->lado = lado;
	this->numeroTravessias = numeroTravessias;
	this->tempoDecisao = 0;
}


int 
Crianca::getNumero()
{
	return numero;
}

int 
Crianca::getTempoDecisao()
{
	return tempoDecisao;
}

int 
Crianca::getNumeroTravessias()
{
	return numeroTravessias;
}

int 
Crianca::getLadoInt()
{
	return lado;
}


char *  
Crianca::getLado()
{
	if(lado == ESQUERDA)
		return (char *)"Esquerdo";
	else
		return (char *)"Direito";
}

void  
Crianca::mudarLado()
{
	if(lado == ESQUERDA)
		lado = DIREITA;
	else
		lado = ESQUERDA;
}

void 
Crianca::gerarTempoDeDecisao(int tempoMaximo)
{
	tempoDecisao = rand() % (tempoMaximo + 1);
}

int 
Crianca::possuiTravessias()
{
	if(numeroTravessias > 0)
		return 1;
	else
		return 0;
}

void 
Crianca::decrementarNumeroTravessias()
{
	if(numeroTravessias > 0)
		numeroTravessias--;
}

















#endif


























