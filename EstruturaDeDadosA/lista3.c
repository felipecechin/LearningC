#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int *aloca_vetor(int col) {
  int *vetor;
  vetor = malloc(col*sizeof(int));
  return vetor; 
}

void le_vetor(int *vet, int col) {
  for (int i = 0; i < col; i++) {
    printf("Digite um valor para vet[%d]: ",i);
    scanf("%d",&vet[i]);
  }
}

void imprime_vetor(int *vet, int col) {
  for (int i = 0; i < col; i++) {
    printf("vet[%d]: %d\n",i,vet[i]);
  }
}

int **aloca_matriz(int lin, int col) {
  int **matriz;
  matriz = malloc(lin*sizeof(int *));
  for (int i=0;i<lin;i++) {
    matriz[i] = malloc(col*sizeof(int));
  }
  return matriz; 
}

void le_matriz(int **mat, int lin, int col) {
  for (int i=0;i<lin;i++) {
    for (int j=0;j<col;j++) {
      printf("Digite um valor para mat[%d][%d]: ",i,j);
      scanf("%d",&mat[i][j]);
    }
  }
}

void imprime_matriz(int **mat, int lin, int col) {
  for (int i=0;i<lin;i++) {
    for (int j=0;j<col;j++) {
      printf("Mat[%d][%d]: %d\n",i,j,mat[i][j]);
    }
  }
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

void le_cubo(int ***cubo, int prof, int lin, int col) {
  for(int i=0;i<prof;i++){
    for(int j=0;j<lin;j++){
      for(int k=0;k<col;k++){
        printf("Informe o valor de cubo[%i][%i][%i]: ", i,j,k);
        scanf("%d", &cubo[i][j][k]);
      }
    }
  }
}

void imprime_cubo(int ***cubo, int prof, int lin, int col) {
  for(int i=0;i<prof;i++){
    for(int j=0;j<lin;j++){
      for(int k=0;k<col;k++){
        printf("%d\t", cubo[i][j][k]);
      }
      printf("\n");
    }
    printf("\n");
  }
  printf("\n");
}

void *cria_estrutura(int prof, int lin, int col) {
  if (prof!=0 && lin!=0 && col!=0) {
    int ***cubo;
    cubo = aloca_cubo(prof,lin,col);
    return cubo;
  } else if (lin!=0 && col!=0) {
    int **matriz;
    matriz = aloca_matriz(lin,col);
    return matriz; 
  } else if (col!=0) {
    int *vetor;
    vetor = aloca_vetor(col);
    return vetor;
  } else {
    int *vazio;
    vazio = NULL;
    return vazio;
  }
}

void le_estrutura(void *estr, int prof, int lin, int col) {
  if (prof!=0 && lin!=0 && col!=0) {
    le_cubo(estr,prof,lin,col);
    return;
  } else if (lin!=0 && col!=0) {
    le_matriz(estr,lin,col);
    return; 
  } else if (col!=0) {
    le_vetor(estr,col);
  } else {
    return;
  }
}

void imprime_estrutura(void *estr, int prof, int lin, int col) {
  if (prof!=0 && lin!=0 && col!=0) {
    imprime_cubo(estr,prof,lin,col);
    return;
  } else if (lin!=0 && col!=0) {
    imprime_matriz(estr,lin,col);
    return; 
  } else if (col!=0) {
    imprime_vetor(estr,col);
  } else {
    return;
  }
}

int main() {
  int prof,lin, col;
  printf("Informe a profundidade:\n");
  scanf("%d",&prof);
  while(prof<0) {
    printf("Informe a profundidade:\n");
    scanf("%d",&prof);
  }
  printf("Informe o número de linhas:\n");
  scanf("%d",&lin);
  while(lin<0) {
    printf("Informe o número de linhas:\n");
    scanf("%d",&lin);
  }
  printf("Informe o número de colunas:\n");
  scanf("%d",&col);
  while(col<0) {
    printf("Informe o número de colunas:\n");
    scanf("%d",&col);
  }
  if (prof==1) {
    prof--;
  }
  // int *vetor;
  // vetor = aloca_vetor(3);
  // le_vetor(vetor,3);
  // imprime_vetor(vetor,3);


  // int **matriz;
  // matriz = aloca_matriz(2,2);
  // le_matriz(matriz,2,2);
  // imprime_matriz(matriz,2,2);

  // int ***cubo;
  // cubo = aloca_cubo(2,2,2);
  // le_cubo(cubo,2,2,2);
  // imprime_cubo(cubo,2,2,2);

  int ***estrutura = cria_estrutura(prof,lin,col);
  le_estrutura(estrutura,prof,lin,col);
  imprime_estrutura(estrutura,prof,lin,col);

  return 0;
}