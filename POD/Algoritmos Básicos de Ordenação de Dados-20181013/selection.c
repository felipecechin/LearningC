#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <sys/time.h>



int *selectionSort(int *vetor, int tam){
  int cont, cont2, menor, novoMenor, aux;

  for(cont=0; cont<tam; cont++){
    novoMenor=cont;
    for(cont2=cont; cont2<tam; cont2++){
	if(vetor[cont2] < vetor[novoMenor])
		novoMenor = cont2;
    }
    aux = vetor[cont];
    vetor[cont] = vetor[novoMenor];
    vetor[novoMenor] = aux;
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
  selectionSort(vet, tamVet);
  clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
  printf("Tempo Selection Sort: %f\n", (float)difTempo(t0, t1));

//  mostra(vet,TAM_VET);
  exit(0);
}
