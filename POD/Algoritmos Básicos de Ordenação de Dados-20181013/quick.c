#include <stdio.h>
#include <stdlib.h>
#include "funcsSort.h"

int partition(int *vet, int lo, int hi){
  int pivo, i, j, aux;
  pivo = vet[lo];
  i=lo-1;
  j=hi+1;

  while(1){
	do{
	  j--;
	} while(vet[j] > pivo);

	do{
		i++;
	} while(vet[i] < pivo);

	if(i<j){
		aux = vet[i];
		vet[i] = vet[j];
		vet[j] = aux;
	} else {
		return j;
	}
  }
}

int *quickSort(int *vet, int lo, int hi){
  int p;
  if(lo<hi){
	p = partition(vet, lo, hi);
//	printf("lo %d hi %d p %d\n", lo, hi, p);
	quickSort(vet, lo, p);
	quickSort(vet, p+1, hi);
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
 // mostra(vet,tamVet);

  clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
  quickSort(vet, 0, tamVet-1);
  clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
  printf("Tempo quick Sort: %f\n", (float)difTempo(t0, t1));
// mostra(vet,tamVet);

  exit(0);
}
