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

void insere_fim_lista(struct ponto **lista, int valor) 
{
  struct ponto *aux;
  if (*lista == NULL) {
    *lista=malloc(sizeof(struct ponto));
    aux = *lista;
    aux->valor=valor;
    aux->proximo=NULL;
    return;
  }
  aux = *lista;

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
  struct ponto *inicio=NULL;
  insere_fim_lista(&inicio,60);
  imprime_lista(inicio);
  // insere_fim_lista(inicio,30);
  // insere_fim_lista(inicio,65);


}