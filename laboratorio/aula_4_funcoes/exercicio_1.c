#include <stdio.h>

double media(double n1, double n2, double n3, char T){
    if(T == 'A'){
        return (n1 + n2 + n3)/3;
    } else {
        return (5*n1 + 3*n2 + 2*n3)/10;
    }
}

int main(){
    double a, b, c;
    char tipo;
    scanf("%lf %lf %lf %c", &a, &b, &c, &tipo);
    double M = media(a, b, c, tipo);
    printf("Média = %lf\n", M);
    return 0;
}
