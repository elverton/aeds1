#include <stdio.h>

int main(){
  float x,y,z;
  printf("Digite os valores: ");
  scanf("%f %f %f", &x, &y, &z);
  x = x*(1+0.01*0.01);
  y = y*(1+0.01);
  z = x + y - z;
  z = z*(1+0.01);
  printf("Saldo total = %.2f\n", z);
  return 0;
}
