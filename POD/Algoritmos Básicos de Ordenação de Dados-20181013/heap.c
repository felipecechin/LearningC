#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <sys/time.h>

#include "funcsSort.h"

void heapsort(int a[], int n) {

   int i = n / 2, pai, filho, t;

   for (;;) {
      if (i > 0) {
          i--;
          t = a[i];
      } else {
          n--;
          if (n == 0) return;
          t = a[n];
          a[n] = a[0];
      }

      pai = i;

      //Primeiro será feita a comparação com o filho da esquerda.
      filho = i * 2 + 1;

      while (filho < n) {

         //Se o filho da esquerda for menor do que o filho da direita,então será feita a troca do filho que será comparado.
          if ((filho + 1 < n)  &&  (a[filho + 1] > a[filho]))
              filho++;
          if (a[filho] > t) {
             a[pai] = a[filho];
             pai = filho;
             filho = pai * 2 + 1;
          } else {
             break;
          }
      }
      a[pai] = t;
   }
}


main(int argc, char *argv[]){
  int  i;
  int *vet, tamVet;
  char linha[16];
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
  heapsort(vet, tamVet);
  clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
  printf("Tempo Heap Sort: %f\n", (float)difTempo(t0, t1));
//  mostra(vet,tamVet);

  exit(0);
}
