// Codigo desenvolvido durante a disciplina ELC1066
// Estrutura de Dados "A" - 2018/01
// Prof.: Celio Trois

#include <stdio.h>
#include <stdlib.h>

struct no {
  int valor;
  int alt;
  struct no* esq;
  struct no* dir;
};

typedef struct no arvore;

arvore *arvore_vazia(){
  return NULL;
}

arvore *cria_arvore(int valor, arvore *esq, arvore *dir){
  arvore *a=malloc(sizeof(arvore));
  a->valor = valor;
  a->alt=0;
  a->esq = esq;
  a->dir = dir;
  return a;
}

int esta_vazia(arvore *a){
  return a==NULL;
}

arvore *desaloca_arvore(arvore *a){
  if (!esta_vazia(a)){
    desaloca_arvore(a->esq);
    desaloca_arvore(a->dir);
    free(a);
  }
  return NULL;
}

int existe_valor(int valor, arvore *a){
  if(esta_vazia(a)){
    return 0;
  }
  else {
    return a->valor==valor || existe_valor(valor, a->esq) || existe_valor(valor, a->dir);
  }
}

void imprime(arvore *a){
  if (!esta_vazia(a)){
     imprime(a->esq);
     printf("%i (%i)\n", a->valor, a->alt);
     imprime(a->dir);
  }
}

int conta_folhas(arvore *a){
  if(esta_vazia(a))
    return 0;
  else 
    return 1 + conta_folhas(a->esq) + conta_folhas(a->dir);
}

int sao_iguais(arvore* a, arvore* b){
  return
    esta_vazia(a) && esta_vazia(b)
      ||
    (!esta_vazia(a) && !esta_vazia(b) &&
    a->valor == b->valor &&
    sao_iguais(a->esq, b->esq) &&
    sao_iguais(a->dir, b->dir));
}

int calcula_altura(arvore *a){
  if (a == NULL)
    return -1;
  else {
    printf("a->valor: %i\n",a->valor);
  if (calcula_altura(a->dir) > calcula_altura(a->esq))
    return calcula_altura(a->dir)+1;
  else 
    return calcula_altura(a->esq)+1;
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


void insere_ordenado(int valor, arvore **a){
  if (!esta_vazia(*a))
     if (valor < (*a)->valor)
       if (esta_vazia((*a)->esq))
         (*a)->esq = cria_arvore(valor, arvore_vazia(), arvore_vazia());
       else
         insere_ordenado(valor, &(*a)->esq);
     else
       if (esta_vazia((*a)->dir))
         (*a)->dir = cria_arvore(valor, arvore_vazia(), arvore_vazia());
       else
         insere_ordenado(valor, &(*a)->dir);
  else
     (*a)=cria_arvore(valor, arvore_vazia(), arvore_vazia());
  (*a)->alt = calcula_altura(*a);
}

int busca_menor_valor(arvore *a){
  if (esta_vazia(a))
    return -999999;
  while(a->esq!=NULL)
    a=a->esq;
  return a->valor;
}

arvore *remover(int valor, arvore *a){
  if (esta_vazia(a))
    return NULL;
  if (valor < a->valor)
    a->esq = remover(valor, a->esq);
  else if (valor > a->valor)
    a->dir = remover(valor, a->dir);
  else { // eh o no que queremos remover
    if (a->dir==NULL && a->esq==NULL){ //sem filhos
      free(a);
      a=NULL;
    }
    else if (a->dir==NULL){ // so tem o filho da esquerda
      arvore *tmp = a;
      a = a->esq;
      free(tmp);
    }
    else if (a->esq==NULL){ // so tem o filho da direita
      arvore *tmp = a;
      a = a->dir;
      free(tmp);
    }
    else { // tem os dois filhos
      int menor = busca_menor_valor(a->dir);
      a->valor = menor;
      a->dir = remover(menor, a->dir);
    }
  }
  if (!esta_vazia(a))
    a->alt = calcula_altura(a);
  return a;
}

void main(){
  // arvore *a1=arvore_vazia();

  //   insere_ordenado(30,&a1);
  // insere_ordenado(10,&a1);

  // insere_ordenado(35,&a1);
  // insere_ordenado(5,&a1);
  // imprime(a1);
arvore *raiz3=NULL;
  insere_ordenado(30,&raiz3);
  insere_ordenado(10,&raiz3);

  insere_ordenado(35,&raiz3);
  insere_ordenado(5,&raiz3);
  imprime(raiz3); 
  printf("\n\n\n");
  remover(30,raiz3);
  imprime(raiz3); 
  // a1=remover(30,a1);
  // imprime(a1);  printf("\n");
  // a1=remover(31,a1);
  // imprime(a1);  printf("\n");
  // a1=remover(10,a1);
  // imprime(a1);  printf("\n");

}
