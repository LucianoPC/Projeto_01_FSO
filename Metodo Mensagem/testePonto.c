#include <stdio.h>

#include "ponto.h"

int main()
{
	Ponto *ponto = ponto_create();
	
	int value;
	
	ponto_up(ponto);
	ponto_down(ponto);
	ponto_down(ponto);
	
	value = ponto_getValue(ponto);
	
	printf("\n value: %d\n\n", value);
	
	ponto_delete(ponto);
	
	printf("\nOk!\n\n");
	
	return 0;
}
