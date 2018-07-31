#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  int *data; 
  int tamanho;
  int inicio;
  int tamanho_maximo;
} Fila; 


Fila* criar(int tamanho){
  Fila* f = (Fila*) malloc(sizeof(Fila));
  int *data = malloc(tamanho*sizeof(int));
  f->data = data;
  f->tamanho_maximo = tamanho;
  f->tamanho = 0;
  f->inicio = 0;
  return f;
}

bool cheia(Fila* f){ return f->tamanho == f->tamanho_maximo;}
bool vazia(Fila* f){ return f->tamanho == 0;}

void enqueue(Fila* f, int elemento){
  //printf("Inserindo %d\n", elemento);
  if (cheia(f)) {
    printf("Fila Cheia\n");
    exit(0);
  }
  int fim = (f->inicio + f->tamanho) % f->tamanho_maximo;
  f->data[fim] = elemento;
  f->tamanho++;
}

int dequeue(Fila* f){
  if (vazia(f)) {
    printf("Erro: Tentando remover da fila vazia...\n");
    exit(0);
  }
  int temp = f->data[f->inicio];
  //printf("Removendo %d\n", temp);
  f->inicio = (f->inicio + 1) % f->tamanho_maximo;
  f->tamanho--;
  return temp;
}

int frente(Fila* f){ 
  if (vazia(f)) {
    printf("Erro: Tentando obter a frente da fila vazia...\n");
    exit(0);
  }
  return f->data[f->inicio];
}

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

struct grafo {
  struct l_descr *arestas;
  int *visitados;
  int tamanho;
};

struct grafo *cria_grafo(int tamanho) {
  struct l_descr *vetor;
  vetor = malloc(tamanho*sizeof(struct l_descr));
  for (int i=0;i<tamanho;i++) {
    inicializa_lista(&vetor[i]);
  }
  struct grafo *grafo = malloc(sizeof(struct grafo));
  grafo->arestas = vetor;
  int *vetor_visitados = malloc(tamanho*sizeof(int));
  grafo->visitados = vetor_visitados;
  grafo->tamanho = tamanho;
  return grafo; 
}

void imprime_grafo(struct grafo *gr) {
  for (int i=0;i<gr->tamanho;i++) {
    printf("--------VETOR[%i]\n",i);
    imprime_lista(&(gr->arestas[i]));
  }
}

void inserir_aresta(struct grafo *gr, int v1, int v2) {
  if (gr == NULL)
    printf("Grafo não alocado");
  else if (v1<gr->tamanho && v2<gr->tamanho)
    insere_ordenado(&(gr->arestas[v1]),v2);
}

void visitarSubGrafoEmProfundidade(struct grafo* g, int vertice){
  printf("Profundidade - CINZA: Visitando o vertice %d em pre-ordem\n", vertice+1);
  g->visitados[vertice] = true;
  struct no *aux = g->arestas[vertice].inicio;
  while(aux!=NULL) {
    if (!g->visitados[aux->valor])
      visitarSubGrafoEmProfundidade(g, aux->valor);
    aux = aux->proximo;
  }
  printf("Profundidade - PRETO: Visitando o vertice %d em pos-ordem\n", vertice+1);
}

void visitarEmProfundidade(struct grafo *g, int inicio) {
  for (int i = 0; i < g->tamanho; i++)
    g->visitados[i] = false;
  for (int i = inicio; i < g->tamanho; i++)
    if (!g->visitados[i])
      visitarSubGrafoEmProfundidade(g, i);
}

void visitarSubGrafoEmLargura(struct grafo *g, int vertice){
  g->visitados[vertice] = true;
  Fila* f = criar(g->tamanho);
  enqueue(f, vertice);
  printf("Largura - CINZA: Visitando o vertice %d em pre-ordem\n", vertice+1);
  while (!vazia(f)){
    int u = dequeue(f); 
    struct no *aux = g->arestas[u].inicio;
    while(aux!=NULL) {
      if (!g->visitados[aux->valor]){
        g->visitados[aux->valor] = true;
        printf("Largura - CINZA: Visitando o vertice %d em pre-ordem\n", aux->valor+1);
        enqueue(f, aux->valor);
      }
      aux = aux->proximo;
    }
    printf("Largura - PRETO: Visitando o vertice %d em pos-ordem\n", u+1);
  }
  free(f->data);
  free(f);
}

void visitarEmLargura(struct grafo *g, int inicio) {
  for (int i = 0; i < g->tamanho; i++)
    g->visitados[i] = false;
  for (int i = inicio; i < g->tamanho; i++)
    if (!g->visitados[i])
      visitarSubGrafoEmLargura(g, i);
}

int ler_tamanho() {
  int tamanho;
  printf("Digite o numero de vertices do grafo a ser construido: ");
  scanf("%d",&tamanho);
  while(tamanho<=0) {
    printf("Digite o numero de vertices do grafo a ser construido: ");
    scanf("%d",&tamanho);
  }
  return tamanho;
}

int ler_vertice(int vertice, int tamanho, struct grafo *gr) {
  int adj;
  printf("Digite um dos vertices adjacentes ao vertice %d.\n",vertice);
  printf("Digite 0 para pular ao proximo vertice.\n");
  printf("Vertice:\n");
  scanf("%d",&adj);
  while(adj<0 || adj>tamanho) {
    printf("Digite um dos vertices adjacentes ao vertice %d.\n",vertice);
    printf("Digite 0 para pular ao proximo vertice.\n");
    printf("Vertice:\n");
    scanf("%d",&adj);
  }
  if (adj!=0) {
    int busca_ind = busca_indice(&(gr->arestas[vertice-1]),adj-1);
    if (busca_ind!=-1) {
      printf("Vertice adjacente ja adicionado\n");
      return ler_vertice(vertice,tamanho,gr);
    }
  }
  return adj;
}

int ler_vertice_busca(int tamanho) {
  int vertice;
  printf("Digite o numero de um no para iniciar a busca: ");
  scanf("%d",&vertice);
  while(vertice<=0 || vertice>tamanho) {
    printf("Digite o numero de um no para iniciar a busca: ");
    scanf("%d",&vertice);
  }
  return vertice-1;
}

int ler_opcao_busca() {
  int busca;
  printf("Digite o tipo da busca.\n");
  printf("(1 - por profundidade)\n");
  printf("(2 - por largura)\n");
  scanf("%d",&busca);
  while(busca!=1 && busca!=2) {
    printf("Digite o tipo da busca.\n");
    printf("(1 - por profundidade)\n");
    printf("(2 - por largura)\n");
    scanf("%d",&busca);
  }
  return busca;
}

void liberar_memoria_lista(struct l_descr *l) {
  int cont = l->cnt;
  for (int i=0;i<cont;i++) {
    remove_primeiro(l);
  }
}

void liberar_memoria(struct grafo *gr) {
  for (int i=0;i<gr->tamanho;i++) {
    liberar_memoria_lista(&(gr->arestas[i]));
  }
  free(gr->arestas);
  free(gr->visitados);
  free(gr);
}

int main() {
  struct grafo *gr;
  int tamanho = ler_tamanho();
  gr = cria_grafo(tamanho);
  printf("O GRAFO EH DO TIPO DIRECIONADO.\n");
  for(int i=1;i<=tamanho;i++) {
    int vertice = ler_vertice(i,tamanho,gr);
    while(vertice>0) {
      printf("Vertice adjacente adicionado.\n");
      inserir_aresta(gr, (i-1), (vertice-1));
      vertice = ler_vertice(i,tamanho,gr);
    }
  }

  int vertice_busca = ler_vertice_busca(tamanho);
  int opcao_busca = ler_opcao_busca();
  if (opcao_busca == 1) {
    visitarEmProfundidade(gr,vertice_busca);
  } else {
    visitarEmLargura(gr,vertice_busca);
  }
  liberar_memoria(gr);
  return 0;
}