#ifndef COORDENADA_H
#define COORDENADA_H

typedef struct { 
	double x;
	double y;
} Coordenada;

Coordenada* cria_coordenada(double x, double y);
void altera_coordenada(Coordenada *p, double x, double y);
Coordenada* duplica_coordenada(Coordenada *p);
double calcula_distancia(Coordenada *p1, Coordenada *p2);
void destroi_coordenada(Coordenada *p);

#endif
