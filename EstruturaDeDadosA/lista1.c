#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Alunos: Felipe Cechin e Fernando Garcia

struct no{
  int valor;
  struct no *proximo;
};

struct l_descr{
  struct no *inicio;
  int cnt;
  struct no *fim;
};

void inicializa_lista(struct l_descr *lista) {
  lista->inicio=NULL;
  lista->cnt=0;
  lista->fim=NULL;
}

void imprime_lista(struct l_descr *lista) 
{
  struct no *aux = lista->inicio;
  while(aux!=NULL) {
    printf("%d\n",aux->valor);
    aux = aux->proximo;
  }
}

int esta_vazia(struct l_descr *lista) {
  if (lista->inicio==NULL) {
    return 1;
  } else {
    return 0;
  }
}

void insere_lista_nula(struct l_descr *lista, int val) {
  lista->inicio = malloc(sizeof(struct no));
  lista->inicio->valor = val;
  lista->inicio->proximo = NULL;
  lista->cnt = 1;
  lista->fim = lista->inicio;
}

void insere_inicio(struct l_descr *lista,int val) {
  if (esta_vazia(lista)==1) {
    insere_lista_nula(lista,val);
  } else {
    struct no *novo = malloc(sizeof(struct no));
    novo->valor = val;
    novo->proximo = lista->inicio;
    lista->inicio = novo;
    lista->cnt++;
  }
}

void insere_fim(struct l_descr *lista, int  val) {
  if (esta_vazia(lista) == 1) {
    insere_lista_nula(lista,val);
  } else {
    if (lista->fim->proximo == NULL) {
      lista->fim->proximo = malloc(sizeof(struct no));
      lista->fim->proximo->valor = val;
      lista->fim->proximo->proximo = NULL;
      lista->fim = lista->fim->proximo;
      lista->cnt++;
    }
  }
}

void insere_ind(struct l_descr *lista, int val, int indice) {
  if (esta_vazia(lista) == 1) {
    insere_lista_nula(lista,val);
  } else {
    if (lista->cnt>indice) {
      struct no *novo = malloc(sizeof(struct no));
      novo->valor = val;
      if (indice <= 0) {
        insere_inicio(lista,val);
        return;
      }
      int i = 0;
      struct no *anterior = lista->inicio;
      while (i!=indice-1) {
        anterior = anterior->proximo;
        i++;
      }
      struct no *seguinte = anterior->proximo;
      anterior->proximo = malloc(sizeof(struct no));
      anterior->proximo->valor = val;
      anterior->proximo->proximo = seguinte;
      lista->cnt++;
    } else {
      insere_fim(lista,val);
    }
  }
}

int insere_ordenado(struct l_descr *lista, int val) {
  if (esta_vazia(lista) == 1) {
    insere_lista_nula(lista,val);
    return 0;
  } else {
    struct no *anterior = lista->inicio;
    int i = 0;
    while (val > anterior->valor) {
      anterior = anterior->proximo;
      i++;
      if (anterior == NULL) {
        insere_fim(lista,val);
        return lista->cnt-1;
      }
    }
    insere_ind(lista,val,i);
    return i;
  }
  return -1;
}

int remove_primeiro(struct l_descr *lista) {
  if (esta_vazia(lista) == 1) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      int valor = lista->inicio->valor;
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cnt = 0;
      return valor;
    } else {
      int valor = lista->inicio->valor;
      struct no *segundo = lista->inicio->proximo;
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cnt--;
      return valor;
    }
  }
  return -1;
}

int remove_ultimo(struct l_descr *lista) {
  if (esta_vazia(lista) == 1) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      int valor = lista->inicio->valor;
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cnt = 0;
      return valor;
    } else {
      struct no *penultimo = lista->inicio;
      struct no *ultimo = lista->fim;
      int valor_ultimo = lista->fim->valor;
      while (penultimo->proximo->proximo != NULL) {
        penultimo = penultimo->proximo;
      }
      penultimo->proximo = NULL;
      lista->fim = penultimo;
      free(ultimo);
      lista->cnt--;
      return valor_ultimo;
    }
  }
  return -1;
}

int remove_indice(struct l_descr *lista,int indice) {
  if (esta_vazia(lista) == 1) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (indice>=lista->cnt || indice<0) {
      printf("A lista nao possui valor nesse indice\n");
      return -1;
    } else {
      if (indice==0) {
        return remove_primeiro(lista);
      } else if (indice==lista->cnt-1) {
        return remove_ultimo(lista);
      }
      struct no *valor = lista->inicio;
      int cont=1;
      while(cont<indice){
        valor = valor->proximo;
        cont++;
      }
      struct no *proximo = valor->proximo->proximo;
      int valor_elemento = valor->proximo->valor;
      free(valor->proximo);
      valor->proximo = proximo;
      lista->cnt--;
      return valor_elemento;
    }
  }
  return -1;
}

int busca_indice(struct l_descr *lista, int val) {
  if (esta_vazia(lista) == 1) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    struct no *aux = lista->inicio;
    int i = 0;
    while(aux->valor!=val) {
      aux = aux->proximo;
      i++;
      if (aux == NULL) {
        return -1;
      }
    }
    return i;
  }
  return -1;
}

void remove_todos_da_lista(struct l_descr *lista) {
  int cont = lista->cnt;
  for (int i=0;i<cont;i++) {
    remove_primeiro(lista);
  }
}

int main() {
  struct l_descr lista1;

  inicializa_lista(&lista1);

  insere_inicio(&lista1,30);
  insere_inicio(&lista1,20);
  insere_inicio(&lista1,10);
  insere_inicio(&lista1,5);
  imprime_lista(&lista1);
  remove_todos_da_lista(&lista1);
  printf("----\n");
  imprime_lista(&lista1);
  return 0;
}