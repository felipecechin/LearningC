#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Aluno: Felipe Cechin 

struct no{
  struct no *anterior;
  int valor;
  struct no *proximo;
};

struct l_descr{
  struct no *inicio;
  int cnt;
  struct no *fim;
};

struct l_descr_circ {
  struct no *inicio;
  int cnt;
};

void inicializa_lista_circ(struct l_descr_circ *lista) {
  lista->inicio = NULL;
  lista->cnt = 0;
}

void insere_lista_nula_circ(struct l_descr_circ *lista, int val) {
  lista->inicio = malloc(sizeof(struct no));
  lista->inicio->anterior = NULL;
  lista->inicio->valor = val;
  lista->inicio->proximo = NULL;
  lista->cnt = 1;
}

void insere_fim_circ(struct l_descr_circ *lista, int  val) {
  if (lista->inicio == NULL) {
    insere_lista_nula_circ(lista,val);
  } else if (lista->cnt==1){
    lista->inicio->proximo = malloc(sizeof(struct no));
    lista->inicio->anterior = lista->inicio->proximo;
    lista->inicio->proximo->proximo = lista->inicio;
    lista->inicio->proximo->anterior = lista->inicio;
    lista->inicio->proximo->valor = val;
    lista->cnt++;
  } else {
    struct no *aux = lista->inicio->anterior;
    struct no *novo = malloc(sizeof(struct no));
    novo->valor = val;
    novo->anterior = aux;
    novo->proximo = lista->inicio;
    aux->proximo->anterior = novo;
    aux->proximo = novo;
    lista->cnt++;
  }
}

void imprime_lista_circ(struct l_descr_circ *lista) {
  struct no *aux = lista->inicio;
  int cont = 0;
  while(aux!=NULL && cont<lista->cnt) {
    printf("%d\n",aux->valor);
    aux = aux->proximo;
    cont++;
  }
}

void copia_inv(struct l_descr_circ *lista1,struct l_descr_circ *lista2) {
  if (lista1->inicio!=NULL) {
    printf("A lista 1 nao esta vazia\n");
    return;
  }
  if (lista2->inicio==NULL) {
    printf("A lista 2 esta vazia\n");
    return;
  }
  if (lista2->cnt==1) {
    lista1->inicio = malloc(sizeof(struct no));
    lista1->inicio->anterior = NULL;
    lista1->inicio->valor = lista2->inicio->valor;
    lista1->inicio->proximo = NULL;
    lista1->cnt=1;
  } else {
    struct no *aux = lista2->inicio->anterior;
    struct no *aux2;
    int cont = 0;
    while (aux!=NULL && cont<lista2->cnt) {
      if (lista1->inicio == NULL) {
        lista1->inicio = malloc(sizeof(struct no));
        lista1->inicio->anterior = NULL;
        lista1->inicio->valor = aux->valor;
        lista1->inicio->proximo = NULL;
        lista1->cnt=1;
        aux2 = lista1->inicio;
      } else {
        aux2->proximo = malloc(sizeof(struct no));
        aux2->proximo->anterior = aux2;
        aux2->proximo->valor = aux->valor;
        if (cont==lista2->cnt-1) {
          aux2->proximo->proximo = lista1->inicio;
          lista1->inicio->anterior = aux2;
        } else {
          aux2->proximo->proximo = NULL;
        }
        aux2 = aux2->proximo;
        lista1->cnt++;
      }
      aux = aux->anterior;
      cont++;
    }
  }
}

void remove_pares(struct l_descr_circ *lista) {
  if (lista->inicio==NULL) {
    return;
  }
  if (lista->cnt==1) {
    return;
  }
  if (lista->cnt==2) {
    free(lista->inicio->proximo);
    lista->inicio->proximo = NULL;
    lista->inicio->anterior = NULL;
    return;
  }
  struct no *aux = lista->inicio;
  int cont = 1;
  int cont_lista = lista->cnt;
  while (aux!=NULL && cont<=cont_lista) {
    if (cont%2==0) {
      aux->anterior->proximo = aux->proximo;
      struct no *aux2 = aux;
      aux->proximo->anterior = aux->anterior;
      aux = aux->proximo;
      free(aux2);
      lista->cnt--;
    } else {
      aux = aux->proximo;
    }
    cont++;
  }
}

void intercala(struct l_descr_circ *lista1,struct l_descr_circ *lista2) {
  if (lista1->inicio == NULL || lista2->inicio == NULL) {
    return;
  }
  struct no *aux1 = lista1->inicio;
  struct no *aux2 = lista2->inicio;
  if (lista1->cnt==1) {
    aux1->proximo = aux2;
    if (aux2->anterior!=NULL) {
      aux2->anterior->proximo = aux1;
      aux1->anterior = aux2->anterior;
    } else {
      aux1->anterior = aux2;
      aux2->proximo = aux1;
      aux2->anterior = aux1;
    }
    lista1->cnt += lista2->cnt;
    return;
  }

  int cont = 0;
  struct no *inicio_lista1 = aux1;
  struct no *ultimo_lista2 = aux2->anterior;
  while(cont<lista2->cnt) {
    struct no *proximo2 = aux2->proximo;
    struct no *proximo = aux1->proximo;
    if (proximo == inicio_lista1) {
      aux1->proximo = aux2;
      aux2->anterior = aux1;
      proximo->anterior = ultimo_lista2;
      ultimo_lista2->proximo = inicio_lista1;
      break;
    }
    aux1->proximo = aux2;
    proximo->anterior = aux2;
    aux2->anterior = aux1;
    aux2->proximo = proximo;
    aux2 = proximo2;
    aux1 = proximo;
    cont++;
  }
  lista1->cnt += lista2->cnt;
}

void inicializa_lista(struct l_descr *lista) {
  lista->inicio=NULL;
  lista->cnt=0;
  lista->fim=NULL;
}

void imprime_lista(struct l_descr *lista) {
  struct no *aux = lista->inicio;
  while(aux!=NULL) {
    printf("%d\n",aux->valor);
    aux = aux->proximo;
  }
}

int sao_iguais(struct l_descr *lista1,struct l_descr *lista2) {
  if (lista1->cnt != lista2->cnt) {
    return 0;
  } else if (lista1->inicio==NULL && lista2->inicio==NULL) {
    return 1;
  } else if (lista1->cnt == 1 && lista1->inicio->valor == lista2->inicio->valor) {
    return 1;
  } else if (lista1->cnt > 1) {
    if (lista1->inicio->valor != lista2->inicio->valor || lista1->fim->valor != lista2->fim->valor) {
      return 0;
    }
    struct no *aux = lista1->inicio->proximo;
    struct no *aux2 = lista2->inicio->proximo;
    bool iguais = false;
    while (aux->valor == aux2->valor) {
      aux = aux->proximo;
      aux2 = aux2->proximo;
      if (aux == NULL && aux2 == NULL) {
        iguais = true;
        break;
      }
    }
    if (iguais) {
      return 1;
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}

void copiar(struct l_descr *lista1,struct l_descr *lista2) {
  if (lista2->inicio != NULL) {
    printf("A lista 2 nao esta vazia\n");
    return;
  } else if (lista1->inicio == NULL) {
    printf("A lista 1 esta vazia\n");
    return;
  } else if (lista1->cnt == 1) {
    lista2->inicio = malloc(sizeof(struct no));
    lista2->inicio->anterior = NULL;
    lista2->inicio->valor = lista1->inicio->valor;
    lista2->inicio->proximo = NULL;
    lista2->cnt = 1;
    lista2->fim = lista2->inicio;
  } else {
    struct no *aux = lista1->inicio;
    struct no *aux2 = NULL; 
    int i = 0;
    while (aux != NULL) {
      if (i==0) {
        aux2 = malloc(sizeof(struct no));
        aux2->anterior = NULL;
        aux2->valor = aux->valor;
        aux2->proximo = NULL;
        lista2->inicio = aux2;
        lista2->cnt = 1;
        lista2->fim = aux2;
      } else {
        aux2->proximo = malloc(sizeof(struct no));
        aux2->proximo->anterior = aux2;
        aux2->proximo->proximo = NULL;
        aux2->proximo->valor = aux->valor;
        lista2->cnt++;
        lista2->fim = aux2->proximo;
        aux2 = aux2->proximo;
      }
      aux = aux->proximo;
      i++;
    }
  }
}

bool esta_na_lista(struct l_descr *lista,int val) {
  struct no *aux = lista->inicio;
  while (aux!=NULL) {
    if (aux->valor == val) {
      return true;
    }
    aux = aux->proximo;
  }
  return false;
}

void insere_ordenado(struct l_descr *lista,int val) {
  if (lista->inicio == NULL) {
    lista->inicio = malloc(sizeof(struct no));
    lista->inicio->valor = val;
    lista->inicio->anterior = NULL;
    lista->inicio->proximo = NULL;
    lista->cnt = 1;
    lista->fim = lista->inicio;
  } else {
    if (val<=lista->inicio->valor) {
      struct no *aux = malloc(sizeof(struct no));
      aux->valor = val;
      aux->anterior = NULL;
      aux->proximo = lista->inicio;
      lista->inicio = aux;
      lista->cnt++;
      aux->proximo->anterior = aux;
    } else if (val>=lista->fim->valor) {
      struct no *aux = malloc(sizeof(struct no));
      aux->valor = val;
      aux->anterior = lista->fim;
      aux->proximo = NULL;
      aux->anterior->proximo = aux;
      lista->fim = aux;
      lista->cnt++;
    } else {
      struct no *aux = lista->inicio;
      while(aux->valor<val) {
        aux = aux->proximo;
      }
      struct no *novo = malloc(sizeof(struct no));
      novo->valor = val;
      novo->proximo = aux;
      lista->cnt++;
      novo->anterior = aux->anterior;
      aux->anterior->proximo = novo;
      aux->anterior = novo;
    }
  }
}

void diferenca_ordenada(struct l_descr *L,struct l_descr *lista1,struct l_descr *lista2) {
  if (lista1->inicio == NULL) {
    printf("A lista 1 esta vazia\n");
    return;
  }
  if (lista2->inicio == NULL) {
    copiar(lista1,L);
    return;
  }
  struct no *aux = lista1->inicio;
  struct no *aux2 = lista2->inicio;
  while(aux!=NULL) {
    if (aux->valor < aux2->valor) {
      insere_ordenado(L,aux->valor);
      aux = aux->proximo;
    } else if (aux->valor == aux2->valor){
      aux = aux->proximo;
    } else {
      if (aux2->proximo == NULL) {
        insere_ordenado(L,aux->valor);
        aux = aux->proximo;
      } else {
        aux2 = aux2->proximo;
      }
    }
  }
}

void diferenca(struct l_descr *L,struct l_descr *lista1,struct l_descr *lista2) {
  if (lista1->inicio == NULL) {
    printf("A lista 1 esta vazia\n");
    return;
  }
  if (lista2->inicio == NULL) {
    copiar(lista1,L);
    return;
  }
  struct no *aux = lista1->inicio;
  while(aux!=NULL) {
    if (!esta_na_lista(lista2,aux->valor)) {
      if (L->inicio == NULL) {
        L->inicio = malloc(sizeof(struct no));
        L->inicio->anterior = NULL;
        L->inicio->valor = aux->valor;
        L->inicio->proximo = NULL;
        L->cnt = 1;
        L->fim = L->inicio;
      } else {
        L->fim->proximo = malloc(sizeof(struct no));
        L->fim->proximo->valor = aux->valor;
        L->fim->proximo->anterior = L->fim;
        L->fim->proximo->proximo = NULL;
        L->fim = L->fim->proximo;
        L->cnt++;
      }
    }
    aux = aux->proximo;
  }
}

int comuns(struct l_descr *lista1,struct l_descr *lista2) {
  if (lista1->inicio == NULL || lista2->inicio == NULL) {
    return 0;
  }
  struct no *aux = lista1->inicio;
  struct no *aux2 = lista2->inicio;
  int cont = 0;
  while(aux!=NULL && aux2!=NULL) {
    if (aux->valor < aux2->valor) {
      aux = aux->proximo;
    } else if (aux->valor == aux2->valor){
      cont++;
      while(aux2!=NULL) {
        if (aux2->valor == aux->valor) {
          aux2 = aux2->proximo;
        } else {
          break;
        }
      }
      aux = aux->proximo;
    } else {
      if (aux2->proximo == NULL) {
        aux = aux->proximo;
      } else {
        aux2 = aux2->proximo;
      }
    }
  }
  return cont;
}

void destroi(struct l_descr *lista) {
  if (lista->inicio==NULL) {
    return;
  } else if (lista->cnt==1) {
    free(lista->inicio);
    lista->inicio = NULL;
    lista->cnt = 0;
    lista->fim = NULL;
  } else {
    struct no *aux = NULL;
    struct no *aux2 = lista->inicio->proximo;
    free(lista->inicio);
    do{
      aux = aux2;
      aux2 = aux2->proximo;
      free(aux);
    }while(aux2!=NULL);
    lista->inicio = NULL;
    lista->cnt = 0;
    lista->fim = NULL;
  }
}

void insere_lista_nula(struct l_descr *lista, int val) {
  lista->inicio = malloc(sizeof(struct no));
  lista->inicio->anterior = NULL;
  lista->inicio->valor = val;
  lista->inicio->proximo = NULL;
  lista->cnt = 1;
  lista->fim = lista->inicio;
}

void insere_inicio(struct l_descr *lista,int val) {
  if (lista->inicio == NULL) {
    insere_lista_nula(lista,val);
  } else {
    struct no *novo = malloc(sizeof(struct no));
    novo->anterior = NULL;
    novo->valor = val;
    novo->proximo = lista->inicio;
    lista->inicio->anterior = novo;
    lista->inicio = novo;
    lista->cnt++;
  }
}

int eh_inversa(struct l_descr *lista1,struct l_descr *lista2) {
  if (lista1->inicio == NULL || lista2->inicio == NULL) {
    return 0;
  }
  if (lista1->cnt!=lista2->cnt) {
    return 0;
  } else if (lista1->cnt > lista2->cnt) {
    return -2;
  } else if (lista1->cnt < lista2->cnt) {
    return -1;
  } else if (lista1->cnt==lista2->cnt) {
    if (lista1->cnt == 1 && lista1->inicio->valor == lista2->inicio->valor) {
      return 1;
    } else {
      struct no *aux1 = lista1->inicio;
      struct no *aux2 = lista2->fim;
      bool inversa = false;
      while (aux1->valor == aux2->valor) {
        aux1 = aux1->proximo;
        aux2 = aux2->anterior;
        if (aux1 == NULL && aux2 == NULL) {
          inversa = true;
          break;
        }
      }
      if (inversa) {
        return 1;
      } else {
        return 0;
      }
    }
  } else {
    return 0;
  }
}

void remove_impares(struct l_descr *lista) {
  if (lista->inicio==NULL) {
    return;
  }
  if (lista->cnt==1) {
    free(lista->inicio);
    lista->inicio = NULL;
    lista->cnt = 0;
    lista->fim = NULL;
  }
  struct no *aux = lista->inicio;
  int cont = 1;
  while (aux!=NULL) {
    if (cont%2==1) {
      if (cont==1) {
        aux->proximo->anterior = NULL;
        struct no *aux2 = aux->proximo;
        free(lista->inicio);
        lista->inicio = aux2;
        aux = aux2;
        lista->cnt--;
      } else {
        aux->anterior->proximo = aux->proximo;
        if (aux->proximo!=NULL) {
          struct no *aux2 = aux;
          aux->proximo->anterior = aux->anterior;
          aux = aux->proximo;
          free(aux2);
          lista->cnt--;
        } else {
          lista->fim = aux->anterior;
          aux->anterior->proximo = NULL;
          lista->cnt--;
          free(aux);
          break;
        }
      }
    } else {
      aux = aux->proximo;
    }
    cont++;
  }
}

int main() {
  struct l_descr lista1;
  struct l_descr lista2;
  struct l_descr lista_diferenca;

  inicializa_lista(&lista1);
  inicializa_lista(&lista2);
  inicializa_lista(&lista_diferenca);

  insere_inicio(&lista1,25);
  insere_inicio(&lista1,20);
  insere_inicio(&lista1,10);

  insere_inicio(&lista2,10);
  insere_inicio(&lista2,20);
  insere_inicio(&lista2,25);
  insere_inicio(&lista2,30);
  
  remove_impares(&lista2);


  imprime_lista(&lista2);
  printf("Sao inversas:%d\n",eh_inversa(&lista1,&lista2));
  destroi(&lista1);
  printf("----\n");

  imprime_lista(&lista1);
  printf("----\n");
  imprime_lista(&lista2);
  printf("----\n");

  struct l_descr_circ lista_circ1;
  struct l_descr_circ lista_circ2;

  inicializa_lista_circ(&lista_circ1);
  inicializa_lista_circ(&lista_circ2);

  insere_fim_circ(&lista_circ1,20);
  insere_fim_circ(&lista_circ1,40);
  insere_fim_circ(&lista_circ2,30);
  insere_fim_circ(&lista_circ2,50);
  
  imprime_lista_circ(&lista_circ1);
  printf("-----\n");
  remove_pares(&lista_circ1);
  imprime_lista_circ(&lista_circ1);
  return 0;
}