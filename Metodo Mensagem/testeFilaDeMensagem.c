#include <stdio.h>

#include "filaDeMensagem.h"

int main()
{
	FilaDeMensagem *filaDeMensagem = filaDeMensagem_create('B');
	
	enviar_mensagem(filaDeMensagem, "Ola!");
	
	printf("\nMensagem Enviada: Ola!\n");
	
	char *mensagem;
	
	mensagem = receber_mensagem(filaDeMensagem);
	
	printf("\nMensagem Recebida: %s\n", mensagem);
	
	mensagem = receber_mensagem(filaDeMensagem);
	
	filaDeMensagem_delete(filaDeMensagem);
	
	
	printf("\nOk\n\n");
	
	return 0;
}
