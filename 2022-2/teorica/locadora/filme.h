#ifndef FILME_H
#define FILME_H

typedef struct {
	int id; 
	char nome[100];
	int ano;
	int duracao;
} Filme;

Filme* cria_filme(int id, char *nome, int ano, int duracao);
int recupera_id(Filme *f);
char* recupera_nome(Filme *f);
void destroi_filme(Filme *f);

#endif
