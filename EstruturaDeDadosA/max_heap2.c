#include <stdio.h>
#define vazio -9999

void balanceia(int *vetor, int i) {
  int indice_pai,aux;
  indice_pai = (i-1)/2;
  if (vetor[indice_pai] < vetor[i]) {
    aux =  vetor[indice_pai];
    vetor[indice_pai] = vetor[i];
    vetor[i]  = aux;
    i = indice_pai;
    if (i!=0) 
      balanceia(vetor,i);
  } else {
    return;
  }
}

int ultimo_indice(int *vetor) {
  int valor, i;
  i = 0;
  while(vetor[i] != vazio) {
    i++;
  }
  return i-1;
}

void excluir_valor(int *vetor, int tamanho, int valor) {
  printf("Excluindo o valor %d\n", valor);
  for (int i = 0; i <  tamanho; i++){
    if (vetor[i] == valor) {
      int indice = ultimo_indice(vetor);
      vetor[i] = vetor[indice];
      vetor[indice] = vazio;
      for (int j = i; j <  indice; j++){
        balanceia(vetor,j);
      }
      return;
    }
  }
}

void inicializa_vetor(int *vetor, int tam) {
  for (int i = 0; i <  tam; i++){
    vetor[i] = vazio;
  }
}

void insere(int *vetor,int tam, int valor) {
  printf("Inserindo o valor %d\n", valor);
  for (int i = 0; i <  tam; i++){
    if (vetor[i] == vazio) {
      vetor[i] = valor;
      balanceia(vetor,i);
      return;
    }
  }
}

void main()
{
  int vetor[20];
  inicializa_vetor(vetor,20);
  insere(vetor,20,10);
  insere(vetor,20,15);
  insere(vetor,20,30);
  insere(vetor,20,50);
  insere(vetor,20,60);
  insere(vetor,20,34);
  insere(vetor,20,15);
  insere(vetor,20,16);
  insere(vetor,20,17);
  insere(vetor,20,50);
  insere(vetor,20,35);

  
  for (int i = 0; i <  20; i++) {
    if (vetor[i] != vazio) 
      printf("Vetor[%d]: %d\n", i, vetor[i]);
    else
      break;
  }


  excluir_valor(vetor,20,30);
  insere(vetor,20,36);
  excluir_valor(vetor,20,36);
  insere(vetor,20,33);
  excluir_valor(vetor,20,50);

  for (int i = 0; i <  20; i++) {
    if (vetor[i] != vazio) 
      printf("Vetor[%d]: %d\n", i, vetor[i]);
    else
      break;
  }
}