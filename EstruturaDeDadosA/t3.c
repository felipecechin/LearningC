#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <unistd.h> 

//Bruno Frizzo, Felipe Cechin e Fernando Garcia

struct no {
  char chave[255];
  char valor[255];
  struct no *proximo;
};

struct l_descr {
  struct no *inicio;
  int cnt;
  struct no *fim;
};

void inicializa_lista(struct l_descr *lista) {
  lista->inicio=NULL;
  lista->cnt=0;
  lista->fim=NULL;
}

bool esta_na_lista(struct l_descr *lista,char *chave) {
  struct no *aux = lista->inicio;
  while(aux != NULL) {
    if (strcmp(aux->chave,chave) == 0) {
      printf("chave: %s - valor: %s\n", aux->chave,aux->valor);
      return true;
    }
    aux = aux->proximo;
  }
  return false;
}

bool esta_na_lista_sem_print(struct l_descr *lista,char *chave) {
  struct no *aux = lista->inicio;
  while(aux != NULL) {
    if (strcmp(aux->chave,chave) == 0) {
      return true;
    }
    aux = aux->proximo;
  }
  return false;
}

void insere_lista_nula(struct l_descr *lista, char valor[255], char chave[255]) {
  lista->inicio = malloc(sizeof(struct no));
  strcpy(lista->inicio->chave, chave);
  strcpy(lista->inicio->valor, valor);
  lista->inicio->proximo = NULL;
  lista->cnt = 1;
  lista->fim = lista->inicio;
}

// void insere_inicio(struct l_descr *lista,char valor[], char chave[]) {
//   if (esta_vazia(lista)==1) {
//     insere_lista_nula(lista,valor,chave);
//   } else {
//     struct no *novo = malloc(sizeof(struct no));
//     strcpy(novo->chave,chave);
//     strcpy(novo->valor,valor);
//     novo->proximo = lista->inicio;
//     lista->inicio = novo;
//     lista->cnt++;
//   }
// }

void insere_fim(struct l_descr *lista, char valor[255], char chave[255]) {
  if (lista->inicio == NULL) {
    insere_lista_nula(lista,valor,chave);
  } else {
    if(!esta_na_lista(lista, chave)){
      lista->fim->proximo = malloc(sizeof(struct no));
      strcpy(lista->fim->proximo->chave, chave);
      strcpy(lista->fim->proximo->valor, valor);
      lista->fim->proximo->proximo = NULL;
      lista->fim = lista->fim->proximo;
      lista->cnt++;
    }else{
      struct no *aux = lista->inicio;
      while(aux != NULL){
        if(strcmp(aux->chave, chave) == 0){
          strcpy(aux->valor, valor);
          return;
        }
        aux = aux->proximo;
      }
    }
  }
}

int remove_primeiro(struct l_descr *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cnt = 0;
      return 1;
    } else {
      struct no *segundo = lista->inicio->proximo;
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cnt--;
      return 1;
    }
  }
  return -1;
}

int remove_ultimo(struct l_descr *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cnt = 0;
      return 1;
    } else {
      struct no *penultimo = lista->inicio;
      struct no *ultimo = lista->fim;
      while (penultimo->proximo->proximo != NULL) {
        penultimo = penultimo->proximo;
      }
      penultimo->proximo = NULL;
      lista->fim = penultimo;
      free(ultimo);
      lista->cnt--;
      return 1;
    }
  }
  return -1;
}

int remove_indice(struct l_descr *lista,int indice) {
  if (lista->inicio == NULL) {
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
      free(valor->proximo);
      valor->proximo = proximo;
      lista->cnt--;
      return 1;
    }
  }
  return -1;
}

bool remove_chave(struct l_descr *lista,char *chave) {
  struct no *aux = lista->inicio;
  int indice = 0;
  while(aux!=NULL) {
    if (strcmp(aux->chave,chave) == 0) {
      remove_indice(lista,indice);
      return true;
    }
    indice++;
    aux = aux->proximo;
  }
  return false;
}

void retira_barra_n(char *string) {
  char *pos;
  if ((pos=strchr(string, '\n')) != NULL) {
    *pos = '\0';
  }
}

void le_no(struct l_descr *lista){
  setbuf(stdin, 0);
  char chave[255];
  printf("Digite a chave do no:\n");
  fgets (chave, 255, stdin);
  retira_barra_n(chave);
  while (strlen(chave) == 0) {
    setbuf(stdin, 0);
    printf("Digite a chave do no:\n");
    fgets (chave, 255, stdin);
    retira_barra_n(chave);
  }

  setbuf(stdin, 0);
  char valor[255];
  printf("Digite o valor do no:\n");
  fgets (valor, 255, stdin);
  retira_barra_n(valor);
  while (strlen(valor) == 0) {
    setbuf(stdin, 0);
    printf("Digite o valor do no:\n");
    fgets (valor, 255, stdin);
    retira_barra_n(valor);
  }

  insere_fim(lista, valor, chave);
}

void exclusao(struct l_descr *lista) {
  setbuf(stdin, 0);
  char chave[255];
  printf("Digite a chave do no:\n");
  fgets (chave, 255, stdin);
  retira_barra_n(chave);
  while (strlen(chave) == 0 || !esta_na_lista(lista,chave)) {
    setbuf(stdin, 0);
    printf("Chave incorreta. ");
    printf("Digite a chave do no:\n");
    fgets (chave, 255, stdin);
    retira_barra_n(chave);
  }

  remove_chave(lista,chave);
}

int menu(){
  int opcao;


  printf("DICIONARIO\n");
  printf("Qual operacao voce deseja fazer?\n");
  printf("1 - Inclusao de chave-valor\n");
  printf("2 - Exclusao de chave\n");
  printf("3 - Ver quantidade de chave-valor\n");
  printf("4 - Imprimir todas as chaves do dicionario\n");
  printf("5 - Imprimir todos os valores do dicionario\n");
  printf("6 - Imprimir todos os elementos do dicionario (chave-valor)\n");
  printf("7 - Verificar se uma chave existe ou nao no dicionario\n");
  printf("8 - Sair\n");
  scanf("%d",&opcao);
  while(opcao<1 || opcao>8) {
    printf("Qual operacao voce deseja fazer?");
    scanf("%d",&opcao);
  }
  return opcao;
}

void imprimir_chaves_dicionario(struct l_descr *lista) {
  struct no *aux = lista->inicio;
  printf("Chaves: \n");
  while(aux!=NULL) {
    printf("- %s\n", aux->chave);
    aux = aux->proximo;
  }
}


void imprimir_valores_dicionario(struct l_descr *lista) {
  struct no *aux = lista->inicio;
  printf("Valores: \n");
  while(aux!=NULL) {
    printf("- %s\n", aux->valor);
    aux = aux->proximo;
  }
}

void imprimir_dicionario(struct l_descr *lista) {
  struct no *aux = lista->inicio;
  while(aux!=NULL) {
    printf("Chave-valor: %s - %s\n", aux->chave, aux->valor);
    aux = aux->proximo;
  }
}

void calculaTempo(struct timespec *ts1, struct timespec *ts2){
    if (ts2->tv_nsec < ts1->tv_nsec) {
        ts2->tv_nsec += 1000000000;
        ts2->tv_sec--;
    }
    printf("%ld.%09ld\n", (long)(ts2->tv_sec - ts1->tv_sec), ts2->tv_nsec - ts1->tv_nsec);
}

void verificar_chave_existe(struct l_descr *lista) {
  setbuf(stdin, 0);
  char chave[255];
  printf("Digite a chave do no:\n");
  fgets (chave, 255, stdin);
  retira_barra_n(chave);
  while (strlen(chave) == 0) {
    setbuf(stdin, 0);
    printf("Digite a chave do no:\n");
    fgets (chave, 255, stdin);
    retira_barra_n(chave);
  }

  if (esta_na_lista(lista,chave)) {
    printf("A chave esta no dicionario\n");
  } else {
    printf("Chave nao existe no dicionario\n");
  }
}

void menor_elemento(struct l_descr *lista) {
  struct no *menor = lista->inicio;
  struct no *aux = lista->inicio->proximo;
  while(aux!=NULL) {
    if (strcmp(menor->chave,aux->chave) < 0) {
      menor = aux;
    }
    aux = aux->proximo;
  }
  printf("chave: %s - valor: %s\n",menor->chave,menor->valor);
}

void maior_elemento(struct l_descr *lista) {
  struct no *maior = lista->inicio;
  struct no *aux = lista->inicio->proximo;
  while(aux!=NULL) {
    if (strcmp(maior->chave,aux->chave) > 0) {
      maior = aux;
    }
    aux = aux->proximo;
  }
  printf("chave: %s - valor: %s\n",maior->chave,maior->valor);
}

int main() {

  // int opcao = menu();
  struct timespec ini, fim;
  struct l_descr lista;
  inicializa_lista(&lista);
  char x[256];


  //CRESCENTE DE 1 A 50000
  clock_gettime(CLOCK_REALTIME, &ini); 
  for (int i=1;i<500001;i++) {
    sprintf(x, "%07d", i);
    insere_fim(&lista, x, x);
  }
  printf("Primeiro elemento inserido:\n");
  strcpy(x,"0000001");
  esta_na_lista(&lista,x);
  printf("Ultimo elemento inserido: \n");
  strcpy(x,"0500000");
  esta_na_lista(&lista,x);
  clock_gettime(CLOCK_REALTIME, &fim);
  printf("TEMPO: ");
  calculaTempo(&ini, &fim);


  //DECRESCENTE DE 1 A 50000
  // clock_gettime(CLOCK_REALTIME, &ini); 
  // for (int i=500001;i>0;i--) {
  //   sprintf(x, "%07d", i);
  //   insere_fim(&lista, x, x);
  // }
  // printf("Primeiro elemento inserido:\n");
  // strcpy(x,"0500001");
  // esta_na_lista(&lista,x);
  // printf("Ultimo elemento inserido: \n");
  // strcpy(x,"0000001");
  // esta_na_lista(&lista,x);
  // clock_gettime(CLOCK_REALTIME, &fim);
  // printf("TEMPO: ");
  // calculaTempo(&ini, &fim);


  //ALEATORIA
  // clock_gettime(CLOCK_REALTIME, &ini); 
  // srand(time(NULL));
  // int num;
  // for (int i=1;i<500001;i++) {
  //   num = rand()%2147483647;
  //   sprintf(x, "%11d", num);
  //   while(esta_na_lista_sem_print(&lista, x)) {
  //     num = rand()%2147483647;
  //     sprintf(x, "%11d", num);
  //   }
  //   insere_fim(&lista, x, x);
  // }
  // printf("Menor elemento inserido:\n");
  // menor_elemento(&lista);
  // printf("Maior elemento inserido: \n");
  // maior_elemento(&lista);
  // clock_gettime(CLOCK_REALTIME, &fim);
  // printf("TEMPO: ");
  // calculaTempo(&ini, &fim);






  // while(true){
  //   switch(opcao){
  //     case 1:
  //       le_no(&lista);
  //       printf("Chave-valor incluida no dicionario com sucesso!\n");
  //     break;
  //     case 2:
  //       if (lista.inicio == NULL) {
  //         printf("O dicionario nao possui nenhuma chave-valor.\n");
  //         break;
  //       }
  //       exclusao(&lista);
  //       printf("Chave excluida com sucesso!\n");
  //     break;
  //     case 3:
  //       printf("Quantidade de chaves-valores: %d\n",lista.cnt);
  //     break;
  //     case 4:
  //       if (lista.inicio == NULL) {
  //         printf("O dicionario nao possui nenhuma chave-valor.\n");
  //         break;
  //       }
  //       imprimir_chaves_dicionario(&lista);
  //     break;
  //     case 5:
  //       if (lista.inicio == NULL) {
  //         printf("O dicionario nao possui nenhuma chave-valor.\n");
  //         break;
  //       }
  //       imprimir_valores_dicionario(&lista);
  //     break;
  //     case 6:
  //       if (lista.inicio == NULL) {
  //         printf("O dicionario nao possui nenhuma chave-valor.\n");
  //         break;
  //       }
  //       imprimir_dicionario(&lista);
  //     break;
  //     case 7:
  //       if (lista.inicio == NULL) {
  //         printf("O dicionario nao possui nenhuma chave-valor.\n");
  //         break;
  //       }
  //       verificar_chave_existe(&lista);
  //     break;
  //     case 8:
  //       printf("Fim do programa\n");
  //       return 0;
  //     break;
  //   }
  //   printf("\n\n");
  //   opcao = menu();
  // }
}