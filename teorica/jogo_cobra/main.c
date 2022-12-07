#include <jogo.h>
#include <input.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SEGMENTOS 1000
#define TAM_SEGMENTO 10

typedef struct {
    int x;
    int y;
} Segmento;

typedef struct {
    Segmento segmentos[MAX_SEGMENTOS];
    int direcao;
    int tamanho;
} Cobra;

Cobra *cria_cobra(){
    Cobra *cobra = (Cobra*)malloc(sizeof(Cobra));
    cobra->segmentos[0].x = 40;
    cobra->segmentos[0].y = 0;   
    cobra->segmentos[1].x = 30;
    cobra->segmentos[1].y = 0;    
    cobra->segmentos[2].x = 20;
    cobra->segmentos[2].y = 0;    
    cobra->segmentos[3].x = 10;
    cobra->segmentos[3].y = 0;    
    cobra->direcao = DIREITA;
    cobra->tamanho = 4;
    return cobra;
}

void atualiza_cobra(Cobra *cobra){
    Segmento nova_cabeca;
    int tamanho_cobra = cobra->tamanho;
    nova_cabeca.x = cobra->segmentos[0].x;
    nova_cabeca.y = cobra->segmentos[0].y;

    if(cobra->direcao == CIMA){
        nova_cabeca.y -= TAM_SEGMENTO;
    }
    if(cobra->direcao == BAIXO){
        nova_cabeca.y += TAM_SEGMENTO;
    }
    if(cobra->direcao == DIREITA){
        nova_cabeca.x += TAM_SEGMENTO;
    }
    if(cobra->direcao == ESQUERDA){
        nova_cabeca.x -= TAM_SEGMENTO;
    }

    for(int i=tamanho_cobra-1; i>=0; i--){
        cobra->segmentos[i+1] = cobra->segmentos[i];
    }
    cobra->segmentos[0] = nova_cabeca;
}

void desenha_cobra(Cobra *cobra){
    for(int i=0; i < cobra->tamanho; i++){
        int x = cobra->segmentos[i].x;
        int y = cobra->segmentos[i].y;
        desenha_retangulo(x, y, TAM_SEGMENTO, TAM_SEGMENTO);
    }
}

int main() {

    abre_janela(640, 480);
    Cobra *cobra = cria_cobra();

    while (janela_esta_aberta()) {
        atualiza_cobra(cobra);
        desenha_cobra(cobra);

        if (tecla_acabou_de_ser_apertada(CIMA)) 
            cobra->direcao = CIMA;
        if (tecla_acabou_de_ser_apertada(BAIXO)) 
            cobra->direcao = BAIXO;
        if (tecla_acabou_de_ser_apertada(ESQUERDA)) 
            cobra->direcao = ESQUERDA;
        if (tecla_acabou_de_ser_apertada(DIREITA)) 
            cobra->direcao = DIREITA;
        int i=0;
        while(i < 100000000){
            i++;
        }
    }
    fecha_janela();
}


