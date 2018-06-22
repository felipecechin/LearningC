#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Aluno: Felipe Cechin Mello

// Considere uma lista de carros, onde cada carro possui os seguintes campos: placa, marca e ano. Crie um programa com os seguintes requisitos:
// 1. A lista deve ser ordenada fisicamente pela placa dos carros.
// 2. Deve ser possivel incluir e excluir carros na lista.
// 3. Deve ser mantida em memória uma árvore binária relativa à placa dos carros.
// 4. Deve ser mantida em memória uma árvore binária cujo percurso seja equivalente à lista ordenada pelo marca.
// 5. Deve ser mantida em memória uma árvore binária cujo percurso seja equivalente à lista ordenada pela ano.
// 6. Deve ser possível buscar carros pela placa, usando a árvore binária auxiliar.
// 7. Deve ser possivel listar os carros ordenadamente pela placa, percorrendo a lista.
// 8. Deve ser possivel listar os carros ordenadamente pelo marca, através da árvore auxiliar.
// 9. Deve ser possivel listar os carros ordenadamente pela ano, através da árvore auxiliar.

struct carro {
  char placa[10];
  char marca[50];
  int ano;
};

void imprime_carro(struct carro *carro) {
  printf("PLACA: %s | ",carro->placa);
  printf("MARCA: %s | ",carro->marca);
  printf("ANO: %d\n",carro->ano);
}

// LISTAS //
 
struct no {
  struct carro *carro;
  struct no *proximo;
};

struct l_descr{
  struct no *inicio;
  int cont;
  struct no *fim;
};

void inicializa_lista(struct l_descr *lista) {
  lista->inicio=NULL;
  lista->cont=0;
  lista->fim=NULL;
}

void insere_lista_nula(struct l_descr *lista, struct carro *carro) {
  lista->inicio = malloc(sizeof(struct no));
  lista->inicio->carro = carro;
  lista->inicio->proximo = NULL;
  lista->cont = 1;
  lista->fim = lista->inicio;
}

void insere_inicio(struct l_descr *lista, struct carro *carro) {
  if (lista->inicio==NULL) {
    insere_lista_nula(lista,carro);
  } else {
    struct no *novo = malloc(sizeof(struct no));
    novo->carro = carro;
    novo->proximo = lista->inicio;
    lista->inicio = novo;
    lista->cont++;
  }
}

void insere_fim(struct l_descr *lista, struct carro *carro) {
  if (lista->inicio==NULL) {
    insere_lista_nula(lista,carro);
  } else {
    lista->fim->proximo = malloc(sizeof(struct no));
    lista->fim->proximo->carro = carro;
    lista->fim->proximo->proximo = NULL;
    lista->fim = lista->fim->proximo;
    lista->cont++;
  }
}

void insere_ind(struct l_descr *lista, struct carro *carro, int indice) {
  if (lista->inicio==NULL) {
    insere_lista_nula(lista,carro);
  } else {
    if (lista->cont>indice) {
      struct no *novo = malloc(sizeof(struct no));
      novo->carro = carro;
      if (indice <= 0) {
        insere_inicio(lista,carro);
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
      anterior->proximo->carro = carro;
      anterior->proximo->proximo = seguinte;
      lista->cont++;
    } else {
      insere_fim(lista,carro);
    }
  }
}

int insere_ordenado(struct l_descr *lista, struct carro *carro) {
  if (lista->inicio==NULL) {
    insere_lista_nula(lista,carro);
    return 0;
  } else {
    struct no *anterior = lista->inicio;
    int i = 0;
    while (strcmp(carro->placa, anterior->carro->placa) > 0) {
      anterior = anterior->proximo;
      i++;
      if (anterior == NULL) {
        insere_fim(lista,carro);
        return lista->cont-1;
      }
    }
    insere_ind(lista,carro,i);
    return i;
  }
  return -1;
}

void imprime_lista(struct l_descr *lista) {
  if (lista->inicio==NULL) {
    printf("Nao ha carros cadastrados.\n");
    return;
  }
  struct no *aux = lista->inicio;
  while(aux!=NULL) {
    imprime_carro(aux->carro);
    aux = aux->proximo;
  }
}

void remove_primeiro(struct l_descr *lista) {
  if (lista->inicio==NULL) {
    printf("A lista esta vazia\n");
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
    } else {
      struct no *segundo = lista->inicio->proximo;
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
    }
  }
}

void remove_ultimo(struct l_descr *lista) {
  if (lista->inicio==NULL) {
    printf("A lista esta vazia\n");
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
    } else {
      struct no *penultimo = lista->inicio;
      struct no *ultimo = lista->fim;
      while (penultimo->proximo->proximo != NULL) {
        penultimo = penultimo->proximo;
      }
      penultimo->proximo = NULL;
      lista->fim = penultimo;
      free(ultimo);
      lista->cont--;
    }
  }
}

void remove_indice(struct l_descr *lista,int indice) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
  } else {
    if (indice>=lista->cont || indice<0) {
      printf("A lista nao possui valor nesse indice\n");
      return;
    } else {
      if (indice==0) {
        remove_primeiro(lista);
        return;
      } else if (indice==lista->cont-1) {
        remove_ultimo(lista);
        return;
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
      lista->cont--;
    }
  }
}

void remove_carro_lista(struct l_descr *lista,struct carro *carro) {
  struct no *aux = lista->inicio;
  int indice = 0;
  while(aux!=NULL) {
    if (aux->carro == carro) {
      remove_indice(lista,indice);
      return;
    }
    indice++;
    aux = aux->proximo;
  }
}

//ARVORES //

struct arvore {
  struct carro *carro;
  struct arvore *esq;
  struct arvore *dir;
};


struct arvore *cria_vazia(){
  return NULL;
}

int esta_vazia(struct arvore *a){
  return a==NULL;
}

void imprime(struct arvore *a){
  if (!esta_vazia(a)) {
     imprime(a->esq);
     imprime_carro(a->carro);
     imprime(a->dir);
  }
}

struct arvore *cria_arvore(struct carro *carro, struct arvore *sae,struct arvore *sad) {
  struct arvore *arvore = malloc(sizeof(arvore));
  arvore->carro = carro;
  arvore->esq = sae;
  arvore->dir = sad;
  return arvore;
}

struct arvore *desaloca_arvore(struct arvore *a){
  if (a!=NULL) {
    desaloca_arvore(a->esq);
    desaloca_arvore(a->dir);
    free(a);
  }
  return NULL;
}

struct arvore *insere_ordenado_arvore_placa(struct carro *carro,struct arvore *a) {
  if (esta_vazia(a)) {
    a = cria_arvore(carro,cria_vazia(),cria_vazia());
  } else {
    if (strcmp(carro->placa,a->carro->placa) < 0) {
      a->esq = insere_ordenado_arvore_placa(carro,a->esq);
    } else {
      a->dir = insere_ordenado_arvore_placa(carro,a->dir);
    }
  }
  return a;
}

struct arvore *remove_arvore_placa(struct arvore* a, struct carro *carro) {
  if (esta_vazia(a)) 
    return NULL;
  if (strcmp(carro->placa,a->carro->placa) < 0)
    a->esq = remove_arvore_placa(a->esq, carro);
  else if (strcmp(carro->placa,a->carro->placa) > 0)
    a->dir = remove_arvore_placa(a->dir, carro);
  else {
    if ((a->esq == NULL) && (a->dir == NULL)){
      free(a);
      a = NULL;
    } else if (a->esq == NULL){
      struct arvore* t = a;
      a = a->dir;
      free(t);
    } else if (a->dir == NULL){
      struct arvore* t = a;
      a = a->esq;
      free(t);
    } else {
      struct arvore* f = a->esq;
      while (f->dir != NULL)
         f = f->dir;
      a->carro = f->carro;
      f->carro = carro;
      a->esq = remove_arvore_placa(a->esq, carro);
    }
  }
  return a; 
}

bool carro_existe_arvore_placa(struct arvore *a, char *placa) {
  if (esta_vazia(a)) {
    return false;
  } else {
    return strcmp(a->carro->placa,placa) == 0
    ||carro_existe_arvore_placa(a->esq,placa)
    ||carro_existe_arvore_placa(a->dir,placa);
  }
}

struct carro *buscar_carro_arvore_placa(struct arvore *a, char *placa) {
  if (a == NULL) 
    return NULL;
  else if (strcmp(placa,a->carro->placa) < 0) 
    return buscar_carro_arvore_placa(a->esq, placa);
  else if (strcmp(placa,a->carro->placa) > 0) 
    return buscar_carro_arvore_placa(a->dir, placa);
  else if (strcmp(placa,a->carro->placa) == 0)
    return a->carro;
  else 
    return NULL;
}

struct arvore *insere_ordenado_arvore_marca(struct carro *carro,struct arvore *a) {
  if (esta_vazia(a)) {
    a = cria_arvore(carro,cria_vazia(),cria_vazia());
  } else {
    if (strcmp(carro->marca,a->carro->marca) < 0) {
      a->esq = insere_ordenado_arvore_marca(carro,a->esq);
    } else {
      a->dir = insere_ordenado_arvore_marca(carro,a->dir);
    }
  }
  return a;
}

struct arvore *remove_arvore_marca(struct arvore* a, struct carro *carro) {
  if (esta_vazia(a)) 
    return NULL;
  if (strcmp(carro->marca,a->carro->marca) < 0)
    a->esq = remove_arvore_marca(a->esq, carro);
  else if (strcmp(carro->marca,a->carro->marca) > 0)
    a->dir = remove_arvore_marca(a->dir, carro);
  else {
    if ((a->esq == NULL) && (a->dir == NULL)){
      free(a);
      a = NULL;
    } else if (a->esq == NULL) {
      struct arvore* t = a;
      a = a->dir;
      free(t);           
    } else if (a->dir == NULL) {
      struct arvore* t = a;
      a = a->esq;
      free(t);           
    } else {
      struct arvore* f = a->esq;
      while (f->dir != NULL)
         f = f->dir;
      a->carro = f->carro;
      f->carro = carro;
      a->esq = remove_arvore_marca(a->esq, carro);
    }
  }
  return a; 
}

struct arvore *insere_ordenado_arvore_ano(struct carro *carro,struct arvore *a) {
  if (esta_vazia(a)) {
    a = cria_arvore(carro,cria_vazia(),cria_vazia());
  } else {
    if (carro->ano < a->carro->ano) {
      a->esq = insere_ordenado_arvore_ano(carro,a->esq);
    } else {
      a->dir = insere_ordenado_arvore_ano(carro,a->dir);
    }
  }
  return a;
}

struct arvore *remove_arvore_ano(struct arvore* a, struct carro *carro) {
  if (esta_vazia(a)) 
    return NULL;
  if (carro->ano < a->carro->ano)
    a->esq = remove_arvore_ano(a->esq, carro);
  else if (carro->ano > a->carro->ano)
    a->dir = remove_arvore_ano(a->dir, carro);
  else {
    if ((a->esq == NULL) && (a->dir == NULL)){
      free(a);
      a = NULL;
    } else if (a->esq == NULL) {
      struct arvore* t = a;
      a = a->dir;
      free(t);           
    } else if (a->dir == NULL) {
      struct arvore* t = a;
      a = a->esq;
      free(t);           
    } else {
      struct arvore* f = a->esq;
      while (f->dir != NULL)
         f = f->dir;
      a->carro = f->carro;
      f->carro = carro;
      a->esq = remove_arvore_ano(a->esq, carro);
    }
  }
  return a; 
}

void liberar_memoria(struct l_descr *lista, struct arvore *arvore_ano,
                     struct arvore *arvore_marca, struct arvore *arvore_placa) {
  int cont = lista->cont;
  for (int i=0;i<cont;i++) {
    struct carro *carro = lista->inicio->carro;
    arvore_ano = remove_arvore_ano(arvore_ano,carro);
    arvore_marca = remove_arvore_marca(arvore_marca,carro);
    arvore_placa = remove_arvore_placa(arvore_placa,carro);
    remove_carro_lista(lista,carro);
    free(carro);
  }
}

void imprimir_menu() {
  printf("MENU:\n");
  printf("1 - Incluir carros\n");
  printf("2 - Excluir carros\n");
  printf("3 - Buscar carros\n");
  printf("4 - Listar carros ordenadamente pela placa\n");
  printf("5 - Listar carros ordenadamente pela marca\n");
  printf("6 - Listar carros ordenadamente pelo ano\n");
  printf("0 - Sair do programa\n");
}

int ler_opcao_menu() {
  int menu = 0;
  imprimir_menu();
  printf("\n");
  printf("Digite sua opcao do menu: \n");
  setbuf(stdin, 0);
  scanf("%d",&menu);
  while(menu<0 || menu>6) {
    setbuf(stdin, 0);
    printf("Digite sua opcao do menu: \n");
    scanf("%d",&menu);
  }
  return menu;
}

void retira_barra_n(char *string) {
  char *pos;
  if ((pos=strchr(string, '\n')) != NULL) {
    *pos = '\0';
  }
}

bool carro_existe(struct l_descr *lista,char *placa) {
  struct no *aux = lista->inicio;
  while(aux!=NULL) {
    if (strcmp(aux->carro->placa,placa) == 0) {
      return true;
    }
    aux = aux->proximo;
  }
  return false;
}

struct carro *buscar_carro(struct l_descr *lista,char *placa) {
  struct no *aux = lista->inicio;
  while(aux!=NULL) {
    if (strcmp(aux->carro->placa,placa) == 0) {
      return aux->carro;
    }
    aux = aux->proximo;
  }
  return NULL;
}

struct carro *excluir_carro(struct l_descr *lista) {
  setbuf(stdin, 0);
  char placa[10];
  printf("Digite a placa do carro a ser excluido:\n");
  fgets (placa, 10, stdin);
  retira_barra_n(placa);
  while (strlen(placa) == 0 || !carro_existe(lista,placa)) {
    setbuf(stdin, 0);
    printf("Digite a placa do carro a ser excluido:\n");
    fgets (placa, 10, stdin);
    retira_barra_n(placa);
  }

  struct carro *carro = buscar_carro(lista, placa);
  return carro;
}

struct carro *ler_carro(struct l_descr *lista) {
  setbuf(stdin, 0);
  char placa[10];
  printf("Digite a placa do carro:\n");
  fgets (placa, 10, stdin);
  retira_barra_n(placa);
  while (strlen(placa) == 0 || carro_existe(lista,placa)) {
    setbuf(stdin, 0);
    printf("Digite a placa do carro:\n");
    fgets (placa, 10, stdin);
    retira_barra_n(placa);
  }

  setbuf(stdin, 0);
  char marca[50];
  printf("Digite a marca do carro:\n");
  fgets (marca, 50, stdin);
  retira_barra_n(marca);
  while (strlen(marca) == 0) {
    setbuf(stdin, 0);
    printf("Digite a marca do carro:\n");
    fgets (marca, 50, stdin);
    retira_barra_n(marca);
  }

  setbuf(stdin, 0);
  int ano;
  printf("Digite o ano do carro: \n");
  scanf("%d",&ano);
  while (ano<=0) {
    setbuf(stdin, 0);
    printf("Digite o ano do carro: \n");
    scanf("%d",&ano);
  }

  struct carro *carro = malloc(sizeof(struct carro));
  strcpy(carro->placa, placa);
  strcpy(carro->marca, marca);
  carro->ano = ano;
  return carro;
}

int main() {
  struct l_descr lista;
  struct arvore *arvore_placa=NULL;
  struct arvore *arvore_marca=NULL;
  struct arvore *arvore_ano=NULL;

  inicializa_lista(&lista);

  int opcao;
  opcao = ler_opcao_menu();
  while(opcao>0) {
    if (opcao == 1) {
      // incluir carros
      struct carro *carro = ler_carro(&lista);
      insere_ordenado(&lista, carro);
      arvore_placa = insere_ordenado_arvore_placa(carro, arvore_placa);
      arvore_marca = insere_ordenado_arvore_marca(carro, arvore_marca);
      arvore_ano = insere_ordenado_arvore_ano(carro, arvore_ano);
      printf("Carro incluido com sucesso!\n");
    } else if (opcao == 2) {
      //excluir carros
      if (lista.inicio == NULL) {
        printf("Nao ha carros no sistema.\n");
      } else {
        struct carro *carro = excluir_carro(&lista);
        arvore_ano = remove_arvore_ano(arvore_ano,carro);
        arvore_marca = remove_arvore_marca(arvore_marca,carro);
        arvore_placa = remove_arvore_placa(arvore_placa,carro);
        remove_carro_lista(&lista,carro);
        free(carro);
        printf("Carro excluido com sucesso!\n");
      }
    } else if (opcao == 3) {
      //buscar carros pela arvore
      if (lista.inicio == NULL) {
        printf("Nao ha carros no sistema.\n");
      } else {
        setbuf(stdin, 0);
        char placa[10];
        printf("Digite a placa do carro a ser buscado:\n");
        fgets (placa, 10, stdin);
        retira_barra_n(placa);
        while (strlen(placa) == 0 || !carro_existe_arvore_placa(arvore_placa,placa) && strcmp(placa,"0") != 0) {
          setbuf(stdin, 0);
          printf("Carro nao existe.\nDigite 0 para sair\nDigite a placa do carro a ser buscado:\n");
          fgets (placa, 10, stdin);
          retira_barra_n(placa);
        }
        if (strcmp(placa,"0") != 0) {
          struct carro *carro = buscar_carro_arvore_placa(arvore_placa, placa);
          imprime_carro(carro);
        }
      }
    } else if (opcao == 4) {
      //listar carros pela placa percorrendo a lista
      imprime_lista(&lista);
    } else if (opcao == 5) {
      //listar carros pela marca atraves da arvore
      if (lista.inicio == NULL)
        printf("Nao ha carros no sistema.\n");
      else
        imprime(arvore_marca);
    } else if (opcao == 6) {
      //listar carros pelo ano atraves da arvore
      if (lista.inicio == NULL)
        printf("Nao ha carros no sistema.\n");
      else
        imprime(arvore_ano);
    }
    printf("\n");
    opcao = ler_opcao_menu();
  }
  liberar_memoria(&lista, arvore_ano, arvore_marca, arvore_placa);
  printf("FIM DO PROGRAMA\n");
}