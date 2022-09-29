#include <stdio.h>
#include <math.h>

int main(){
	int n1, n2;
	printf("Insira dois inteiros: ");
	scanf("%d %d", &n1, &n2);
	
	if(n1 > n2){
		printf("%d é maior\n", n1);
	}

	if(n1 < n2){
		printf("%d é maior\n", n2);
	}

	if(n1 == n2){
		printf("Números iguais\n");
	}
	return 0;
}
