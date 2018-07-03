#include <stdio.h>
#define vazio -9999

void balanceia_recursiva(int *vetor, int i) {
    int aux;
    int indice_pai  = (i - 1) / 2;
    if  (vetor[indice_pai] < vetor[i]){
      aux =  vetor[indice_pai];
      vetor[indice_pai] = vetor[i];
      vetor[i]  = aux;
    }
    i =  indice_pai;
    if (i!=0)
      balanceia_recursiva(vetor,i);
}


void balanceia(int *vetor, int tamanho) {
  for (int i = 1; i <  tamanho; i++){
    balanceia_recursiva(vetor,i);
  }
}

void excluir_valor(int *vetor, int valor, int tamanho) {
  for (int i = 0; i <  tamanho; i++){
    if (vetor[i] == valor) {
      vetor[i] = vetor[tamanho-1];
      vetor[tamanho-1] = vazio;
    }
  }
  balanceia(vetor,tamanho);
}

void main()
{
  int tam,  i;
  printf("Insira o numero de valores da arvore: ");
  scanf("%d", &tam);
  int vetor[tam];
  printf("\nInsira os valores um por um: \n");
  for (i = 0; i <  tam; i++) {
    printf("Vetor[%d]:",i);
    scanf("%d", &vetor[i]);
  }

  balanceia(vetor,tam);
  for (i = 0; i <  tam; i++)
    printf("Vetor[%d]: %d\n", i, vetor[i]);


  int valor;
  printf("\nDigite o valor a ser excluido:");
  scanf("%d",&valor);
  excluir_valor(vetor,valor,tam);

  printf("Vetor max heap:\n");
  for (i = 0; i <  tam-1; i++)
    printf("Vetor[%d]: %d\n", i, vetor[i]);
}