#ifndef FILADEMENSAGEM_H
#define FILADEMENSAGEM_H	


#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace std;

#define TAMANHO_MENSAGEM 50

struct my_msgbuf
{
	long mtype;
	char mtext[TAMANHO_MENSAGEM];
};

class FilaDeMensagem
{
public:
	FilaDeMensagem(int projeto_identificador);
	~FilaDeMensagem();
	
	void enviarMensagem(char mensagem[TAMANHO_MENSAGEM]);
	char * receberMensagem();
	int getNumeroMensagens();
private:
	struct my_msgbuf buffer;
	int identificador;
	key_t chave;
	
	void criar_chave(int projeto_identificador);
	void criar_identificador();
	void excluir_identificador();
};

FilaDeMensagem::FilaDeMensagem(int projeto_identificador)
{
	criar_chave(projeto_identificador);
	criar_identificador();
}

FilaDeMensagem::~FilaDeMensagem()
{
	excluir_identificador();
}


void 
FilaDeMensagem::enviarMensagem(char mensagem[TAMANHO_MENSAGEM])
{
	strcpy(this->buffer.mtext, mensagem);
	
	struct my_msgbuf buf = this->buffer;
	
	buf.mtype = 1;
	
	if( msgsnd( this->identificador, (struct msgbuf *) &buf, sizeof(buf), 0 ) == -1 )
	{
		cout << "Erro no envio da mensagem." << endl;
		exit(-1);
	}
}

char * 
FilaDeMensagem::receberMensagem()
{
	struct my_msgbuf buf = this->buffer;
	int identificador = this->identificador;

	if( msgrcv( this->identificador, (struct msgbuf *) &buf, sizeof(buf), 0, 0 ) == -1 )
	{
		cout << "Erro ao receber mensagem.\n" << endl;
		exit(1);
	}
	
	this->identificador = identificador;
	
	return this->buffer.mtext;
}

int 
FilaDeMensagem::getNumeroMensagens()
{
	struct msqid_ds buf;
	int numeroMensagens;
	
	if(msgctl(this->identificador, IPC_STAT, &buf) == -1){
      cout << "Erro ao Identificar o Numero de Mensagens.\n" << endl;
      exit(-1);
    }
    
    numeroMensagens = buf.msg_qnum;
    
    return numeroMensagens;
}


void
FilaDeMensagem::criar_chave(int projeto_identificador)
{	
	if( (this->chave = ftok("filaDeMensagem.h", projeto_identificador)) == -1 )
	{
		cout << "Erro na Criacao da Chave da Fila de Mensagem" << endl;
		exit(-1);
	}
}

void 
FilaDeMensagem::criar_identificador()
{
	if( ( this->identificador = msgget( this->chave, 0644 | IPC_CREAT ) ) == -1 )
	{
		cout << "Erro na Criacao do Identificador da Fila de Mensagem" << endl;
		exit(1);
	}
}

void 
FilaDeMensagem::excluir_identificador()
{
	if( msgctl( this->identificador, IPC_RMID, NULL ) == -1 )
	{
		cout << "Erro na Exclusao do Identificador da Fila de Mensagem" << endl;
		exit(1);
	}
}

#endif

















