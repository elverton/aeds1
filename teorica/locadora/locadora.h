#ifndef LOCADORA_H
#define LOCADORA_H

#include "filme.h"
#include "cliente.h"

typedef struct {
	int id_cliente;
	int id_filme;
} Locacao;

typedef struct {
	Filme *filmes;
	Cliente *clientes;
	Locacao *locacoes;
	int num_filmes;
	int num_clientes;
	int num_locacoes;
} Locadora;

Locadora* cria_locadora(int max_filmes, int max_clientes, int max_locacoes);
void insere_cliente(Locadora *l, char *nome, char *endereco);
void insere_filme(Locadora *l, char *nome, int ano, int duracao);
void locacao(Locadora *l, int id_filme, int id_cliente);
void devolucao(Locadora *l, int id_filme);
void exibe_filmes(Locadora *l);
void exibe_clientes(Locadora *l);
void exibe_locacoes(Locadora *l);
void destroi_locadora(Locadora *l);

#endif
