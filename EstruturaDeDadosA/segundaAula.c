#include <stdio.h>
#include <stdlib.h>

struct ponto{
  int valor;
  struct ponto *proximo;
};


void imprime_lista(struct ponto *aux) 
{
  while(aux!=NULL) {
    printf("%d\n",aux->valor);
    aux = aux->proximo;
  }
}

void insere_fim_lista(struct ponto *aux, int valor) 
{
  for(;;) {
    if (aux->proximo==NULL) {
      aux->proximo = malloc(sizeof(struct ponto));
      aux->proximo->valor = valor;
      aux->proximo->proximo = NULL;
      break;
    }
    aux = aux->proximo;
  }
}

int main() {

  struct ponto a;
  struct ponto *inicio=&a;
  //imprime_lista(inicio);
  inicio->valor = 10;
  inicio->proximo=NULL;
  insere_fim_lista(inicio,60);
  insere_fim_lista(inicio,30);
  insere_fim_lista(inicio,65);

  imprime_lista(inicio);
}