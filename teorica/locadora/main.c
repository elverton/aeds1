#include "locadora.h"
#include <stdio.h>

int main(){
    char nome_filme[100], nome_cliente[50], endereco[100];
    int id, ano, duracao, num_clientes, num_filmes;
    
    scanf("%d %d\n", &num_filmes, &num_clientes);
    Locadora *l = cria_locadora(10, 10, 10);
    
    for(int i=0; i<num_filmes; i++){
        scanf("%d\n", &id);
        fgets(nome_filme, 100, stdin);
        scanf("%d\n", &ano);
        scanf("%d\n", &duracao);
        insere_filme(l, id, nome_filme, ano, duracao);
    }
    for(int i=0; i<num_clientes; i++){
        scanf("%d\n", &id);
        fgets(nome_cliente, 50, stdin);
        fgets(endereco, 100, stdin);
        insere_cliente(l, id, nome_cliente, endereco);
    }
    exibe_filmes(l);
    exibe_clientes(l);
    return 0;
}
