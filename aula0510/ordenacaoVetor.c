//Ordenando um vetor do menor para o maior
#include <stdio.h>
#define TAM 5
main()
{
  int vetor[TAM],i,j,aux;
  
  for (i=0;i<TAM;i++) {
    printf("Digite um numero: ");
    scanf("%d",&vetor[i]);
  }
  
  for (i=0;i<(TAM-1);i++) {
  	for (j=i+1;j<TAM;j++) {
  	  printf("i-%d .... j-%d\n",i,j);
  	  if (vetor[i] > vetor[j]) {
  	    aux = vetor[i];
		vetor[i] = vetor[j];
		vetor[j] = aux;  
      }
    }
  }
  
  for (i=0;i<TAM;i++) {
    printf("%d ",vetor[i]);
  }
}
