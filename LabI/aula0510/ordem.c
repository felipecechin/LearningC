//Ler um vetor de números e dizer se o vetor está na ordem ou não (do menor para o maior)
#include <stdio.h>
#include <stdbool.h>

main()
{
  int vetor[5],i;
  for (i=0;i<5;i++) {
    printf("Digite um numero: ");
    scanf("%d",&vetor[i]);
  }
  bool ordem = true;
  for (i=0;i<4;i++) {
  	if (vetor[i] > vetor[i+1]) {
  	  ordem = false;  
    }
  }
  
  if (ordem) {
    printf("O vetor esta na ordem do menor para o maior\n");
  } else {
  	printf("O vetor nao esta na ordem do menor para o maior\n");
  }
  for (i=0;i<5;i++) {
    printf("%d ",vetor[i]);
  }
}
