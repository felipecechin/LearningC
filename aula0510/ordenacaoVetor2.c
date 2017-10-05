#include <stdio.h>

int achaind(int v[],int i1,int i2) 
{
  int menor = v[i1];
  int posicao = i1;
  int i;
  for (i=i1+1;i<i2;i++) {
  	if (v[i] < menor) {
  	  menor = v[i];	
  	  posicao = i;
	}
  }
  return posicao;
}

void troca(int v[],int i, int j) 
{
  int aux;
  aux = v[i];
  v[i] = v[j];
  v[j] = aux;
}


void ordena(int v[],int n)
{
  int i,j;
  for (i=0;i<n-1;i++) {
    j = achaind(v,i,n);
    troca(v,i,j);
  }
}

int main(void)
{
  int v[5];
  int i;
  for (i=0;i<5;i++) {
    printf("Digite um numero: ");
    scanf("%d",&v[i]);
  }
  
  ordena(v,5);
  
  for (i=0;i<5;i++) {
    printf("%d  ",v[i]);
  }
}
