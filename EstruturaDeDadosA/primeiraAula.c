#include <stdio.h>
#include <stdlib.h>

struct ponto{
  int x;
  struct ponto *proximo;
};


int main() {
  // int a = 10;
  // //ponteiro apontando para a posição alocada de memória
  // int *ptr = malloc(sizeof(int));

  // *ptr = 99;
  // //ponteiro apontando para a posição da memória de a
  // ptr=&a;

  // printf("a=%d   |  %p   |  %d\n",a ,ptr, *ptr);

  // struct ponto a;

  // struct ponto *ptr;

  // a.x = 10;
  // a.y = 20;

  // ptr = malloc(sizeof(struct ponto));

  // ptr->x=5;
  // ptr->y=0;

  struct ponto a;
  struct ponto *inicio =&a;
  a.x = 10;
  a.proximo = malloc(sizeof(struct ponto));
  a.proximo->x = 20;
  a.proximo->proximo=NULL;
  a.proximo->proximo=malloc(sizeof(struct ponto));
  a.proximo->proximo->x=30;
  a.proximo->proximo->proximo=NULL;

  struct ponto *aux=inicio;
  while(aux!=NULL) {
    printf("%d\n",aux->x);
    aux = aux->proximo;
  }
  free(a.proximo);
  // printf("a0=%d | a1=%d | a2=%d\n", a.x,a.proximo->x,a.proximo->proximo->x);
}