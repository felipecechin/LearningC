#include <stdio.h>
#include <stdlib.h>

struct grafo {
   int **mat;
   int num_arestas;
   int num_vertices;
};

int **aloca_matriz(int lin, int col) {
  int **matriz;
  matriz = malloc(lin*sizeof(int *));
  for (int i=0;i<lin;i++) {
    matriz[i] = malloc(col*sizeof(int));
  }
  return matriz; 
}

struct grafo* cria_grafo(int tamanho){
   struct grafo* g = malloc(sizeof(struct grafo));
   g->num_vertices = 0;
   g->num_arestas = 0;
   g->mat = aloca_matriz(tamanho,tamanho);
   return g;
}

void insere_vertice(struct grafo *g) {
  g->num_vertices++;
}

void insere_aresta(struct grafo *g, int v1, int v2) {
  if (g==NULL)
    return;
  if (v1>=g->num_vertices || v2>=g->num_vertices)
    return;
  if (g->mat[v1][v2] == 0) {
    g->mat[v1][v2] = 1;
    g->num_arestas++;
  }
}

void remove_aresta(struct grafo *g, int v1, int v2) {
  if (g==NULL)
    return;
  if (v1>=g->num_vertices || v2>=g->num_vertices)
    return;
  if (g->mat[v1][v2] == 1) {
    g->mat[v1][v2] = 0;
    g->num_arestas--;
  }
}

void mostra_grafo(struct grafo *g) {
  printf("Lista de vertices\n");
  for (int i=0;i<g->num_vertices;i++) {
    printf("%i ",i);
  }
  printf("\n");
  printf("Lista de arestas\n");
  for (int i=0;i<g->num_vertices;i++) {
    for (int j=0;j<g->num_vertices;j++) {
      if (g->mat[i][j] == 1) {
        printf("%i-%i\n",i,j);
      }
    }
  }
}

int main() {
  // struct grafo *gr;
  // gr = cria_grafo(20);
  // insere_vertice(gr);
  // insere_vertice(gr);
  // insere_aresta(gr,0,1);
  // mostra_grafo(gr);
  int num = 65;
  char letra = num;
  printf("%c\n", letra);
}