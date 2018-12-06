#include <stdio.h>
#include <stdlib.h>
#include "funcsSort.h"


int *shellSort(int *vet, int tam){
  int i, j, k=0, temp;
  int gaps[8]={701,301,132,57,23,10,4,1};
  while (gaps[k] > ((tam/2)-1))
	k++;
  while( gaps[k] >= 1 ){
    for(i = gaps[k]; i<tam; i++){
	temp = vet[i];
        j = i - gaps[k];
	while( j >= 0 && temp < vet[j]){
		vet[j+gaps[k]] = vet[j];
		j -= gaps[k];
	}
	vet[j+gaps[k]] = temp;
    }
    k++;
  }
  return vet;
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

  clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
  for(i=0; i<tamVet; i++){
	fgets(linha, 16, stdin);
	sscanf(linha, "%d", &vet[i]);
  }
  clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
  printf("Tempo leitura de dados: %f\n", (float)difTempo(t0, t1));

  clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
  shellSort(vet, tamVet);
  clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
  printf("Tempo Shell Sort: %f\n", (float)difTempo(t0, t1));

  exit(0);
}
