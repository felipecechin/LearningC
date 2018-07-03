#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int **aloca_matriz(int lin, int col){
  int i;
  int **m = malloc(lin*sizeof(int *));
  for(i=0;i<lin;i++) 
    m[i]=malloc(col*sizeof(int));
  return m;
}


void mostra_matriz(int **m, int lin, int col){
  int i,j;
  for (i=0;i<lin;i++){
    for(j=0;j<col;j++){
      printf("%i\t",m[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int conta_nao_nulos(int **matriz, int lin, int col){
  int cnt=0, i,j;
  for (i=0;i<lin;i++)
    for(j=0;j<col;j++)
      if (matriz[i][j] != 0)
        cnt++;
  return cnt;
}

void zerar_matriz(int **matriz,int lin,int col) {
  for (int i=0;i<lin;i++)
    for(int j=0;j<col;j++)
      matriz[i][j] = 0;
}

// Recebe uma matriz “normal” e suas dimensões e retorna uma matriz 
// esparsa estaticamente declarada, usando a representação triplet:
int **conv_matriz_n2sp(int **matriz, int lin, int col) {
  int conta_nao_n = conta_nao_nulos(matriz,lin,col);
  int **triplet = aloca_matriz(3,conta_nao_n+1);
  triplet[0][0] = lin;
  triplet[1][0] = col;
  triplet[2][0] = conta_nao_n;

  int coluna_triplet = 1;
  for (int i=0;i<lin;i++) {
    for (int j=0;j<col;j++) {
      if (matriz[i][j]!=0) {
        triplet[0][coluna_triplet] = i;
        triplet[1][coluna_triplet] = j;
        triplet[2][coluna_triplet] = matriz[i][j];
        coluna_triplet++;
      }
    }
  }

  return triplet;
}

// Recebe uma matriz esparsa usando a representação triplet e retorna uma 
// matriz “normal”. O parâmetro num representa o número de elementos não 
// nulos da matriz_esparsa:

int **conv_matriz_sp2n(int **matriz_esparsa, int num, int lin, int col) {
  int **matriz_normal = aloca_matriz(lin,col);
  zerar_matriz(matriz_normal,lin,col);
  for (int i=1;i<=num;i++) {
    matriz_normal[matriz_esparsa[0][i]][matriz_esparsa[1][i]] = matriz_esparsa[2][i];
  }

  return matriz_normal;
}

int main() {
  int **matriz = aloca_matriz(2,3);
  zerar_matriz(matriz,2,3);
  matriz[0][1] = 2;
  matriz[1][1] = 2;


  int **triplet;
  triplet = conv_matriz_n2sp(matriz,2,3);
  mostra_matriz(triplet,3,(triplet[2][0]+1));


  int **matriz_convertida;
  matriz_convertida = conv_matriz_sp2n(triplet,(triplet[2][0]),(triplet[0][0]),(triplet[1][0]));
  printf("\n");
  mostra_matriz(matriz_convertida,triplet[0][0],(triplet[1][0]));
  return 0;
}