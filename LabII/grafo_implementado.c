#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "stdbool.h"

#define N 5
#define TAM 100

typedef struct {
     int data[N]; 
     int tamanho;
     int inicio;
} Fila;   

void erro(char msg[]){
     printf("%s",msg);
}

Fila* criar(){
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->tamanho = 0;
    f->inicio = 0;
    return f;
}

bool cheia(Fila* f){ return f->tamanho == N;}
bool vazia(Fila* f){ return f->tamanho == 0;}

void print_elemento(Fila* f, int i) {
  printf("Elemento na pos %d , valor: %d\n", i, f->data[i]);
}

void print(Fila* f){
    printf("***********************************************\n");
    int fim = (f->inicio + f->tamanho) % N;
    printf("Fila=[inicio=%d, fim=%d]\n",f->inicio, fim);
    if (fim >= f->inicio)
      for (int i = f->inicio; i < fim; i++)
        print_elemento(f, i);
    else {
      for (int i = f->inicio; i < N; i++)
        print_elemento(f, i);
      for (int i = 0; i < fim; i++)
        print_elemento(f, i);
    }
    printf(" ");     
}

void enqueue(Fila* f, int elemento){
     //printf("Inserindo %d\n", elemento);
     if (cheia(f))
        erro("Fila Cheia\n");
     int fim = (f->inicio + f->tamanho) % N;
     f->data[fim] = elemento;
     f->tamanho++;
    // print(f);
}

int dequeue(Fila* f){ 
    if (vazia(f))
      erro("Erro: Tentando remover da fila vazia...\n");
    int temp = f->data[f->inicio];
    //printf("Removendo %d\n", temp);
    f->inicio = (f->inicio + 1) % N;
    f->tamanho--;
  //  print(f);
    return temp;    
}

int frente(Fila* f){ 
    if (vazia(f))
      erro("Erro: Tentando obter a frente da fila vazia...\n");
    return f->data[f->inicio];
}

typedef struct {
   bool m[TAM][TAM];
   int visitados[TAM];
   int tamanho;
} Grafo;

typedef struct {
   int itens[TAM];
   int tamanho;
} ListaAdj;

ListaAdj* criarListaAdj(){
   ListaAdj* l = (ListaAdj*) malloc(sizeof(ListaAdj));
   l->tamanho = 0;
   return l;
}

void inserirAdj(ListaAdj* l, int item){
  l->itens[l->tamanho] = item;
  l->tamanho++;
}

Grafo* criar_grafo(int tamanho){
   Grafo* g = (Grafo*) malloc(sizeof(Grafo));
   g->tamanho = tamanho;
   for(int i = 0; i < tamanho; i++)       
      for(int j = 0; j < tamanho; j++)       
          g->m[i][j] = false;
   return g;
}

void imprimir(Grafo* g){
   for(int i = 0; i < g->tamanho; i++){
      for(int j = 0; j < g->tamanho; j++)
         printf("%d ", g->m[i][j]);
      printf("\n");
   }
}

void inserirAresta(Grafo* g, int v1, int v2){
   if (g == NULL)
      printf("Grafo nao alocado");
   else 
      g->m[v1][v2] = true;
}

void removerAresta(Grafo* g, int v1, int v2){
   if (g == NULL)
      printf("Grafo nao alocado");
   else 
      g->m[v1][v2] = false;
}

bool existeAresta(Grafo* g, int v1, int v2){
   if (g == NULL)
      printf("Grafo nao alocado");
   else 
      return g->m[v1][v2];
}

ListaAdj* adjacentes(Grafo* g, int v){
   ListaAdj* l = criarListaAdj();
   for(int j = 0; j < g->tamanho; j++)
      if (g->m[v][j])
         inserirAdj(l, j);
  return l;
}

void imprimir_adjacentes(ListaAdj *adj) {
  for(int j = 0; j < adj->tamanho; j++)
    printf("%d\n", adj->itens[j]);
}

void visitarSubGrafoEmProfundidade(Grafo* g, int vertice){
   printf("CINZA: Visitando o vertice %d em pre-ordem\n", vertice);
   g->visitados[vertice] = true;
   ListaAdj * adj = adjacentes(g, vertice);
   // imprimir_adjacentes(adj);
   for (int i = 0; i < adj->tamanho; i++)
      if (!g->visitados[adj->itens[i]])
         visitarSubGrafoEmProfundidade(g, adj->itens[i]);
   printf("PRETO: Visitando o vertice %d em pos-ordem\n", vertice);
}

void visitarEmProfundidade(Grafo* g,int inicio){
   for (int i = 0; i < g->tamanho; i++)
       g->visitados[i] = false;
   for (int i = inicio; i < g->tamanho; i++)
       if (!g->visitados[i])
          visitarSubGrafoEmProfundidade(g, i);
}

void visitarSubGrafoEmLargura(Grafo* g, int vertice){
   g->visitados[vertice] = true;
   Fila* f = criar();
   enqueue(f, vertice);
   printf("Largura - CINZA: Visitando o vertice %d em pre-ordem\n", vertice);
   while (!vazia(f)){
      int u = dequeue(f); 
      ListaAdj * adj = adjacentes(g, u);
      for (int i = 0; i < adj->tamanho; i++)
         if (!g->visitados[adj->itens[i]]){
             g->visitados[adj->itens[i]] = true;
             printf("Largura - CINZA: Visitando o vertice %d em pre-ordem\n", adj->itens[i]);
             enqueue(f, adj->itens[i]);                             
         }
      printf("Largura - PRETO: Visitando o vertice %d em pos-ordem\n", u);
   }
}

void visitarEmLargura(Grafo* g,int inicio){
   for (int i = 0; i < g->tamanho; i++)
       g->visitados[i] = false;
   for (int i = inicio; i < g->tamanho; i++)
       if (!g->visitados[i])
          visitarSubGrafoEmLargura(g, i);
}

int main()
{
  Grafo* g = criar_grafo(5);
  imprimir(g);
  printf("\n");
  inserirAresta(g, 0, 1);
  inserirAresta(g, 1, 2);
  inserirAresta(g, 2, 3);
  inserirAresta(g, 3, 4);
  imprimir(g);
  visitarEmLargura(g,0);
  return 0;
}
