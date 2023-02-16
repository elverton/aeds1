#include "locadora.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Locadora* cria_locadora(int max_filmes, int max_clientes, int max_locacoes){
	Locadora *l = (Locadora*)malloc(sizeof(Locadora));
	l->filmes = (Filme*)malloc(max_filmes*sizeof(Filme));
	l->clientes = (Cliente*)malloc(max_clientes*sizeof(Cliente));
	l->locacoes = (Locacao*)malloc(max_locacoes*sizeof(Locacao));
	for(int i=0; i<max_locacoes; i++){
        l->locacoes[i].id_cliente = -1;
        l->locacoes[i].id_filme = -1;
    }
    l->num_filmes = 0;
	l->num_clientes = 0;
	l->num_locacoes = 0;
	return l;
}

void insere_cliente(Locadora *l, int id, char *nome, char *endereco){
	l->clientes[l->num_clientes].id = id;
	strcpy(l->clientes[l->num_clientes].nome, nome);
	strcpy(l->clientes[l->num_clientes].endereco, endereco);
	l->num_clientes++;
}

void insere_filme(Locadora *l, int id, char *nome, int ano, int duracao){
	l->filmes[l->num_filmes].id = id;
	strcpy(l->filmes[l->num_filmes].nome, nome);
	l->filmes[l->num_filmes].ano = ano;
	l->filmes[l->num_filmes].duracao = duracao;
	l->num_filmes++;
}

void locacao(Locadora *l, int id_filme, int id_cliente){
	int idx = 0;
	while(1){
		if(l->locacoes[idx].id_filme != -1){
			idx++;
			continue;
		}
		l->locacoes[idx].id_filme = id_filme;
		l->locacoes[idx].id_cliente = id_cliente;
		break;
	}
}

void devolucao(Locadora *l, int id_filme){
	int idx = 0;
	while(1){
		if(l->locacoes[idx].id_filme != id_filme){
			idx++;
			continue;
		}
		l->locacoes[idx].id_filme = -1;
		l->locacoes[idx].id_cliente = -1;
		break;
	}
	l->num_locacoes--;
}

void exibe_filmes(Locadora *l){
	printf("--------- Filmes ---------\n");
	for(int i=0; i<l->num_filmes; i++){
		printf("%5d -- %s", l->filmes[i].id, l->filmes[i].nome);
	}
	printf("--------------------------\n");
}

void exibe_clientes(Locadora *l){
	printf("--------- Clientes ---------\n");
	for(int i=0; i<l->num_clientes; i++){
		printf("%5d -- %s", l->clientes[i].id, l->clientes[i].nome);
	}
	printf("--------------------------\n");
}

void exibe_locacoes(Locadora *l){
	int idx = 0;
	int num_loc = 0;
	while(num_loc < l->num_locacoes){
		if(l->locacoes[idx].id_filme == -1){
			idx++;
		}
		printf("%d %d", l->locacoes[idx].id_filme, 
				l->locacoes[idx].id_cliente);
		idx++;
		num_loc++;
	}
}

void destroi_locadora(Locadora *l){
	free(l->filmes);
	free(l->clientes);
	free(l->locacoes);
	free(l);
}
