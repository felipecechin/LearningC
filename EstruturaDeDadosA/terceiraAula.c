#include <stdio.h>
#include <stdlib.h>

//enviar ate 26/03 p trois@inf.ufsm.br

struct ponto{
  int valor;
  struct ponto *proximo;
};

struct l_descr{
  struct ponto *inicio;
  int cnt;
  struct ponto *fim;
};

void inicializa_lista(struct l_descr *lista) {
  lista->inicio=NULL;
  lista->cnt=0;
  lista->fim=NULL;
}


void imprime_lista(struct l_descr *lista) 
{
  struct ponto *aux = lista->inicio;
  while(aux!=NULL) {
    printf("%d\n",aux->valor);
    aux = aux->proximo;
  }
}

int encontrar_posicao(struct ponto *aux,int valor)
{
  int i=0;
  while(aux!=NULL) {
    if (aux->valor == valor) {
      return i;
    }
    i++;
    aux = aux->proximo;
  }
  return -1;
}

int quantidade(struct ponto *aux)
{
  int i=0;
  while(aux!=NULL) {
    i++;
    aux = aux->proximo;
  }
  return i;
}

void insere_fim_lista(struct l_descr *lista, int valor) 
{
  struct ponto *aux;
  if (lista->inicio == NULL) {
    lista->inicio=malloc(sizeof(struct ponto));
    aux = lista->inicio;
    aux->valor=valor;
    aux->proximo=NULL;
    lista->cnt++;
    lista->fim=lista->inicio;
    return;
  }
  aux = lista->fim;

  if (aux->proximo==NULL) {
    aux->proximo = malloc(sizeof(struct ponto));
    aux->proximo->valor = valor;
    aux->proximo->proximo = NULL;
    lista->cnt++;
    lista->fim=aux->proximo;
  }
}

int main() {
  struct l_descr lista1;

  inicializa_lista(&lista1);


  insere_fim_lista(&lista1,60);
  insere_fim_lista(&lista1,30);
  insere_fim_lista(&lista1,20);
  imprime_lista(&lista1);
  printf("%d\n",lista1.cnt);
  // insere_fim_lista(inicio,30);
  // insere_fim_lista(inicio,65);
}