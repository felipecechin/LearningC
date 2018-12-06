#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define num_buckets 50

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
    quickSort(vet, lo, p);
    quickSort(vet, p+1, hi);
  }
  return vet;
}

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

    filho = i * 2 + 1;

    while (filho < n) {
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

struct bucket 
{
  int cont;
  int* valores;
};

void bucketSort(int array[],int n)
{
  struct bucket buckets[num_buckets];

  /*Valor de intervalo entre cada bucket*/
  int n_elem_bucket = n/num_buckets;
  int i, j, k;
  for (i = 0; i < num_buckets; i++) {
    buckets[i].cont = 0;
    buckets[i].valores = (int*)malloc(sizeof(int) * n);
  }
  for (i = 0; i < n; i++) {
    j=num_buckets-1;
    while(1){
      if(j<0) {
        break;
      }
      if(array[i]>=j*n_elem_bucket) {
        buckets[j].valores[buckets[j].cont]=array[i];
        (buckets[j].cont)++;
        break;
      }
      j--;
    }
  }
  for (i = 0;i<num_buckets;i++) {
    quickSort(buckets[i].valores, 0, buckets[i].cont-1);
    /*heapsort(buckets[i].valores, buckets[i].cont);*/
    /*insertSort(buckets[i].valores, buckets[i].cont);*/
  }
  k = 0;
  for (i = 0;i<num_buckets;i++) {
    for (j = 0;j<buckets[i].cont;j++) {
      array[k] = buckets[i].valores[j];
      k++;
    }
  }

}

int main(int argc, char *argv[]) {

  int *vet;
  char linha[16];
  int tamVet,i;
  clock_t tempo_inicial, tempo_final;

  if(argc < 2){
    printf("Uso: %s <numero de elementos a ordenar>\n", argv[0]);
    exit(0);
  }

  tamVet = atoi(argv[1]);
  vet = (int *) malloc(sizeof(int) * tamVet);

  for(i=0; i<tamVet; i++){
    if (fgets(linha, 16, stdin) != NULL) {
      sscanf(linha, "%d", &vet[i]);
    }
  }
  tempo_inicial = clock();
  bucketSort(vet, tamVet);
  tempo_final = clock();
  printf("Tempo Bucket Sort: %f s.\n", (tempo_final - tempo_inicial) / (double)CLOCKS_PER_SEC);
  return 0;
}