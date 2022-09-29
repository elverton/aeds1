#include <stdio.h>
#include <math.h>

int main(){
	char maiuscula, minuscula;
	printf("Insira uma letra maiúscula: ");
	scanf("%c", &maiuscula);
	minuscula = maiuscula + 32;
	printf("Letra minúscula: %c\n", minuscula);
	return 0;
}
