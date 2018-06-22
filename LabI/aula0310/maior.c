#include <stdio.h>
#define TAM 4

int main(void)
{
  int v[TAM];
  int i;
  
  for (i=0;i<TAM;i++) {
    scanf("%d",&v[i]);
  }
  
  int maior = v[0];
  
  for (i=1;i<TAM;i++) {
    if (v[i] > maior) {
      maior = v[i];
	}
  }
  
  printf("o maior numero eh %d",maior);
  
}
