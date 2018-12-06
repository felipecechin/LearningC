#include <stdio.h>
#include <stdlib.h>

#include "funcsSort.h"

int *insertSort(int *vetor, int tam){
  int cont, cont2, cont3, aux;

  for(cont=1; cont < tam; cont++){
    for(cont2=0; cont2<cont; cont2++){
	if(vetor[cont2] > vetor[cont]){
		aux = vetor[cont];
		for(cont3=cont; cont3>cont2; cont3--){
			vetor[cont3]=vetor[cont3-1];
		}
		vetor[cont2]=aux;
		break;
	}
    }
  }

  return vetor;
}

main(int argc, char *argv[]){
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
  insertSort(vet, tamVet);
  clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
  printf("Tempo Insertion Sort: %f\n", (float)difTempo(t0, t1));
  exit(0);
}
