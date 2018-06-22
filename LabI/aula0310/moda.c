#include <stdio.h>
#define TAM 4

int main(void)
{
  int v[TAM];
  int i;
  int j;
  int cont[TAM];
  
  for (i=0;i<TAM;i++) {
    scanf("%d",&v[i]);
    cont[i] = 1;
  }
  
  for (i=0;i<TAM;i++) {
    for (j=0;j<TAM;j++) {
      if (i != j) {
        if (v[i] == v[j]) {
          cont[i]++;
		}
	  }
	}
  }
  
  int maior = cont[0];
  int posicao = 0;
  for (i=1;i<TAM;i++) {
    if (cont[i] > maior) {
      maior = cont[i];
      posicao = i;
    }
  }
  
  printf("%d eh a moda e aparece %d vezes",v[posicao],maior);
}
