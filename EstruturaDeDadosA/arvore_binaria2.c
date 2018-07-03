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

int calcula_altura_rec(arvore *a){
  if (a == NULL)
    return -1;
  if (calcula_altura_rec(a->dir) > calcula_altura_rec(a->esq))
    return calcula_altura_rec(a->dir)+1;
  else 
    return calcula_altura_rec(a->esq)+1;
}

int alt_no(arvore *a){
  if (a == NULL)
    return -1;
  else
    return a->alt;
}

int maior(int a, int b){
  if (a>b)
    return a;
  else
    return b;
}

int calcula_altura(arvore *a){
  return maior(alt_no(a->esq), alt_no(a->dir))+1;
}

int calc_fb(arvore *a){
  return alt_no(a->esq) - alt_no(a->dir);
}

void rotacao_ll(arvore **a){
  arvore *b;
  b=(*a)->esq;
  (*a)->esq=b->dir;
  b->dir = (*a);
  (*a)->alt=calcula_altura(*a);
  b->alt=calcula_altura(b);
  (*a)=b;
}

void rotacao_rr(arvore **a){
  arvore *b;
  b=(*a)->dir;
  (*a)->dir=b->esq;
  b->esq = (*a);
  (*a)->alt=calcula_altura(*a);
  b->alt=calcula_altura(b);
  (*a)=b;
}

void rotacao_lr(arvore **a){
  rotacao_rr(&((*a)->esq));
  rotacao_ll(a);
}

void rotacao_rl(arvore **a){
  rotacao_ll(&((*a)->dir));
  rotacao_rr(a);
}

void imprime(arvore *a){
  if (!esta_vazia(a)){
     printf("%i (%i)\n", a->valor, calc_fb(a));
     imprime(a->esq);
     imprime(a->dir);
  }
}

void rebalanceia(arvore **a){
  int fb=calc_fb(*a);
  //printf("fb = %d; valor=%d\n", fb, (*a)->valor);fflush(stdout);
  if (fb>=2){ // a esquerda esta desbalanceada
    if (calc_fb((*a)->esq)>0){ // eh positivo, logo deve-se aplicar a rotacao LL
      printf("LL\n");fflush(stdout);
      rotacao_ll(a);
    }
    else { // o neto esta a direita, logo, LR
      printf("LR\n");fflush(stdout);
      rotacao_lr(a);
    }
  }
  else if (fb<=-2){// a direita esta desbalanceada 
    if (calc_fb((*a)->dir)<0){ // eh negativo, logo deve-se aplicar a rotacao RR
      printf("RR\n");fflush(stdout);
      rotacao_rr(a);
    }
    else{ // o neto esta a esquerda, logo, RL
      printf("RL\n");fflush(stdout);
      rotacao_rl(a);
    }
  }

}

void insere_ordenado(int valor, arvore **a){
  printf("Inserindo %d\n",valor);
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
  rebalanceia(a);
}

int busca_menor_valor(arvore *a){
  if (esta_vazia(a))
    return -999999;
  while(a->esq!=NULL)
    a=a->esq;
  return a->valor;
}

arvore *remover(int valor, arvore *a){
  printf("Removendo %d\n",valor);
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
  if (!esta_vazia(a)){
    a->alt = calcula_altura(a);
    rebalanceia(&a);
  }
  return a;
}



void main(){
  arvore *a1=arvore_vazia();

  insere_ordenado(30, &a1);
  imprime(a1);  printf("\n");
  insere_ordenado(15, &a1);
  imprime(a1);  printf("\n");
  insere_ordenado(50, &a1);
  imprime(a1);  printf("\n");
  insere_ordenado(25, &a1);
  imprime(a1);  printf("\n");
  insere_ordenado(10, &a1);
  imprime(a1);  printf("\n");
  insere_ordenado(5, &a1);
  imprime(a1);  printf("\n");
  insere_ordenado(31, &a1);
  imprime(a1);  printf("\n");

  a1=remover(5,a1);
  imprime(a1);  printf("\n");
  a1=remover(10,a1);
  imprime(a1);  printf("\n");
  a1=remover(15,a1);
  imprime(a1);  printf("\n");

}
