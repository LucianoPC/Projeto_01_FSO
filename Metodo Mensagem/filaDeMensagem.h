#ifndef FILADEMENSAGEM_H
#define FILADEMENSAGEM_H	


#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define TAMANHO_MENSAGEM 50

struct my_msgbuf
{
	long mtype;
	char mtext[TAMANHO_MENSAGEM];
};

typedef struct _FilaDeMensagem
{
	struct my_msgbuf buffer;
	int identificador;
	key_t chave;
}FilaDeMensagem;


FilaDeMensagem * filaDeMensagem_create(int projeto_identificador)
{
	FilaDeMensagem *filaDeMensagem = malloc(sizeof(FilaDeMensagem));
	filaDeMensagem->chave = criar_chave(projeto_identificador);
	filaDeMensagem->identificador = criar_identificador(filaDeMensagem->chave);
	
	return filaDeMensagem;
}

void excluir_identificador(int identificador)
{
	if( msgctl( identificador, IPC_RMID, NULL ) == -1 )
	{
		perror("msgctl");
		exit(1);
	}
}

void filaDeMensagem_delete(FilaDeMensagem *filaDeMensagem)
{
	excluir_identificador(filaDeMensagem->identificador);
	free(filaDeMensagem);
}


key_t criar_chave(int projeto_identificador)
{
	key_t chave;
	
	if( ( chave = ftok( "filaDeMensagem.h", projeto_identificador ) ) == -1 )
	{
		perror("ftok");
		exit(1);
	}
	
	return chave;
}


int criar_identificador(key_t chave)
{
	int identificador;
	
	if( ( identificador = msgget( chave, 0644 | IPC_CREAT ) ) == -1 )
	{
		perror("ftok");
		exit(1);
	}
	
	return identificador;
}


void filaDeMensagem_enviarMensagem(FilaDeMensagem *filaDeMensagem, char mensagem[TAMANHO_MENSAGEM])
{
	strcpy(filaDeMensagem->buffer.mtext, mensagem);
	
	struct my_msgbuf buf = filaDeMensagem->buffer;
	
	buf.mtype = 1;
	
	if( msgsnd( filaDeMensagem->identificador, (struct msgbuf *) &buf, sizeof(buf), 0 ) == -1 )
	{
		fprintf( stderr, "Erro no envio da mensagem.\n" );
		exit(-1);
	}
}


char * filaDeMensagem_receberMensagem(FilaDeMensagem *filaDeMensagem)
{
	struct my_msgbuf buf = filaDeMensagem->buffer;
	int identificador = filaDeMensagem->identificador;

	if( msgrcv( filaDeMensagem->identificador, (struct msgbuf *) &buf, sizeof(buf), 0, 0 ) == -1 )
	{
		fprintf( stderr, "Erro ao receber mensagem.\n" );
		exit(1);
	}
	
	filaDeMensagem->identificador = identificador;
	
	return filaDeMensagem->buffer.mtext;
}

int filaDeMensagem_getNumeroMensagens(FilaDeMensagem *filaDeMensagem)
{
	struct msqid_ds buf;
	int numeroMensagens;
	
	if(msgctl(filaDeMensagem->identificador, IPC_STAT, &buf) == -1){
      perror("msgctl");
      exit(-1);
    }
    
    numeroMensagens = buf.msg_qnum;
    
    return numeroMensagens;
}




































#endif
