#include "funcsSort.h"

void mostra(int *vetor, int tam){
  int cont;
  for(cont=0; cont<tam; cont++)
	printf("%d ", vetor[cont]);
  printf("\n");
  return;
}

double difTempo(struct timespec t0, struct timespec t1){
  return ((double)t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec-t0.tv_nsec) * 1e-9);
}


int *embaralha(int *vetor, int tam){
  int cont, i, aux;
  for(cont=0; cont<tam; cont++){
	i = ((int) random()) % tam;
	aux = vetor[cont];
	vetor[cont] = vetor[i];
	vetor[i] = aux;
  }
  return vetor;
}


