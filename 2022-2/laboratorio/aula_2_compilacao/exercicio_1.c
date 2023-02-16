#include <stdio.h>

#define ANO_ATUAL 2022

int main(){
	int idade, ano_nascimento;
	printf("Insira sua idade: ");
	scanf("%d", &idade);
	ano_nascimento = ANO_ATUAL - idade;
	printf("Ano de nascimento: %d\n", ano_nascimento);
	return 0;
}
