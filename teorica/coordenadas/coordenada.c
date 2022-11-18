#include "coordenada.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Coordenada* cria_coordenada(double x, double y){
	Coordenada *c = (Coordenada*)malloc(sizeof(Coordenada));
	c->x = x;
	c->y = y;
	return c;
}

void altera_coordenada(Coordenada *p, double x, double y){
	p->x = x;
	p->y = y;
}

Coordenada* duplica_coordenada(Coordenada *p){
	return cria_coordenada(p->x, p->y);
}

double calcula_distancia(Coordenada *p1, Coordenada *p2){
	double x = pow(p2->x - p1->x, 2);
	double y = pow(p2->y - p1->y, 2);
	return sqrt(x+y);
}

void destroi_coordenada(Coordenada *p){
	free(p);
}
