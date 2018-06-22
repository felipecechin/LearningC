#include <stdio.h>
#include <math.h>
#define TAM 4

int main(void)
{
  int v[TAM];
  int i;
  int s = 0;
  
  for (i=0;i<TAM;i++) {
    scanf("%d",&v[i]);
    s = s + v[i];
  }
  float m;
  m = (float) s/TAM;
  float somaVariancia = 0;
  for (i=0;i<TAM;i++) {
    somaVariancia = somaVariancia + pow(v[i]-m,2);  
  }
  float variancia;
  variancia = somaVariancia/TAM;
  
  float desvioPadrao;
  desvioPadrao = sqrt(variancia);
  printf("Desvio padrao = %f",desvioPadrao);

}
