#include "filme.h"
#include <stdlib.h>
#include <string.h>

Filme* cria_filme(int id, char *nome, int ano, int duracao){
	Filme *f = (Filme*)malloc(sizeof(Filme));
	f->id = id;
	strcpy(f->nome, nome);
	f->ano = ano;
	f->duracao = duracao;
	return f;
}

int recupera_id(Filme *f){
	return f->id;
}
char* recupera_nome(Filme *f){
	return f->nome;
}

void destroi_filme(Filme *f){
	free(f);
}

