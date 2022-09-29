#include <stdio.h>
#include <math.h>

/* Para compilar o programa, não se esqueça de usar -lm */

#define PI 3.141592

int main(){
	double raio, altura, volume;
	printf("Insira o raio e altura: ");
	scanf("%lf %lf", &raio, &altura);
	/* Função pow(b,e) recebe a base b e expoente e
	 * retorna o resultado de b elevado a e. */
	volume = PI * pow(raio, 2) * altura;
	printf("Volume: %lf\n", volume);
	return 0;
}
