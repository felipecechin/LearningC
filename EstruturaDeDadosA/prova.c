#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

////////////////QUESTAO 4/////////////

int **aloca_matriz(int lin, int col) {
  int i;
  int **m = malloc(lin*sizeof(int *));
  for(i=0;i<lin;i++) 
    m[i]=malloc(col*sizeof(int));
  return m;
}

int conta_nao_nulos(int ***cubo, int prof, int lin, int col) {
  int cnt=0, i,j,k;
  for (k=0;k<prof;k++)
    for (i=0;i<lin;i++)
      for(j=0;j<col;j++)
        if (cubo[k][i][j] != 0)
          cnt++;
  return cnt;
}

void zerar_cubo(int ***cubo, int prof, int lin, int col) {
  int i,j,k;
  for (k=0;k<prof;k++)
    for (i=0;i<lin;i++)
      for(j=0;j<col;j++)
        cubo[k][i][j] = 0;
}


int ***aloca_cubo(int prof, int lin, int col) {
  int ***cubo=malloc(prof*sizeof(int **));
  for(int i=0;i<prof;i++){
    cubo[i]=malloc(lin*sizeof(int *));
    for(int j=0;j<lin;j++){
        cubo[i][j]=malloc(col*sizeof(int));
    }
  }
  return cubo;
}

int **cubo_esparso(int ***cubo, int prof, int lin, int col) {
  int conta_nao_n = conta_nao_nulos(cubo,prof,lin,col);
  int **triplet = aloca_matriz(4,conta_nao_n+1);
  triplet[0][0] = prof;
  triplet[1][0] = lin;
  triplet[2][0] = col;
  triplet[3][0] = conta_nao_n;

  int coluna_triplet = 1;
  for (int k=0;k<prof;k++) {
    for (int i=0;i<lin;i++) {
      for (int j=0;j<col;j++) {
        if (cubo[k][i][j] != 0) {
          triplet[0][coluna_triplet] = k;
          triplet[1][coluna_triplet] = i;
          triplet[2][coluna_triplet] = j;
          triplet[3][coluna_triplet] = cubo[k][i][j];
          coluna_triplet++;
        }
      }
    }
  }

  return triplet;
}

void imprime_matriz(int **mat, int lin, int col) {
  for (int i=0;i<col;i++) {
    for (int j=0;j<lin;j++) {
      printf("Mat[%d][%d]: %d\n",j,i,mat[j][i]);
    }
  }
}


int main() {
  //QUESTAO 4//
  int ***cubo = aloca_cubo(2,2,2);
  zerar_cubo(cubo,2,2,2);
  cubo[0][1][1] = 1;
  cubo[1][0][0] = 2;
  int **triplet = cubo_esparso(cubo,2,2,2);
  imprime_matriz(triplet,4,3);
  return 0;
}