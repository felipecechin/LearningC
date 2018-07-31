#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

arvore *cria_vazia(){
  return NULL;
}

int esta_vazia(arvore *a){
  return a==NULL;
}

void imprime(arvore *a){
  if (!esta_vazia(a)){
         imprime(a->esq);
     printf("%i (%i)\n", a->valor, a->alt);
     imprime(a->dir);
  }
}

arvore *cria_arvore(int valor, arvore *sae, arvore *sad) {
  arvore *arvore = malloc(sizeof(arvore));
  arvore->valor = valor;
  arvore->alt = 0;
  arvore->esq = sae;
  arvore->dir = sad;
  return arvore;
}

arvore *desaloca_arvore(arvore *a){
  if (a!=NULL) {
    desaloca_arvore(a->esq);
    desaloca_arvore(a->dir);
    free(a);
  }
  return NULL;
}

int conta_folhas(arvore *a) {
  if (!esta_vazia(a)) {
    return 1+conta_folhas(a->esq)+conta_folhas(a->dir);
  } else {
    return 0;
  }
}

int sao_iguais(arvore *a, arvore *b) {
  return (
   (esta_vazia(a) && esta_vazia(b))
    || 
   (!esta_vazia(a) && !esta_vazia(b) && a->valor == b->valor && sao_iguais(a->esq,b->esq) && sao_iguais(a->dir,b->dir))
  );
}

//rotação RR ou rotação simples a esquerda
//rotação LL ou rotação simples a direita
//rotação RL ou rotação dupla a esquerda
    //rotação LL -> rotação RR
//rotação LR ou rotação dupla a direita
    //rotação RR -> rotação LL


int calcula_altura(arvore *a) {
  if (a==NULL) {
    return -1;
  } else {
    printf("a->valor: %i\n",a->valor);
    if (calcula_altura(a->dir) > calcula_altura(a->esq)) {
      return calcula_altura(a->dir)+1;
    } else {
      return calcula_altura(a->esq)+1;
    }
  }
}

int calcula_altura_sem_recursao(arvore *a){
  if (a == NULL)
    return -1;
  else if (a->esq==NULL && a->dir==NULL)
    return 0;
  else if (a->dir==NULL) 
    return a->esq->alt+1;
  else if (a->esq==NULL)
    return a->dir->alt+1;
  else if(a->dir->alt > a->esq->alt)
    return a->dir->alt+1;
  else 
    return a->esq->alt+1;
}

void insere_ordenado(int valor, arvore **a) {
  if (esta_vazia(*a)) {
    (*a) = cria_arvore(valor,cria_vazia(),cria_vazia());
  } else {
    if (valor < (*a)->valor) {
      insere_ordenado(valor, &((*a)->esq));
    } else {
      insere_ordenado(valor, &((*a)->dir));
    }
  }
  (*a)->alt = calcula_altura_sem_recursao(*a);
}

int existe_valor(int valor,arvore *a) {
  if (esta_vazia(a)) {
    return 0;
  } else {
    return valor == a->valor||existe_valor(valor,a->esq)||existe_valor(valor,a->dir);
  }
}

arvore *encontra_maior_valor(arvore *a) {
  while (a->dir != NULL) {
    a = a->dir;
  }
  return a;
}


arvore *remover(arvore *a, int valor) {
  if (esta_vazia(a)) {
    return NULL;
  } else if (valor < a->valor) {
    a->esq = remover(a->esq, valor);
  } else if (valor > a->valor) {
    a->dir = remover(a->dir, valor);
  } else if (valor == a->valor) {
    if (a->esq == NULL && a->dir == NULL) {
      free(a);
      return NULL;
    } else if (a->dir == NULL) {
      arvore *b = a->esq;
      free(a);
      return b;
    } else if (a->esq == NULL) {
      arvore *b = a->dir;
      free(a);
      return b;
    } else {
      arvore *b = encontra_maior_valor(a->esq);
      a->valor = b->valor;
      a->esq = remover(a->esq, b->valor);
    }
  }
  a->alt = calcula_altura(a);
  return a;
}


void main() {


  arvore *raiz3=NULL;
  insere_ordenado(30,&raiz3);
  insere_ordenado(10,&raiz3);

  insere_ordenado(35,&raiz3);
  insere_ordenado(5,&raiz3);
  imprime(raiz3); 
  printf("\n\n\n");
  remover(raiz3,30);
  imprime(raiz3); 
  // printf("CONTA-FOLHAS: %d\n",conta_folhas(raiz3));
  // printf("SAO IGUAIS: %d\n",sao_iguais(raiz2,raiz3));
  // printf("EXISTE VALOR: %d\",existe_valor(12,raiz3));
  // printf("\n\n\n");
  

  // imprime(raiz3);  



/*
  arvore *raiz=cria_arvore(5, cria_vazia(), cria_vazia());
  imprime(raiz); printf("\n");

  raiz->esq = cria_arvore(35, 
                     cria_arvore(40, cria_vazia(), cria_vazia()),
                     cria_arvore(42, cria_vazia(), cria_vazia()));
  raiz->dir = cria_arvore(60, 
                     cria_arvore(62, cria_vazia(), cria_vazia()),
                     cria_vazia());
  insere_ordenado(3,raiz);
  imprime(raiz); printf("\n");

*/

/*
  arvore *raiz2=cria_arvore(5, cria_vazia(), cria_vazia());

  raiz2->esq = cria_arvore(35, 
                     cria_arvore(40, cria_vazia(), cria_vazia()),
                     cria_arvore(42, cria_vazia(), cria_vazia()));
  raiz2->dir = cria_arvore(60, 
                     cria_arvore(62, cria_vazia(), cria_vazia()),
                     cria_vazia());

  printf("Existe valor %d\n",existe_valor2(63,raiz));
  printf("Conta folhas %d\n",conta_folhas(raiz));


  printf("Sao iguais %d\n",sao_iguais(raiz,raiz2));



  imprime(raiz);
  imprime(raiz2);
*/
}