#include "massa.h"
#include <stdio.h>

int main(){
    double massa_em_kilos;
    scanf("%lf", &massa_em_kilos);
    double massa_em_gramas = 
        kilo_para_grama(massa_em_kilos);
    printf("Valor em gramas: %lf\n", massa_em_gramas);
    return 0;
}
