#include "cliente.h"
#include <stdlib.h>
#include <string.h>

Cliente* cria_cliente(int id, char *nome, char *endereco){
	Cliente *f = (Cliente*)malloc(sizeof(Cliente));
	f->id = id;
	strcpy(f->nome, nome);
	strcpy(f->endereco, endereco);
	return f;
}

int recupera_id(Cliente *f){
	return f->id;
}
char* recupera_nome(Cliente *f){
	return f->nome;
}

void destroi_cliente(Cliente *f){
	free(f);
}

