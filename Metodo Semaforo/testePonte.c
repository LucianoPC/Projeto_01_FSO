#include <stdio.h>
#include "ponte.h"

int main()
{
	Ponte *ponte = ponte_create();
	
	Crianca *criancaUm = crianca_create(1, 70, 1, 3);
	Crianca *criancaDois = crianca_create(2, 70, 0, 2);
	Crianca *criancaTres = crianca_create(3, 70, 0, 2);
	
	printf("\nCrianca 01 atravessando a ponte da Esquerda para Direita.\n");
	ponte_atravessar_esquerdaParaDireita(ponte, criancaUm, 70);
	printf("Crianca 01 atravessou a ponte.\n");
	
	printf("\nCrianca 02 atravessando a ponte da Dreita para Esquerda.\n");
	ponte_atravessar_direitaParaEsquerda(ponte, criancaDois, 70);
	printf("Crianca 02 atravessou a ponte.\n");
	
	printf("\nCrianca 03 atravessando a ponte da Dreita para Esquerda.\n");
	ponte_atravessar_direitaParaEsquerda(ponte, criancaTres, 70);
	printf("Crianca 03 atravessou a ponte.\n");
	
	ponte_delete(ponte);
	
		
	printf("\nOk!\n\n");
	
	return 0;
}
