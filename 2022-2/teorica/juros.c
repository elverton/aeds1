#include <stdio.h>

int main(){
  float a,b,c;
  printf("Insira três valores: ");
  scanf("%f %f %f", &a, &b, &c);

  float x = a*(1.01*1.01);
  float y = b*(1.01);
  float z = x + y - c;
  float t = z*(1.01);
  printf("Saldo = %f\n", t);

}
