#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h> 

//TIPOS DE NAVIOS
// porta-aviões (cinco quadrados), navios-tanque (quatro quadrados)
// contratorpedeiros (três quadrados) e submarinos (dois quadrados)

int **matriz_jogador_copia;

int** inicializar_tabuleiro(int l,int c) {
  int **m = (int**)malloc(l * sizeof(int*));
 
  for (int i = 0; i < l; i++) {
    m[i] = (int*) malloc(c * sizeof(int));
    for (int j = 0; j < c; j++){
      m[i][j] = 0;
    }
  }
  return m;
}

char imprimir_letra_linha(int num) {
  printf("%c ",(65+num));
}

int imprimir_tabuleiro(int **matriz,int l,int c) {
  printf("  ");
  for (int j = 0; j < c; j++){
    if (j>=9) {
      printf("%d ",j+1);
    } else {
      printf(" %d ",j+1);
    }
  }
  printf("\n");

  for (int i = 0; i < l; i++){
    imprimir_letra_linha(i);
    for (int j = 0; j < c; j++){
      if (matriz[i][j] == 0) {
        printf("[~]");
      } else if (matriz[i][j] == 1) {
        printf("[X]");
      } else if (matriz[i][j] >= 2) {
        printf("[#]");
      }
    }
    printf("\n");
  }
}

int imprimir_tabuleiro_jogadas(int **matriz,int l,int c) {
  printf("  ");
  for (int j = 0; j < c; j++){
    if (j>=9) {
      printf("%d ",j+1);
    } else {
      printf(" %d ",j+1);
    }
  }
  printf("\n");

  for (int i = 0; i < l; i++){
    imprimir_letra_linha(i);
    for (int j = 0; j < c; j++){
      if (matriz[i][j] == 1) {
        printf("[X]");
      } else if (matriz[i][j] == 2) {
        printf("[-]");
      } else {
        printf("[?]");
      }
    }
    printf("\n");
  }
}


int limite_porta_avioes(int l,int c) {
  int porcentagem = 5;
  int quadrados = 5;
  return (l*c*porcentagem)/(100*quadrados);
}

int limite_navios_tanque(int l,int c) {
  int porcentagem = 8;
  int quadrados = 4;
  return (l*c*porcentagem)/(100*quadrados);
}

int limite_contra_torpedeiros(int l,int c) {
  int porcentagem = 9;
  int quadrados = 3;
  return (l*c*porcentagem)/(100*quadrados);
}

int limite_submarinos(int l,int c) {
  int porcentagem = 8;
  int quadrados = 2;
  return (l*c*porcentagem)/(100*quadrados);
}

void atribuir_quantidade(int *qtd_pa,int *qtd_nt, int *qtd_ct, int *qtd_sb,int linhas, int colunas) {
  int limite_pa = limite_porta_avioes(linhas,colunas);
  if (limite_pa <= 0) {
    printf("Devido ao pequeno tamanho do tabuleiro escolhido, porta-avioes nao serao utilizados.");
    *qtd_pa = 0;
  } else if (limite_pa == 1){ 
    printf("Devido ao tamanho do tabuleiro escolhido, sera utilizado somente 1 porta-avioes.");
    *qtd_pa = 1;
  } else {
    printf("Informe a quantidade de porta-avioes: (No maximo %d) ",limite_pa);
    scanf("%d",qtd_pa);
    while (*qtd_pa > limite_pa || *qtd_pa <= 0) {
      printf("Informe a quantidade de porta-avioes: (No maximo %d) ",limite_pa);
      scanf("%d",qtd_pa);
    }
  }

  int limite_nt = limite_navios_tanque(linhas,colunas);
  if (limite_nt <= 0) {
    printf("\nDevido ao pequeno tamanho do tabuleiro escolhido, navios-tanque nao serao utilizados.");
    *qtd_nt = 0;
  } else if (limite_nt == 1){ 
    printf("\nDevido ao tamanho do tabuleiro escolhido, sera utilizado somente 1 navio-tanque.");
    *qtd_nt = 1;
  } else {
    printf("\nInforme a quantidade de navios-tanque: (No maximo %d) ",limite_nt);
    scanf("%d",qtd_nt);
    while (*qtd_nt > limite_nt || *qtd_nt <= 0) {
      printf("Informe a quantidade de navios-tanque: (No maximo %d) ",limite_nt);
      scanf("%d",qtd_nt);
    }
  }

  int limite_ct = limite_contra_torpedeiros(linhas,colunas);
  if (limite_ct <= 0) {
    printf("\nDevido ao pequeno tamanho do tabuleiro escolhido, contratorpedeiros nao serao utilizados.");
    *qtd_ct = 0;
  } else if (limite_ct == 1){ 
    printf("\nDevido ao tamanho do tabuleiro escolhido, sera utilizado somente 1 contratorpedeiro.");
    *qtd_ct = 1;
  } else {
    printf("\nInforme a quantidade de contratorpedeiros: (No maximo %d) ",limite_ct);
    scanf("%d",qtd_ct);
    while (*qtd_ct > limite_ct || *qtd_ct <= 0) {
      printf("Informe a quantidade de contratorpedeiros: (No maximo %d) ",limite_ct);
      scanf("%d",qtd_ct);
    }
  }

  int limite_sb = limite_submarinos(linhas,colunas);
  if (limite_sb <= 0) {
    printf("\nDevido ao pequeno tamanho do tabuleiro escolhido, submarinos nao serao utilizados.");
    *qtd_sb = 0;
  } else if (limite_sb == 1){ 
    printf("\nDevido ao tamanho do tabuleiro escolhido, sera utilizado somente 1 submarino.");
    *qtd_sb = 1;
  } else {
    printf("\nInforme a quantidade de submarinos: (No maximo %d) ",limite_sb);
    scanf("%d",qtd_sb);
    while (*qtd_sb > limite_sb || *qtd_sb <= 0) {
      printf("Informe a quantidade de submarinos: (No maximo %d) ",limite_sb);
      scanf("%d",qtd_sb);
    }
  }
}

void digitar_linha_coluna_sozinho(int *linhas,int *colunas) {
  printf("\nInforme o numero de linhas para o seu tabuleiro:");
  scanf("%d",linhas);
  while(*linhas<=0 || *linhas>26) {
    if (*linhas>26) {
      printf("\nLinhas deve ser menor ou igual a 26.");
    }
    printf("\nInforme o numero de linhas para o seu tabuleiro:");
    scanf("%d",linhas);
  }
  printf("\nInforme o numero de colunas para o seu tabuleiro:");
  scanf("%d",colunas);
  while(*colunas<=0) {
    printf("\nInforme o numero de colunas para o seu tabuleiro:");
    scanf("%d",colunas);
  }
}

void digitar_linha_coluna(int *linhas,int *colunas) {
  printf("\nInforme o numero de linhas para o seu tabuleiro e o do computador:");
  scanf("%d",linhas);
  while(*linhas<=0 || *linhas>26) {
    if (*linhas>26) {
      printf("\nLinhas deve ser menor ou igual a 26.");
    }
    printf("\nInforme o numero de linhas para o seu tabuleiro e o do computador:");
    scanf("%d",linhas);
  }
  printf("\nInforme o numero de colunas para o seu tabuleiro e o do computador:");
  scanf("%d",colunas);
  while(*colunas<=0) {
    printf("\nInforme o numero de colunas para o seu tabuleiro e o do computador:");
    scanf("%d",colunas);
  }
}

bool preencher_linha_peca(int quadrados, int **matriz, int linha, int coluna, int total_linhas,int total_colunas,int indice_navio) {
  if (coluna+quadrados-1<total_colunas) {
    for (int i=0;i<quadrados;i++) {
      if (matriz[linha][coluna+i] >= 2) {
        return false;
      }
    }
    if (coluna+quadrados<total_colunas) {
      if (matriz[linha][coluna+quadrados] >=2) {
        return false;
      }
    }
    if (coluna-1>=0) {
      if (matriz[linha][coluna-1] >=2) {
        return false;
      }
    }
    for (int i=0;i<quadrados;i++) {
      if (linha-1>=0) {
        if (matriz[linha-1][coluna+i] >= 2) {
          return false;
        }
      }
      if (linha+1<=total_linhas-1) {
        if (matriz[linha+1][coluna+i] >= 2) {
          return false;
        }
      } 
    }
    for (int i=0;i<quadrados;i++) {
      matriz[linha][coluna+i] = indice_navio;
    }
    return true;
  }
  return false;
}

bool preencher_coluna_peca(int quadrados, int **matriz, int linha, int coluna, int total_linhas,int total_colunas,int indice_navio) {
  if (linha+quadrados-1<total_linhas) {
    for (int i=0;i<quadrados;i++) {
      if (matriz[linha+i][coluna] >= 2) {
        return false;
      }
    }
    if (linha+quadrados<total_linhas) {
      if (matriz[linha+quadrados][coluna] >=2) {
        return false;
      }
    }
    if (linha-1>=0) {
      if (matriz[linha-1][coluna] >=2) {
        return false;
      }
    }
    for (int i=0;i<quadrados;i++) {
      if (coluna-1>=0) {
        if (matriz[linha+i][coluna-1] >= 2) {
          return false;
        }
      }
      if (coluna+1<=total_colunas-1) {
        if (matriz[linha+i][coluna+1] >= 2) {
          return false;
        }
      } 
    }
    for (int i=0;i<quadrados;i++) {
      matriz[linha+i][coluna] = indice_navio;
    }
    return true;
  }
  return false;
}

//ao colocar os navios no tabuleiro, a funcao nao permite colocar navios um ao lado do outro (sem colisao)
void colocar_peca_tabuleiro(int qtd_pecas,int quadrados,int **matriz,int linhas, int colunas,int indice_navio) {
  for (int i=0;i<qtd_pecas;i++) {
    bool colocou = false;
    while(!colocou) {
      int linha_aleatoria = rand()%linhas;
      int coluna_aleatoria = rand()%colunas;
      int direcao = rand()%2;
      if (direcao == 0) {
        if (preencher_linha_peca(quadrados,matriz,linha_aleatoria,coluna_aleatoria,linhas,colunas,indice_navio)) {
          colocou = true;
        }
      } else {
        if (preencher_coluna_peca(quadrados,matriz,linha_aleatoria,coluna_aleatoria,linhas,colunas,indice_navio)) {
          colocou = true;
        }
      }
    }
    indice_navio++;
  }
}


//codigo usado para a matriz do jogador
//0 para agua
//1 atingiu navio
//maior ou igual a 2 eh navio

//codigo usado para a matriz das jogadas
//1 atingiu navio
//2 atingiu agua
//0 nao atirou
bool verificar_jogada(int **matriz_atacada,int **matriz_jogadas,int linha, int coluna,int *indice_navio) {
  if(matriz_atacada[linha][coluna] >= 2) {
    //atingiu area de navio
    *indice_navio = matriz_atacada[linha][coluna];
    matriz_atacada[linha][coluna] = 1;
    matriz_jogadas[linha][coluna] = 1;
    return true;
  } else if (matriz_atacada[linha][coluna] == 0) {
    //atingiu agua
    matriz_jogadas[linha][coluna] = 2;
    return false;
  }
  return false;
}

bool atirou_na_posicao(int **matriz, int linha, int coluna) {
  if (matriz[linha][coluna] > 0) {
    return true;
  } else {
    return false;
  }
  return false;
}


bool acertou(int **matriz, int linha, int coluna) {
  if (matriz[linha][coluna] == 1) {
    return true;
  } else {
    return false;
  }
  return false;
}

bool nao_atirou_na_posicao_em_volta(int **matriz, int i, int j) {
  if (!atirou_na_posicao(matriz,i+1,j) && !atirou_na_posicao(matriz,i-1,j)
   && !atirou_na_posicao(matriz,i,j+1) && !atirou_na_posicao(matriz,i,j-1)) {
    return true;
  } else {
    return false;
  }
  return false;
}

bool verificar_indice_matriz_linha_acima(int **matriz,int inicio,int linha,int coluna) {
  if (linha>inicio) {
    if (matriz[linha][coluna] == 1) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool verificar_indice_matriz_linha_abaixo(int **matriz,int fim,int linha,int coluna) {
  if (linha<fim) {
    if (matriz[linha][coluna] == 1) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

int encontrar_primeira_area_nao_atingida_linha_acima(int **matriz_jogadas,int inicio,int i,int coluna) {
  int valor_inicial = i;
  while (verificar_indice_matriz_linha_acima(matriz_jogadas,inicio,i,coluna)) {
    i--;
    if (matriz_jogador_copia[i][coluna] == -1) {
      return valor_inicial;
    }
  }
  return i;
}

int encontrar_primeira_area_nao_atingida_linha_abaixo(int **matriz_jogadas,int i,int fim,int coluna) {
  int valor_inicial = i;
  while (verificar_indice_matriz_linha_abaixo(matriz_jogadas,fim,i,coluna)) {
    i++;
    if (matriz_jogador_copia[i][coluna] == -1) {
      return valor_inicial;
    }
  }
  return i;
}

bool verificar_indice_matriz_coluna_esquerda(int **matriz,int inicio,int linha,int coluna) {
  if (coluna>inicio) {
    if (matriz[linha][coluna] == 1) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool verificar_indice_matriz_coluna_direita(int **matriz,int fim,int linha,int coluna) {
  if (coluna<fim) {
    if (matriz[linha][coluna] == 1) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

int encontrar_primeira_area_nao_atingida_coluna_esquerda(int **matriz_jogadas,int inicio,int i,int linha) {
  int valor_inicial = i;
  while (verificar_indice_matriz_coluna_esquerda(matriz_jogadas,inicio,linha,i)) {
    i--;
    if (matriz_jogador_copia[linha][i] == -1) {
      return valor_inicial;
    }
  }
  return i;
}


int encontrar_primeira_area_nao_atingida_coluna_direita(int **matriz_jogadas,int i,int fim,int linha) {
  int valor_inicial = i;
  while (verificar_indice_matriz_coluna_direita(matriz_jogadas,fim,linha,i)) {
    i++;
    if (matriz_jogador_copia[linha][i] == -1) {
      return valor_inicial;
    }
  }
  return i;
}

bool tiver_extremidade_esquerda(int coluna) {
  if (coluna-1>=0) {
    return true;
  }
  return false;
}

bool tiver_extremidade_direita(int coluna,int total_colunas) {
  if (coluna+1<=total_colunas-1) {
    return true;
  }
  return false;
}

bool tiver_extremidade_acima(int linha) {
  if (linha-1>=0) {
    return true;
  }
  return false;
}

bool tiver_extremidade_abaixo(int linha,int total_linhas) {
  if (linha+1<=total_linhas-1) {
    return true;
  }
  return false;
}

void verificar_acerto_jogada(int **matriz_jogadas,int linha, int coluna,int *linha_chutada,int *coluna_chutada,int *linha_ou_coluna, int valor) {
  if (acertou(matriz_jogadas,linha,coluna) && matriz_jogador_copia[linha][coluna] == -1) {
    *linha_ou_coluna = valor;
  } else if (!atirou_na_posicao(matriz_jogadas,linha,coluna)) {
    *linha_chutada = linha;
    *coluna_chutada = coluna;
  } else {
    *linha_ou_coluna = (rand()%2)+1;
  }
}

void chutar_posicao(int **matriz,int **matriz_jogadas,int *linha_chutada, int *coluna_chutada,int i,int j,int total_linhas,int total_colunas,int *linha_ou_coluna,int *direcao) {
  if (tiver_extremidade_abaixo(i,total_linhas) && tiver_extremidade_acima(i) && tiver_extremidade_esquerda(j) && tiver_extremidade_direita(j,total_colunas)) {
    if (*linha_ou_coluna == 0) {
      if (nao_atirou_na_posicao_em_volta(matriz_jogadas,i,j)) {
        int opcao_linha_coluna = rand()%2;
        if (opcao_linha_coluna == 0) {
          int opcao_linha = rand()%2;
          if (opcao_linha == 0) {
            *linha_chutada = i+1;
            *coluna_chutada = j;
          } else {
            *linha_chutada = i-1;
            *coluna_chutada = j;
          }
        } else {
          int opcao_coluna = rand()%2;
          if (opcao_coluna == 0) {
            *linha_chutada = i;
            *coluna_chutada = j+1;
          } else {
            *linha_chutada = i;
            *coluna_chutada = j-1;
          }
        }
      } else if (atirou_na_posicao(matriz_jogadas,i+1,j) && !acertou(matriz_jogadas,i+1,j) && atirou_na_posicao(matriz_jogadas,i-1,j) && !acertou(matriz_jogadas,i-1,j)) {
        *linha_ou_coluna = 2;
      } else if (atirou_na_posicao(matriz_jogadas,i,j+1) && !acertou(matriz_jogadas,i,j+1) && atirou_na_posicao(matriz_jogadas,i,j-1) && !acertou(matriz_jogadas,i,j-1)) {
        *linha_ou_coluna = 1;
      } else if (atirou_na_posicao(matriz_jogadas,i+1,j) && !acertou(matriz_jogadas,i+1,j)) {
        verificar_acerto_jogada(matriz_jogadas,i-1,j,linha_chutada,coluna_chutada,linha_ou_coluna,2);
      } else if (atirou_na_posicao(matriz_jogadas,i-1,j) && !acertou(matriz_jogadas,i-1,j)) {
        verificar_acerto_jogada(matriz_jogadas,i+1,j,linha_chutada,coluna_chutada,linha_ou_coluna,2);
      } else if (atirou_na_posicao(matriz_jogadas,i,j+1) && !acertou(matriz_jogadas,i,j+1)) {
        verificar_acerto_jogada(matriz_jogadas,i,j-1,linha_chutada,coluna_chutada,linha_ou_coluna,1);
      } else if (atirou_na_posicao(matriz_jogadas,i,j-1) && !acertou(matriz_jogadas,i,j-1)) {
        verificar_acerto_jogada(matriz_jogadas,i,j+1,linha_chutada,coluna_chutada,linha_ou_coluna,1);
      } else {
        *linha_ou_coluna = (rand()%2)+1;
      }
    } 
    if (*linha_ou_coluna == 1){
      *coluna_chutada = j;
      int acima = encontrar_primeira_area_nao_atingida_linha_acima(matriz_jogadas,0,i,j);
      int abaixo = encontrar_primeira_area_nao_atingida_linha_abaixo(matriz_jogadas,i,(total_linhas-1),j);
      if (!atirou_na_posicao(matriz_jogadas,acima,j) && !atirou_na_posicao(matriz_jogadas,abaixo,j)) {
        int opcao_linha = rand()%2;
        if (opcao_linha==0) {
          *linha_chutada = acima;
        } else {
          *linha_chutada = abaixo;
        }
      } else if (atirou_na_posicao(matriz_jogadas,acima,j) && atirou_na_posicao(matriz_jogadas,abaixo,j)) {
        *linha_ou_coluna = 2;
        chutar_posicao(matriz,matriz_jogadas,linha_chutada,coluna_chutada,i,j,total_linhas,total_colunas,linha_ou_coluna,direcao);
      } else if (atirou_na_posicao(matriz_jogadas,acima,j)) {
        *linha_chutada = abaixo;
      } else if (atirou_na_posicao(matriz_jogadas,abaixo,j)) {
        *linha_chutada = acima;
      }
    } else if (*linha_ou_coluna == 2) {
      *linha_chutada = i;
      int esquerda = encontrar_primeira_area_nao_atingida_coluna_esquerda(matriz_jogadas,0,j,i);
      int direita = encontrar_primeira_area_nao_atingida_coluna_direita(matriz_jogadas,j,(total_colunas-1),i);
      if (direita!=j && esquerda!=j && !atirou_na_posicao(matriz_jogadas,i,direita) && !atirou_na_posicao(matriz_jogadas,i,esquerda)) {
        int opcao_linha = rand()%2;
        if (opcao_linha==0) {
          *coluna_chutada = direita;
        } else {
          *coluna_chutada = esquerda;
        }
      } else if (atirou_na_posicao(matriz_jogadas,i,direita) && atirou_na_posicao(matriz_jogadas,i,esquerda)) {
        *linha_ou_coluna = 1;
        chutar_posicao(matriz,matriz_jogadas,linha_chutada,coluna_chutada,i,j,total_linhas,total_colunas,linha_ou_coluna,direcao);
      } else if (atirou_na_posicao(matriz_jogadas,i,direita)) {
        *coluna_chutada = esquerda;
      } else if (atirou_na_posicao(matriz_jogadas,i,esquerda)) {
        *coluna_chutada = direita;
      }
    }
  } else if (tiver_extremidade_esquerda(j) && !tiver_extremidade_direita(j,total_colunas)
             && tiver_extremidade_acima(i) && !tiver_extremidade_abaixo(i,total_linhas)) {
    if (*linha_ou_coluna == 0) {
      if (!atirou_na_posicao(matriz_jogadas,i,j-1) && !atirou_na_posicao(matriz_jogadas,i-1,j)) {
      int opcao = rand()%2;
      if (opcao == 0) {
        *linha_chutada = i-1;
        *coluna_chutada = j;
      } else {
        *linha_chutada = i;
        *coluna_chutada = j-1;
      }
      } else if (atirou_na_posicao(matriz_jogadas,i,j-1) && !acertou(matriz_jogadas,i,j-1)) {
        *linha_ou_coluna = 1;
      } else if (atirou_na_posicao(matriz_jogadas,i-1,j) && !acertou(matriz_jogadas,i-1,j)) {
        *linha_ou_coluna = 2;
      } else {
        *linha_ou_coluna = (rand()%2)+1;
      }
    } 
    if (*linha_ou_coluna == 1) {
      int acima = encontrar_primeira_area_nao_atingida_linha_acima(matriz_jogadas,0,i,j);
      *linha_chutada = acima;
      *coluna_chutada = j;
      if (atirou_na_posicao(matriz_jogadas,acima,j)) {
        *linha_ou_coluna = 2;
        chutar_posicao(matriz,matriz_jogadas,linha_chutada,coluna_chutada,i,j,total_linhas,total_colunas,linha_ou_coluna,direcao);
      }
    } else if (*linha_ou_coluna == 2) {
      int esquerda = encontrar_primeira_area_nao_atingida_coluna_esquerda(matriz_jogadas,0,j,i);
      *linha_chutada = i;
      *coluna_chutada = esquerda;
      if (atirou_na_posicao(matriz_jogadas,i,esquerda)) {
        *linha_ou_coluna = 1;
        chutar_posicao(matriz,matriz_jogadas,linha_chutada,coluna_chutada,i,j,total_linhas,total_colunas,linha_ou_coluna,direcao);
      }
    }
  } else if (!tiver_extremidade_esquerda(j) && tiver_extremidade_direita(j,total_colunas)
             && tiver_extremidade_acima(i) && !tiver_extremidade_abaixo(i,total_linhas)) {
    if (*linha_ou_coluna == 0) {
      if (!atirou_na_posicao(matriz_jogadas,i-1,j) && !atirou_na_posicao(matriz_jogadas,i,j+1)) {
        int opcao = rand()%2;
        if (opcao == 0) {
          *linha_chutada = i-1;
          *coluna_chutada = j;
        } else {
          *linha_chutada = i;
          *coluna_chutada = j+1;
        }
      } else if (atirou_na_posicao(matriz_jogadas,i,j+1) && !acertou(matriz_jogadas,i,j+1)) {
        *linha_ou_coluna = 1;
      } else if (atirou_na_posicao(matriz_jogadas,i-1,j) && !acertou(matriz_jogadas,i-1,j)) {
        *linha_ou_coluna = 2;
      } else {
        *linha_ou_coluna = (rand()%2)+1;
      }
    }
    if (*linha_ou_coluna == 1) {
      int acima = encontrar_primeira_area_nao_atingida_linha_acima(matriz_jogadas,0,i,j);
      *linha_chutada = acima;
      *coluna_chutada = j;
      if (atirou_na_posicao(matriz_jogadas,acima,j)) {
        *linha_ou_coluna = 2;
        chutar_posicao(matriz,matriz_jogadas,linha_chutada,coluna_chutada,i,j,total_linhas,total_colunas,linha_ou_coluna,direcao);
      }
    } else if (*linha_ou_coluna == 2) {
      int direita = encontrar_primeira_area_nao_atingida_coluna_direita(matriz_jogadas,j,total_colunas-1,i);
      *linha_chutada = i;
      *coluna_chutada = direita;
      if (atirou_na_posicao(matriz_jogadas,i,direita)) {
        *linha_ou_coluna = 1;
        chutar_posicao(matriz,matriz_jogadas,linha_chutada,coluna_chutada,i,j,total_linhas,total_colunas,linha_ou_coluna,direcao);
      }
    }
  } else if (!tiver_extremidade_esquerda(j) && tiver_extremidade_direita(j,total_colunas)
             && !tiver_extremidade_acima(i) && tiver_extremidade_abaixo(i,total_linhas)) {
    if (*linha_ou_coluna == 0) {
      if (!atirou_na_posicao(matriz_jogadas,i+1,j) && !atirou_na_posicao(matriz_jogadas,i,j+1)) {
        int opcao = rand()%2;
        if (opcao == 0) {
          *linha_chutada = i+1;
          *coluna_chutada = j;
        } else {
          *linha_chutada = i;
          *coluna_chutada = j+1;
        }
      } else if (atirou_na_posicao(matriz_jogadas,i,j+1) && !acertou(matriz_jogadas,i,j+1)) {
        *linha_ou_coluna = 1;
      } else if (atirou_na_posicao(matriz_jogadas,i+1,j) && !acertou(matriz_jogadas,i+1,j)) {
        *linha_ou_coluna = 2;
      } else {
        *linha_ou_coluna = (rand()%2)+1;
      }
    } 
    if (*linha_ou_coluna == 1) {
      int abaixo = encontrar_primeira_area_nao_atingida_linha_abaixo(matriz_jogadas,i,total_linhas-1,j);
      *linha_chutada = abaixo;
      *coluna_chutada = j;
      if (atirou_na_posicao(matriz_jogadas,abaixo,j)) {
        *linha_ou_coluna = 2;
        chutar_posicao(matriz,matriz_jogadas,linha_chutada,coluna_chutada,i,j,total_linhas,total_colunas,linha_ou_coluna,direcao);
      }
    } else if (*linha_ou_coluna == 2) {
      int direita = encontrar_primeira_area_nao_atingida_coluna_direita(matriz_jogadas,j,total_colunas-1,i);
      *linha_chutada = i;
      *coluna_chutada = direita;
      if (atirou_na_posicao(matriz_jogadas,i,direita)) {
        *linha_ou_coluna = 1;
        chutar_posicao(matriz,matriz_jogadas,linha_chutada,coluna_chutada,i,j,total_linhas,total_colunas,linha_ou_coluna,direcao);
      }
    }
  } else if (tiver_extremidade_esquerda(j) && !tiver_extremidade_direita(j,total_colunas)
             && !tiver_extremidade_acima(i) && tiver_extremidade_abaixo(i,total_linhas)) {
    if (*linha_ou_coluna == 0) {
      if (!atirou_na_posicao(matriz_jogadas,i+1,j) && !atirou_na_posicao(matriz_jogadas,i,j-1)) {
        int opcao = rand()%2;
        if (opcao == 0) {
          *linha_chutada = i+1;
          *coluna_chutada = j;
        } else {
          *linha_chutada = i;
          *coluna_chutada = j-1;
        }
      } else if (atirou_na_posicao(matriz_jogadas,i,j-1) && !acertou(matriz_jogadas,i,j-1)) {
        *linha_ou_coluna = 1;
      } else if (atirou_na_posicao(matriz_jogadas,i+1,j) && !acertou(matriz_jogadas,i+1,j)) {
        *linha_ou_coluna = 2;
      } else {
        *linha_ou_coluna = (rand()%2)+1;
      }
    }
    if (*linha_ou_coluna == 1) {
      int abaixo = encontrar_primeira_area_nao_atingida_linha_abaixo(matriz_jogadas,i,total_linhas-1,j);
      *linha_chutada = abaixo;
      *coluna_chutada = j;
      if (atirou_na_posicao(matriz_jogadas,abaixo,j)) {
        *linha_ou_coluna = 2;
        chutar_posicao(matriz,matriz_jogadas,linha_chutada,coluna_chutada,i,j,total_linhas,total_colunas,linha_ou_coluna,direcao);
      }
    } else if (*linha_ou_coluna == 2) {
      int esquerda = encontrar_primeira_area_nao_atingida_coluna_esquerda(matriz_jogadas,0,j,i);
      *linha_chutada = i;
      *coluna_chutada = esquerda;
      if (atirou_na_posicao(matriz_jogadas,i,esquerda)) {
        *linha_ou_coluna = 1;
        chutar_posicao(matriz,matriz_jogadas,linha_chutada,coluna_chutada,i,j,total_linhas,total_colunas,linha_ou_coluna,direcao);
      }
    }
  } else if (!tiver_extremidade_esquerda(j) && tiver_extremidade_direita(j,total_colunas)
             && tiver_extremidade_acima(i) && tiver_extremidade_abaixo(i,total_linhas)) {
    if (*linha_ou_coluna == 0) {
      if (!atirou_na_posicao(matriz_jogadas,i+1,j) && !atirou_na_posicao(matriz_jogadas,i,j+1) && !atirou_na_posicao(matriz_jogadas,i-1,j)) {
        int opcao = rand()%3;
        if (opcao == 0) {
          *linha_chutada = i+1;
          *coluna_chutada = j;
        } else if (opcao == 1) {
          *linha_chutada = i;
          *coluna_chutada = j+1;
        } else {
          *linha_chutada = i-1;
          *coluna_chutada = j;
        }
      } else if (atirou_na_posicao(matriz_jogadas,i,j+1) && !acertou(matriz_jogadas,i,j+1)) {
        *linha_ou_coluna = 1;
      } else if ((atirou_na_posicao(matriz_jogadas,i+1,j) && !acertou(matriz_jogadas,i+1,j)) && (atirou_na_posicao(matriz_jogadas,i-1,j) && !acertou(matriz_jogadas,i-1,j))) {
        *linha_ou_coluna = 2;
      } else if (atirou_na_posicao(matriz_jogadas,i+1,j) && !acertou(matriz_jogadas,i+1,j)) {
        verificar_acerto_jogada(matriz_jogadas,i-1,j,linha_chutada,coluna_chutada,linha_ou_coluna,2);
      } else if (atirou_na_posicao(matriz_jogadas,i-1,j) && !acertou(matriz_jogadas,i-1,j)) {
        verificar_acerto_jogada(matriz_jogadas,i+1,j,linha_chutada,coluna_chutada,linha_ou_coluna,2);
      } else {
        *linha_ou_coluna = (rand()%2)+1;
      }
    } 
    if (*linha_ou_coluna == 1) {
      *coluna_chutada = j;
      int acima = encontrar_primeira_area_nao_atingida_linha_acima(matriz_jogadas,0,i,j);
      int abaixo = encontrar_primeira_area_nao_atingida_linha_abaixo(matriz_jogadas,i,total_linhas-1,j);
      if (!atirou_na_posicao(matriz_jogadas,acima,j) && !atirou_na_posicao(matriz_jogadas,abaixo,j)) {
        int opcao_linha = rand()%2;
        if (opcao_linha==0) {
          *linha_chutada = acima;
        } else {
          *linha_chutada = abaixo;
        }
      } else if (atirou_na_posicao(matriz_jogadas,acima,j) && atirou_na_posicao(matriz_jogadas,abaixo,j)) {
        *linha_ou_coluna = 2;
        chutar_posicao(matriz,matriz_jogadas,linha_chutada,coluna_chutada,i,j,total_linhas,total_colunas,linha_ou_coluna,direcao);
      } else if (atirou_na_posicao(matriz_jogadas,acima,j)) {
        *linha_chutada = abaixo;
      } else if (atirou_na_posicao(matriz_jogadas,abaixo,j)) {
        *linha_chutada = acima;
      }
    } else if (*linha_ou_coluna == 2) {
      int direita = encontrar_primeira_area_nao_atingida_coluna_direita(matriz_jogadas,j,total_colunas-1,i);
      *linha_chutada = i;
      *coluna_chutada = direita;
      if (atirou_na_posicao(matriz_jogadas,i,direita)) {
        *linha_ou_coluna = 1;
        chutar_posicao(matriz,matriz_jogadas,linha_chutada,coluna_chutada,i,j,total_linhas,total_colunas,linha_ou_coluna,direcao);
      }
    }
  } else if (tiver_extremidade_esquerda(j) && tiver_extremidade_direita(j,total_colunas)
             && !tiver_extremidade_acima(i) && tiver_extremidade_abaixo(i,total_linhas)) {
    if (*linha_ou_coluna == 0) {
      if (!atirou_na_posicao(matriz_jogadas,i+1,j) && !atirou_na_posicao(matriz_jogadas,i,j+1) && !atirou_na_posicao(matriz_jogadas,i,j-1)) {
        int opcao = rand()%3;
        if (opcao == 0) {
          *linha_chutada = i+1;
          *coluna_chutada = j;
        } else if (opcao == 1) {
          *linha_chutada = i;
          *coluna_chutada = j+1;
        } else {
          *linha_chutada = i;
          *coluna_chutada = j-1;
        }
      } else if (atirou_na_posicao(matriz_jogadas,i+1,j) && !acertou(matriz_jogadas,i+1,j)) {
        *linha_ou_coluna = 2;
      } else if ((atirou_na_posicao(matriz_jogadas,i,j+1) && !acertou(matriz_jogadas,i,j+1)) && (atirou_na_posicao(matriz_jogadas,i,j-1) && !acertou(matriz_jogadas,i,j-1))) {
        *linha_ou_coluna = 1;
      } else if (atirou_na_posicao(matriz_jogadas,i,j+1) && !acertou(matriz_jogadas,i,j+1)) {
        verificar_acerto_jogada(matriz_jogadas,i,j-1,linha_chutada,coluna_chutada,linha_ou_coluna,1);
      } else if (atirou_na_posicao(matriz_jogadas,i,j-1) && !acertou(matriz_jogadas,i,j-1)) {
        verificar_acerto_jogada(matriz_jogadas,i,j+1,linha_chutada,coluna_chutada,linha_ou_coluna,1);
      } else {
        *linha_ou_coluna = (rand()%2)+1;
      }
    } 
    if (*linha_ou_coluna == 1) {
      int abaixo = encontrar_primeira_area_nao_atingida_linha_abaixo(matriz_jogadas,i,total_linhas-1,j);
      *linha_chutada = abaixo;
      *coluna_chutada = j;
      if (atirou_na_posicao(matriz_jogadas,abaixo,j)) {
        *linha_ou_coluna = 2;
        chutar_posicao(matriz,matriz_jogadas,linha_chutada,coluna_chutada,i,j,total_linhas,total_colunas,linha_ou_coluna,direcao);
      }
    } else if (*linha_ou_coluna == 2) {
      *linha_chutada = i;
      int esquerda = encontrar_primeira_area_nao_atingida_coluna_esquerda(matriz_jogadas,0,j,i);
      int direita = encontrar_primeira_area_nao_atingida_coluna_direita(matriz_jogadas,j,total_colunas-1,i);
      if (!atirou_na_posicao(matriz_jogadas,i,direita) && !atirou_na_posicao(matriz_jogadas,i,esquerda)) {
        int opcao_linha = rand()%2;
        if (opcao_linha==0) {
          *coluna_chutada = direita;
        } else {
          *coluna_chutada = esquerda;
        }
      } else if (atirou_na_posicao(matriz_jogadas,i,direita) && atirou_na_posicao(matriz_jogadas,i,esquerda)) {
        *linha_ou_coluna = 1;
        chutar_posicao(matriz,matriz_jogadas,linha_chutada,coluna_chutada,i,j,total_linhas,total_colunas,linha_ou_coluna,direcao);
      } else if (atirou_na_posicao(matriz_jogadas,i,direita)) {
        *coluna_chutada = esquerda;
      } else if (atirou_na_posicao(matriz_jogadas,i,esquerda)) {
        *coluna_chutada = direita;
      }
    }
  } else if (tiver_extremidade_esquerda(j) && !tiver_extremidade_direita(j,total_colunas)
             && tiver_extremidade_acima(i) && tiver_extremidade_abaixo(i,total_linhas)) {
    if (*linha_ou_coluna == 0) {
      if (!atirou_na_posicao(matriz_jogadas,i+1,j) && !atirou_na_posicao(matriz_jogadas,i,j-1) && !atirou_na_posicao(matriz_jogadas,i-1,j)) {
        int opcao = rand()%3;
        if (opcao == 0) {
          *linha_chutada = i+1;
          *coluna_chutada = j;
        } else if (opcao == 1) {
          *linha_chutada = i;
          *coluna_chutada = j-1;
        } else {
          *linha_chutada = i-1;
          *coluna_chutada = j;
        }
      } else if (atirou_na_posicao(matriz_jogadas,i,j-1) && !acertou(matriz_jogadas,i,j-1)) {
        *linha_ou_coluna = 1;
      } else if ((atirou_na_posicao(matriz_jogadas,i+1,j) && !acertou(matriz_jogadas,i+1,j)) && (atirou_na_posicao(matriz_jogadas,i-1,j) && !acertou(matriz_jogadas,i-1,j))) {
        *linha_ou_coluna = 2;
      } else if (atirou_na_posicao(matriz_jogadas,i+1,j) && !acertou(matriz_jogadas,i+1,j)) {
        verificar_acerto_jogada(matriz_jogadas,i-1,j,linha_chutada,coluna_chutada,linha_ou_coluna,2);
      } else if (atirou_na_posicao(matriz_jogadas,i-1,j) && !acertou(matriz_jogadas,i-1,j)) {
        verificar_acerto_jogada(matriz_jogadas,i+1,j,linha_chutada,coluna_chutada,linha_ou_coluna,2);
      } else {
        *linha_ou_coluna = (rand()%2)+1;
      }
    } 
    if (*linha_ou_coluna == 1) {
      *coluna_chutada = j;
      int acima = encontrar_primeira_area_nao_atingida_linha_acima(matriz_jogadas,0,i,j);
      int abaixo = encontrar_primeira_area_nao_atingida_linha_abaixo(matriz_jogadas,i,total_linhas-1,j);
      if (!atirou_na_posicao(matriz_jogadas,acima,j) && !atirou_na_posicao(matriz_jogadas,abaixo,j)) {
        int opcao_linha = rand()%2;
        if (opcao_linha==0) {
          *linha_chutada = acima;
        } else {
          *linha_chutada = abaixo;
        }
      } else if (atirou_na_posicao(matriz_jogadas,acima,j) && atirou_na_posicao(matriz_jogadas,abaixo,j)) {
        *linha_ou_coluna = 2;
        chutar_posicao(matriz,matriz_jogadas,linha_chutada,coluna_chutada,i,j,total_linhas,total_colunas,linha_ou_coluna,direcao);
      } else if (atirou_na_posicao(matriz_jogadas,acima,j)) {
        *linha_chutada = abaixo;
      } else if (atirou_na_posicao(matriz_jogadas,abaixo,j)) {
        *linha_chutada = acima;
      }
    } else if (*linha_ou_coluna == 2) {
      int esquerda = encontrar_primeira_area_nao_atingida_coluna_esquerda(matriz_jogadas,0,j,i);
      *linha_chutada = i;
      *coluna_chutada = esquerda;
      if (atirou_na_posicao(matriz_jogadas,i,esquerda)) {
        *linha_ou_coluna = 1;
        chutar_posicao(matriz,matriz_jogadas,linha_chutada,coluna_chutada,i,j,total_linhas,total_colunas,linha_ou_coluna,direcao);
      }
    }
  } else if (tiver_extremidade_esquerda(j) && tiver_extremidade_direita(j,total_colunas)
             && tiver_extremidade_acima(i) && !tiver_extremidade_abaixo(i,total_linhas)) {
    if (*linha_ou_coluna == 0) {
      if (!atirou_na_posicao(matriz_jogadas,i-1,j) && !atirou_na_posicao(matriz_jogadas,i,j-1) && !atirou_na_posicao(matriz_jogadas,i,j+1)) {
        int opcao = rand()%3;
        if (opcao == 0) {
          *linha_chutada = i-1;
          *coluna_chutada = j;
        } else if (opcao == 1) {
          *linha_chutada = i;
          *coluna_chutada = j-1;
        } else {
          *linha_chutada = i;
          *coluna_chutada = j+1;
        }
      } else if (atirou_na_posicao(matriz_jogadas,i-1,j) && !acertou(matriz_jogadas,i-1,j)) {
        *linha_ou_coluna = 2;
      } else if ((atirou_na_posicao(matriz_jogadas,i,j-1) && !acertou(matriz_jogadas,i,j-1)) && (atirou_na_posicao(matriz_jogadas,i,j+1) && !acertou(matriz_jogadas,i,j+1))) {
        *linha_ou_coluna = 1;
      } else if (atirou_na_posicao(matriz_jogadas,i,j-1) && !acertou(matriz_jogadas,i,j-1)) {
        verificar_acerto_jogada(matriz_jogadas,i,j+1,linha_chutada,coluna_chutada,linha_ou_coluna,1);
      } else if (atirou_na_posicao(matriz_jogadas,i,j+1) && !acertou(matriz_jogadas,i,j+1)) {
        verificar_acerto_jogada(matriz_jogadas,i,j-1,linha_chutada,coluna_chutada,linha_ou_coluna,1);
      } else {
        *linha_ou_coluna = (rand()%2)+1;
      }
    }
    if (*linha_ou_coluna == 1) {
      int acima = encontrar_primeira_area_nao_atingida_linha_acima(matriz_jogadas,0,i,j);
      *linha_chutada = acima;
      *coluna_chutada = j;
      if (atirou_na_posicao(matriz_jogadas,acima,j)) {
        *linha_ou_coluna = 2;
        chutar_posicao(matriz,matriz_jogadas,linha_chutada,coluna_chutada,i,j,total_linhas,total_colunas,linha_ou_coluna,direcao);
      }
    } else if (*linha_ou_coluna == 2) {
      *linha_chutada = i;
      int esquerda = encontrar_primeira_area_nao_atingida_coluna_esquerda(matriz_jogadas,0,j,i);
      int direita = encontrar_primeira_area_nao_atingida_coluna_direita(matriz_jogadas,j,total_colunas-1,i);
      if (!atirou_na_posicao(matriz_jogadas,i,direita) && !atirou_na_posicao(matriz_jogadas,i,esquerda)) {
        int opcao_linha = rand()%2;
        if (opcao_linha==0) {
          *coluna_chutada = direita;
        } else {
          *coluna_chutada = esquerda;
        }
      } else if (atirou_na_posicao(matriz_jogadas,i,direita) && atirou_na_posicao(matriz_jogadas,i,esquerda)) {
        *linha_ou_coluna = 1;
        chutar_posicao(matriz,matriz_jogadas,linha_chutada,coluna_chutada,i,j,total_linhas,total_colunas,linha_ou_coluna,direcao);
      } else if (atirou_na_posicao(matriz_jogadas,i,direita)) {
        *coluna_chutada = esquerda;
      } else if (atirou_na_posicao(matriz_jogadas,i,esquerda)) {
        *coluna_chutada = direita;
      }
    }
  }
}


bool verificar_navio_afundou(int **matriz,int linha, int coluna,int linhas, int colunas,int indice_navio_jogador) {
  for (int i = 0;i<colunas;i++) {
    if (matriz[linha][i] == indice_navio_jogador) {
      return false;
    }
  }
  for (int i = 0;i<linhas;i++) {
    if (matriz[i][coluna] == indice_navio_jogador) {
      return false;
    }
  }
  return true;
}

bool ocorreu_variacao(int valor_antigo,int valor_novo) {
  if (valor_antigo-valor_novo!=0) {
    return true;
  } 
  return false;
}

void setar_copia_tabuleiro_jogador(int **matriz_copia,int indice_navio,int linhas,int colunas) {
  for (int i=0;i<linhas;i++) {
    for (int j=0;j<colunas;j++) {
      if (matriz_copia[i][j]==indice_navio) {
        matriz_copia[i][j] = -1;
      }
    }
  }
}

void imprimir_tabuleiro_copia(int **matriz_copia,int l,int c) {
  for (int i = 0; i < l; i++){
    for (int j = 0; j < c; j++){
      printf("[%d]",matriz_copia[i][j]);
    }
    printf("\n");
  }
}

void gerar_jogada_computador(int **matriz,int **matriz_jogadas_computador,int linhas, int colunas,
                             int *indice_navio,int *linha_acertada,
                             int *coluna_acertada,int *linha_ou_coluna,int *direcao) {
  int linha_escolhida = -1;
  int coluna_escolhida = -1;

  if (*linha_acertada!=-1 && *coluna_acertada!=-1) {
    chutar_posicao(matriz,matriz_jogadas_computador,&linha_escolhida,&coluna_escolhida,*linha_acertada,*coluna_acertada,linhas,colunas,linha_ou_coluna,direcao);
  }

  if (linha_escolhida==-1 || coluna_escolhida==-1) {
    linha_escolhida = rand()%linhas;
    coluna_escolhida = rand()%colunas;
    while(matriz_jogadas_computador[linha_escolhida][coluna_escolhida]>0) {
      linha_escolhida = rand()%linhas;
      coluna_escolhida = rand()%colunas;
    }
  }
  printf("\nO computador escolheu a posicao %d%c do seu tabuleiro.",coluna_escolhida+1,linha_escolhida+65);
  printf("\nSeu tabuleiro: \n([#] -> area de navio)\n([~] -> agua)\n");
  printf("([X] -> area de navio atingida)\n");
  imprimir_tabuleiro(matriz,linhas,colunas);
  int indice_navio_antigo = *indice_navio;
  if (verificar_jogada(matriz,matriz_jogadas_computador,linha_escolhida,coluna_escolhida,indice_navio)) {
    if (verificar_navio_afundou(matriz,linha_escolhida,coluna_escolhida,linhas,colunas,*indice_navio)) {
      setar_copia_tabuleiro_jogador(matriz_jogador_copia,*indice_navio,linhas,colunas);
      printf("\nO computador afundou um navio seu.\n");
      *indice_navio = 0;
      *linha_acertada = -1;
      *coluna_acertada = -1;
      *linha_ou_coluna = 0;
      *direcao = 0;
    } else {
      if (*linha_acertada != -1 && *coluna_acertada != -1) {
        if (ocorreu_variacao(*linha_acertada,linha_escolhida)) {
          *linha_ou_coluna = 1;
        } else if (ocorreu_variacao(*coluna_acertada,coluna_escolhida)) {
          *linha_ou_coluna = 2;
        }
      } else {
        *linha_acertada = linha_escolhida;
        *coluna_acertada = coluna_escolhida;
        *linha_ou_coluna = 0;
      }
      printf("\nO computador acertou uma area de navio.\n");
    }
  } else {
    printf("\nO computador acertou a agua.\n");
  }
}

void colocar_pecas_tabuleiro(int qtd_pa,int qtd_nt,int qtd_ct,int qtd_sb,int **matriz,int linhas,int colunas) {
  colocar_peca_tabuleiro(qtd_pa,5,matriz,linhas,colunas,2);
  int indice_navio = 2+qtd_pa;
  colocar_peca_tabuleiro(qtd_nt,4,matriz,linhas,colunas,indice_navio);
  indice_navio += qtd_nt;
  colocar_peca_tabuleiro(qtd_ct,3,matriz,linhas,colunas,indice_navio);
  indice_navio += qtd_ct;
  colocar_peca_tabuleiro(qtd_sb,2,matriz,linhas,colunas,indice_navio);
}

bool verificar_chute_jogador(int **matriz,int coluna_escolhida,int linha_letra,int colunas,int linhas) {
  if (coluna_escolhida>colunas || coluna_escolhida<1 || linha_letra>65+linhas-1 || linha_letra<65) {
    return true;
  }
  coluna_escolhida--;
  linha_letra = linha_letra - 65;
  if (matriz[linha_letra][coluna_escolhida]>0) {
    return true;
  }
}

bool verificar_fim_jogo(int **matriz,int linhas,int colunas) {
  for (int i = 0; i < linhas; i++){
    for (int j = 0; j < colunas; j++){
      if (matriz[i][j]>=2) {
        return false;
      }
    }
  }
  return true;
}

void tempo_formatado(int segundos) {
  if (segundos>=60) {
    int minutos = segundos/60;
    while(segundos>=60) {
      segundos = segundos - 60;
    }
    if (segundos != 0) {
      printf("Tempo de jogo:%dmin %ds.\n",minutos,segundos);
    } else {
      printf("Tempo de jogo:%dmin.\n",minutos);
    }
  } else {
    printf("Tempo de jogo:%ds.\n",segundos);
  }
}

void copiar_tabuleiro(int **matriz_jogador,int **matriz_jogador_copia,int linhas,int colunas) {
  for (int i=0;i<linhas;i++) {
    for (int j=0;j<colunas;j++) {
      matriz_jogador_copia[i][j] = matriz_jogador[i][j];
    }
  }
}

int **liberar_memoria(int **matriz,int linhas) {
  for (int i=0; i<linhas; i++) {
    free(matriz[i]); 
  }
  free(matriz);
  return NULL;
}

int main() {
  int linhas,colunas,opcao;

  srand(time(NULL));
  
  printf("Escolha entre jogar sozinho (digite 1) ou contra o computador (digite 2).");
  printf("\nSe voce optar por jogar sozinho, voce nao sabera a disposição das peças no tabuleiro\ne devera chutar posicoes ate afundar todos os navios.");
  printf("\nSe voce optar por jogar contra o computador, você sabera a disposicao do seu tabuleiro\nmas nao sabera a do computador.");
  printf("\nResposta: ");
  scanf("%d",&opcao);

  while(opcao!= 1 && opcao!=2) {
    printf("\nEscolha entre jogar sozinho (digite 1) ou contra o computador (digite 2).");
    printf("\nSe voce optar por jogar sozinho, voce nao sabera a disposição das peças no tabuleiro\ne devera chutar posicoes ate afundar todos os navios.");
    printf("\nSe voce optar por jogar contra o computador, você sabera a disposicao do seu tabuleiro\nmas nao sabera a do computador.");
    printf("\nResposta: ");
    scanf("%d",&opcao);
  }

  printf("Voce precisa informar o numero de linhas e de colunas do tabuleiro.");
  printf("\nQuanto maior o tabuleiro, maior a quantidade de pecas.");

  if (opcao == 1) {
    digitar_linha_coluna_sozinho(&linhas,&colunas);
    while(colunas*linhas < 25) {
      printf("\nO tabuleiro deve ter mais que 25 quadrados.");
      digitar_linha_coluna_sozinho(&linhas,&colunas);
    }
    int **matriz = inicializar_tabuleiro(linhas,colunas);
    int **matriz_jogadas_jogador = inicializar_tabuleiro(linhas,colunas);
    int qtd_pa, qtd_nt, qtd_ct, qtd_sb;
    atribuir_quantidade(&qtd_pa,&qtd_nt,&qtd_ct,&qtd_sb,linhas,colunas);
    colocar_pecas_tabuleiro(qtd_pa,qtd_nt,qtd_ct,qtd_sb,matriz,linhas,colunas);
    time_t inicio = time(NULL);
    while(true) {
      int coluna_escolhida;
      char linha_letra[1];
      printf("\nO tabuleiro que representa seus ataques esta assim: \n");
      printf("([X] -> atacou area de navio)\n");
      printf("([-] -> atirou na agua)\n");
      printf("([?] -> nao atirou ainda)\n");
      imprimir_tabuleiro_jogadas(matriz_jogadas_jogador,linhas,colunas);
      printf("\nChute uma posicao para acertar os navios do tabuleiro do computador: (Exemplo 1A) ");
      scanf("%d%c",&coluna_escolhida,linha_letra);
      while (verificar_chute_jogador(matriz_jogadas_jogador,coluna_escolhida,linha_letra[0],colunas,linhas)) {
        printf("\nChute uma posicao ainda nao atingida para acertar os navios do tabuleiro do computador: (Exemplo 1A) ");
        scanf("%d%c",&coluna_escolhida,linha_letra);
      }
      coluna_escolhida--;
      int linha_escolhida = linha_letra[0] - 65;
      int indice_navio_jogador;
      if (verificar_jogada(matriz,matriz_jogadas_jogador,linha_escolhida,coluna_escolhida,&indice_navio_jogador)) {
        if (verificar_navio_afundou(matriz,linha_escolhida,coluna_escolhida,linhas,colunas,indice_navio_jogador)) {
          printf("VOCE AFUNDOU UM NAVIO INTEIRO.\n");
        } else {
          printf("VOCE ACERTOU UMA AREA DE NAVIO.\n");
        }
      } else {
        printf("VOCE ACERTOU A AGUA!\n");
      }
      if (verificar_fim_jogo(matriz,linhas,colunas)) {
        printf("VOCE ACERTOU TODOS OS NAVIOS. PARABENS!\n");
        time_t tempo_total = time(NULL) - inicio;
        int segundos = (int)tempo_total;
        tempo_formatado(segundos);
        matriz = liberar_memoria(matriz,linhas);
        matriz_jogadas_jogador = liberar_memoria(matriz_jogadas_jogador,linhas);
        break;
      }
    }
  } else if (opcao == 2) {
    digitar_linha_coluna(&linhas,&colunas);
    while(colunas*linhas < 25) {
      printf("\nO tabuleiro deve ter mais que 25 quadrados.");
      digitar_linha_coluna(&linhas,&colunas);
    }
    int **matriz_jogador = inicializar_tabuleiro(linhas,colunas);
    int **matriz_jogadas_jogador = inicializar_tabuleiro(linhas,colunas);
    matriz_jogador_copia = inicializar_tabuleiro(linhas,colunas);
    int **matriz_computador = inicializar_tabuleiro(linhas,colunas);
    int **matriz_jogadas_computador = inicializar_tabuleiro(linhas,colunas);
    int indice_navio = 0,linha_acertada = -1, coluna_acertada = -1, linha_ou_coluna = 0,direcao = 0;
    int qtd_pa, qtd_nt, qtd_ct, qtd_sb;
    atribuir_quantidade(&qtd_pa,&qtd_nt,&qtd_ct,&qtd_sb,linhas,colunas);
    colocar_pecas_tabuleiro(qtd_pa,qtd_nt,qtd_ct,qtd_sb,matriz_jogador,linhas,colunas);
    copiar_tabuleiro(matriz_jogador,matriz_jogador_copia,linhas,colunas);
    colocar_pecas_tabuleiro(qtd_pa,qtd_nt,qtd_ct,qtd_sb,matriz_computador,linhas,colunas);
    time_t inicio = time(NULL);

    printf("\nO seu tabuleiro ficou assim: \n([#] -> area de navio)\n([~] -> agua)\n");
    printf("([X] -> area de navio atingida)\n");
    imprimir_tabuleiro(matriz_jogador,linhas,colunas);
    
    while(true) {
      printf("SUA VEZ");
      int coluna_escolhida;
      char linha_letra[1];
      printf("\nO tabuleiro que representa seus ataques esta assim: \n");
      printf("([X] -> atacou area de navio)\n");
      printf("([-] -> atirou na agua)\n");
      printf("([?] -> nao atirou ainda)\n");
      imprimir_tabuleiro_jogadas(matriz_jogadas_jogador,linhas,colunas);
      printf("\nChute uma posicao para acertar os navios do tabuleiro do computador: (Exemplo 1A) ");
      scanf("%d%c",&coluna_escolhida,linha_letra);
      while (verificar_chute_jogador(matriz_jogadas_jogador,coluna_escolhida,linha_letra[0],colunas,linhas)) {
        printf("\nChute uma posicao ainda nao atingida para acertar os navios do tabuleiro do computador: (Exemplo 1A) ");
        scanf("%d%c",&coluna_escolhida,linha_letra);
      }
      coluna_escolhida--;
      int linha_escolhida = linha_letra[0] - 65;
      int indice_navio_jogador;
      if (verificar_jogada(matriz_computador,matriz_jogadas_jogador,linha_escolhida,coluna_escolhida,&indice_navio_jogador)) {
        if (verificar_navio_afundou(matriz_computador,linha_escolhida,coluna_escolhida,linhas,colunas,indice_navio_jogador)) {
          printf("VOCE AFUNDOU UM NAVIO INTEIRO.\n");
        } else {
          printf("VOCE ACERTOU UMA AREA DE NAVIO.\n");
        }
      } else {
        printf("VOCE ACERTOU A AGUA!\n");
      }
      if (verificar_fim_jogo(matriz_computador,linhas,colunas)) {
        printf("VOCE AFUNDOU TODOS OS NAVIOS DO COMPUTADOR. PARABENS!\n");
        time_t tempo_total = time(NULL) - inicio;
        int segundos = (int)tempo_total;
        tempo_formatado(segundos);
        matriz_jogador = liberar_memoria(matriz_jogador,linhas);
        matriz_jogadas_jogador = liberar_memoria(matriz_jogadas_jogador,linhas);
        matriz_computador = liberar_memoria(matriz_computador,linhas);
        matriz_jogadas_computador = liberar_memoria(matriz_jogadas_computador,linhas);
        matriz_jogador_copia = liberar_memoria(matriz_jogador_copia,linhas);
        break;
      }
      printf("\n\n\nVEZ DO COMPUTADOR\n\n");
      gerar_jogada_computador(matriz_jogador,matriz_jogadas_computador,linhas,colunas,&indice_navio,&linha_acertada,&coluna_acertada,&linha_ou_coluna,&direcao);
      if (verificar_fim_jogo(matriz_jogador,linhas,colunas)) {
        printf("O computador afundou todos os seus navios. Voce perdeu!\n");
        time_t tempo_total = time(NULL) - inicio;
        int segundos = (int)tempo_total;
        tempo_formatado(segundos);
        matriz_jogador = liberar_memoria(matriz_jogador,linhas);
        matriz_jogadas_jogador = liberar_memoria(matriz_jogadas_jogador,linhas);
        matriz_computador = liberar_memoria(matriz_computador,linhas);
        matriz_jogadas_computador = liberar_memoria(matriz_jogadas_computador,linhas);
        matriz_jogador_copia = liberar_memoria(matriz_jogador_copia,linhas);
        break;
      }
    }
  }
  return 0;
}