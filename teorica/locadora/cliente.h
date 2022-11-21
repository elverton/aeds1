#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct {
	int id; 
	char nome[50];
	char endereco[100];
} Cliente;

Cliente* cria_cliente(int id, char *nome, char *endereco);
int recupera_id_cliente(Cliente *f);
char *recupera_nome_cliente(Cliente *f);
void destroi_cliente(Cliente *f);


#endif
