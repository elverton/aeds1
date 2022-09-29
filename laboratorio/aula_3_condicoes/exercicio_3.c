#include <stdio.h>
#include <math.h>

int main(){
	double altura, peso;
	printf("Insira altura e peso: ");
	scanf("%lf %lf", &altura, &peso);
	if(altura < 1.20){
		if(peso < 60){
			printf("A\n");
		}
		if(peso >= 60 && peso <= 90){
			printf("D\n");
		}
		if(peso > 90){
			printf("G\n");
		}
	}
	if(altura >= 1.20 && altura <= 1.70){
		if(peso < 60){
			printf("B\n");
		}
		if(peso >= 60 && peso <= 90){
			printf("E\n");
		}
		if(peso > 90){
			printf("H\n");
		}
	}
	if(altura > 1.70){
		if(peso < 60){
			printf("C\n");
		}
		if(peso >= 60 && peso <= 90){
			printf("F\n");
		}
		if(peso > 90){
			printf("I\n");
		}
	}
	return 0;
}
