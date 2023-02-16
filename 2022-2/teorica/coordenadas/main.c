#include "coordenada.h"
#include <stdio.h>

int main(){
	Coordenada *p1 = cria_coordenada(2.2, 3.9);
	Coordenada *p2 = duplica_coordenada(p1);
	altera_coordenada(p2, 1.0, 1.0);
	printf("Distância = %lf", calcula_distancia(p1,p2));
	return 0;
}
