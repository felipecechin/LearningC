#include <stdio.h>
#include <stdlib.h>
#define vazio -9999

void inicializa_vetor(int *vet, int col) {
  for (int i = 0; i < col; i++) {
    vet[i] = vazio;
  }
}

int *aloca_vetor(int col) {
  int *vetor;
  vetor = malloc(col*sizeof(int));
  inicializa_vetor(vetor, col);
  return vetor; 
}

void imprime_vetor(int *vet, int col) {
  for (int i = 0; i < col; i++) {
    printf("vet[%d]: %d\n",i,vet[i]);
  }
}

void insercao_ordenada(int *vet, int valor) {
  int i = 0;
  while (vet[i] != vazio) {
    if (valor < vet[i]) {
      i = (i*2)+1;
    } else {
      i = (i*2)+2;
    }
  }
  vet[i] = valor;
}

void remover(int *vet, int valor) {
  int i = 0;
  while (vet[i] != vazio) {
    if (valor < vet[i]) {
      i = (i*2)+1;
    } else if (valor > vet[i]) {
      i = (i*2)+2;
    } else {
      vet[i] = vazio;
      return;
    }
  }
}

int buscar(int *vet, int valor) {
  int i = 0;
  while (vet[i] != vazio) {
    if (valor < vet[i]) {
      i = (i*2)+1;
    } else if (valor > vet[i]) {
      i = (i*2)+2;
    } else {
      return i;
    }
  }
}

int main() {
  int *vetor = aloca_vetor(50);
  insercao_ordenada(vetor,2);
  insercao_ordenada(vetor,4);
  insercao_ordenada(vetor,5);
  insercao_ordenada(vetor,1);
  insercao_ordenada(vetor,7);
  insercao_ordenada(vetor,3);
  printf("busca: %d\n",buscar(vetor, 1));
  imprime_vetor(vetor,50);
}