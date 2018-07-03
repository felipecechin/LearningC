#include <stdio.h>
#include <stdlib.h>

struct no {
  int valor;
  int alt;
  struct no* esq;
  struct no* dir;
};

typedef struct no arvore;

arvore *cria_vazia(){
  return NULL;
}

int esta_vazia(arvore *a){
  return a==NULL;
}

void imprime(arvore *a){
  if (!esta_vazia(a)){
     imprime(a->esq);
     printf("%i - %i\n", a->valor, a->alt);
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

int existe_valor(int valor, arvore *a){
  if (a!=NULL) {
    if (a->valor == valor) {
      return 1;
    } else {
      if (existe_valor(valor,a->esq) == 1) {
        return 1;
      }
      return existe_valor(valor,a->dir);
    }
  }
  return 0;
}

int conta_folhas(arvore *a) {
  int cont = 0;
  if (!esta_vazia(a)) {
    cont += 1;
    cont += conta_folhas(a->esq);
    cont += conta_folhas(a->dir);
  } else {
    return 0;
  }
  return cont;
}

int conta_folhas2(arvore *a) {
  if (!esta_vazia(a)) {
    return 1+conta_folhas(a->esq)+conta_folhas(a->dir);
  }
}

int sao_iguais2(arvore *a, arvore *b) {
  return ( (esta_vazia(a) && esta_vazia(b))
      || 
      (!esta_vazia(a) && !esta_vazia(b) && a->valor == b->valor && sao_iguais2(a->esq,b->esq) && sao_iguais2(a->dir,b->dir))
    );
}

int sao_iguais(arvore *a, arvore *b) {
  if (esta_vazia(a) && esta_vazia(b)) {
    return 1;
  } else if (esta_vazia(a) || esta_vazia(b)) {
    return 0;
  } else if (conta_folhas(a) != conta_folhas(b)) {
    return 0;
  } else if (a->valor == b->valor) {
    return sao_iguais(a->esq,b->esq) && sao_iguais(a->dir,b->dir);
  } else {
    return 0;
  }
}

int calcula_altura(arvore *a) {
  if (a == NULL) {
    return -1;
  }
  if (calcula_altura(a->dir) > calcula_altura(a->esq)) {
    return calcula_altura(a->dir)+1;
  } else {
    return calcula_altura(a->esq)+1;
  }
}

// int calcula_altura_sem_recursao(arvore *a) {
//   if (a == NULL) {
//     return -1;
//   }
//   if (calcula_altura(a->dir) > calcula_altura(a->esq)) {
//     return calcula_altura(a->dir)+1;
//   } else {
//     return calcula_altura(a->esq)+1;
//   }
// }

int alt_no(arvore *a) {
  if (a==NULL) {
    return -1;
  } else {
    return a->alt;
  }
}

int maior(int a, int b) {
  if (a>b) {
    return a;
  } else {
    return b;
  }
}

int calcula_altura2(arvore *a) {
  return maior(alt_no(a->esq),alt_no(a->dir))+1;
}

int calc_fb(arvore *a) {
  return alt_no(a->esq) - alt_no(a->dir);
}

void rotacao_ll(arvore **a) {
  arvore *b;
  b = (*a)->esq;
  (*a)->esq = b->dir;
  b->dir = (*a);
  (*a)->alt = calcula_altura2(*a);
  b->alt = calcula_altura2(b);
  (*a) = b;
}

void rotacao_rr(arvore **a) {
  arvore *b;
  b=(*a)->dir;
  (*a)->dir = b->esq;
  b->esq = (*a);
  (*a)->alt = calcula_altura2(*a);
  b->alt = calcula_altura2(b);
  (*a) = b;
}

void rotacao_lr(arvore **a) {
  rotacao_rr(&(*a)->esq);
  rotacao_ll(a);
}

void rotacao_rl(arvore **a) {
  rotacao_ll(&(*a)->esq);
  rotacao_rr(a);
}

void rebalanceia(arvore **a) {
  int fb = calc_fb(*a);
  if (fb>=2) { // a esquerda esta desbalanceada
    if (calc_fb((*a)->esq)>0) { //eh positivo, logo deve-se aplicar a rotacao LL
      printf("LL\n");
      fflush(stdout);
      rotacao_ll(a);
    } else { //o neto esta a direita logo LR
      printf("RL\n");
      fflush(stdout);
      rotacao_lr(a);
    }
  } else if (fb<=-2) { // a direita esta desbalanceada
    if (calc_fb((*a)->dir)<0) { // eh negativo, logo deve-se aplicar a rotacao RR
      printf("RR\n");
      fflush(stdout);
      rotacao_rr(a);
    } else { // o neto esta a esquerda, logo RL
      printf("RL\n");
      fflush(stdout);
      rotacao_rl(a);
    }
  }
}

arvore *insere_ordenado(int valor, arvore *a) {
  if (esta_vazia(a)) {
    a = cria_arvore(valor,cria_vazia(),cria_vazia());
  } else {
    if (valor < a->valor) {
      a->esq = insere_ordenado(valor, a->esq);
    } else {
      a->dir = insere_ordenado(valor, a->dir);
    }
  }
  a->alt = calcula_altura2(a);
  rebalanceia(&a);
  return a;
}

int existe_valor2(int valor,arvore *a) {
  if (esta_vazia(a)) {
    return 0;
  } else {
    return valor == a->valor||existe_valor2(valor,a->esq)||existe_valor2(valor,a->dir);
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
      b->valor = valor;
      a->esq = remover(a->esq, valor);
    }
  }
  
  a->alt = calcula_altura2(a);
  rebalanceia(&a);
}


void main(){/*
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
  arvore *raiz3=NULL;
  raiz3 = insere_ordenado(30,raiz3);
  raiz3 = insere_ordenado(20,raiz3);
  raiz3 = remover(raiz3,20);
  imprime(raiz3); printf("\n\n\n");
  // imprime(raiz3); 





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
*/}