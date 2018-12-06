#include <stdio.h>
#include <stdlib.h>

#include "funcsSort.h"

double difTempo(struct timespec t0, struct timespec t1){
  return ((double)t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec-t0.tv_nsec) * 1e-9);
}

int *bubbleSort(int *vetor, int tam){
  int cont, troca, aux;
  do{
    troca=0;
    for(cont=0; cont<(tam-1); cont++)
	if(vetor[cont]>vetor[cont+1]){
		aux=vetor[cont];
		vetor[cont]=vetor[cont+1];
		vetor[cont+1]=aux;
		troca=1;
	}
  }while(troca);
  return vetor;
}

int main(int argc, char *argv[]){
  int  i;
  int *vet;
  char linha[16];
  int tamVet;
  struct timespec t0, t1;

  if(argc < 2){
    printf("Uso: %s <numero de elementos a ordenar>\n", argv[0]);
    exit(0);
  }
  tamVet = atoi(argv[1]);
  vet = (int *) malloc(sizeof(int) * tamVet);

  for(i=0; i<tamVet; i++){
	fgets(linha, 16, stdin);
	sscanf(linha, "%d", &vet[i]);
  }


  clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
  bubbleSort(vet, tamVet);

    for(i=0; i<tamVet; i++){
    printf("%d\n",vet[i]);
  }
  clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
  printf("Tempo Selection Sort: %f\n", (float)difTempo(t0, t1));

  exit(0);
}
