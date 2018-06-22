//Aluno: Felipe Cechin Mello. O algoritmo eh um jogo de tabuleiro de 6x6 posicoes. O usuario deve preencher o tabuleiro de acordo com o valor do dado de cada rodada. A cada 10 pontos somados em uma linha ou coluna do tabuleiro, o usuario ganha 10 pontos. Caso linha e coluna simultaneamente, ganha mais 11 pontos (total 31). O jogo termina quando nao houver posicao possivel a ser colocada o valor do dado gerado.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define TAM 6
int dado()
{
  int numero = rand()%6;
  if (numero == 0) return 6;
  return numero;
}

void zerarVetor(int v[],int tamanho)
{
  int i;
  for (i=0;i<tamanho;i++) {
    v[i] = 0;
  }
}

void imprimirTabuleiro(int m[TAM][TAM]) 
{
  int somaLinhas[TAM];
  int somaColunas[TAM];
  int i,j,k;
  zerarVetor(somaLinhas,TAM);
  zerarVetor(somaColunas,TAM);
  
  for(i=0;i<TAM;i++) {
    for(j=0;j<TAM;j++) {
      somaLinhas[i] = somaLinhas[i] + m[i][j];
      somaColunas[i] = somaColunas[i] + m[j][i];
    }
  }
  
  printf("\n---");
  for (i=0;i<TAM;i++) {
    printf("-------");
  }
  printf("-");
  printf("\n");
  for(i=0;i<TAM;i++) {
    printf("|  ");
    for(j=0;j<TAM;j++) {
      if(m[i][j] == 0) {
        printf("(%d-%d)  ",i+1,j+1);
      } else {
        printf("%3d    ",m[i][j]);
      }
    }
    printf("|");
    printf("  %d",somaLinhas[i]);
    printf("\n");
    if (i==5) printf("---");
    else printf("|--");
    for (k=0;k<TAM;k++) {
      printf("-------");
    }
    if (i==5) printf("-");
    else printf("|");
    printf("\n");
  }
  printf("   ");
  for (i=0;i<TAM;i++) {
    printf("%3d    ",somaColunas[i]);
  }
  printf("  SOMA\n");
}

bool verificarTabuleiroPorPosicao(int m[TAM][TAM],int linha,int coluna,int valorDado)
{
  int i,j,somaLinhas[TAM],somaColunas[TAM];
  zerarVetor(somaLinhas,TAM);
  zerarVetor(somaColunas,TAM);
  if (linha <= 0 || coluna <= 0 || linha>TAM || coluna>TAM) {
    return false;
  }
  linha--;
  coluna--;
  if (m[linha][coluna] != 0) {
    printf("\nA posicao escolhida nao esta vazia. Escolha outra!");
    return false;
  }

  for(i=0;i<TAM;i++) {
    for(j=0;j<TAM;j++) {
      somaLinhas[i] = somaLinhas[i] + m[i][j];
      somaColunas[i] = somaColunas[i] + m[j][i];
    }
  }
  
  if (somaLinhas[linha]+valorDado > 10) {
    printf("\nA linha escolhida tera soma maior que 10. Escolha outra!");
    return false;  
  }
  if (somaColunas[coluna]+valorDado > 10) {
    printf("\nA coluna escolhida tera soma maior que 10. Escolha outra!");
    return false;  
  }
  return true;
}

bool verificarSomaTabuleiroPorPosicao(int m[TAM][TAM],int linha,int coluna,int valorDado)
{
  int i,j,somaLinhas[TAM],somaColunas[TAM];
  zerarVetor(somaLinhas,TAM);
  zerarVetor(somaColunas,TAM);
  for(i=0;i<TAM;i++) {
    for(j=0;j<TAM;j++) {
      somaLinhas[i] = somaLinhas[i] + m[i][j];
      somaColunas[i] = somaColunas[i] + m[j][i];
    }
  }
  if (somaLinhas[linha]+valorDado > 10) {
    return false;
  }
  if (somaColunas[coluna]+valorDado > 10) {
    return false;
  }
  return true;
}

bool tabuleiroOk(int m[TAM][TAM],int valorDado)
{
  int i,j;
  
  for(i=0;i<TAM;i++) {
    for(j=0;j<TAM;j++) {
      if (m[i][j] == 0) {
        if (verificarSomaTabuleiroPorPosicao(m,i,j,valorDado)) {
          return true;
        }
      }
    }
  }
  return false;
}

void zerarTabuleiroLinha(int m[TAM][TAM],int i) 
{
  int j;
  for(j=0;j<TAM;j++) {
    m[i][j] = 0;
  }
}

void zerarTabuleiroColuna(int m[TAM][TAM],int i) 
{
  int j;
  for(j=0;j<TAM;j++) {
    m[j][i] = 0;
  }
}

int verificarTabuleiroPontuacao(int m[TAM][TAM],int linha,int coluna)
{
  int i,j,somaLinhas[TAM],somaColunas[TAM],pontuacao = 0;
  zerarVetor(somaLinhas,TAM);
  zerarVetor(somaColunas,TAM);
  
  for(i=0;i<TAM;i++) {
    for(j=0;j<TAM;j++) {
      somaLinhas[i] = somaLinhas[i] + m[i][j];  
      somaColunas[i] = somaColunas[i] + m[j][i];  
    }
  }
  if (somaLinhas[linha] == 10) {
    zerarTabuleiroLinha(m,linha);
    pontuacao = pontuacao + 10;        
  }
  if (somaColunas[coluna] == 10) {
    zerarTabuleiroColuna(m,coluna);
    pontuacao = pontuacao + 10;  
  }
  if (pontuacao == 20) {
    pontuacao = pontuacao + 11;
  }
  if (pontuacao!=0) {
    printf("\nVoce somou %d pontos na ultima rodada.\n",pontuacao);
  }
  return pontuacao;
}

int main()
{
  int valorDado,i,j,m[TAM][TAM],coluna,linha,pontuacao;
  
  for(i=0;i<TAM;i++) {
    for(j=0;j<TAM;j++) {
      m[i][j] = 0;  
    }
  }
  
  //Funcao colocada abaixo para gerar o valor do dado de forma aleatoria. Sem a funcao, o dado gera quase sempre o mesmo valor.
  srand(time(NULL));
  
  valorDado = dado();
  pontuacao = 0;
  while(tabuleiroOk(m,valorDado)) {
    printf("PONTUACAO: %d\n",pontuacao);
    printf("O valor do dado nesse momento eh %d.",valorDado);
    printf("\nO tabuleiro esta assim:");
    imprimirTabuleiro(m);

    linha = 0;
    coluna = 0;
    printf("\nDigite a linha e a coluna que voce quer colocar o valor do dado separadas por hifen (por exemplo: 1-3): ");
    scanf("%d-%d",&linha,&coluna);
    
    while(!verificarTabuleiroPorPosicao(m,linha,coluna,valorDado)) {
      printf("\nDigite uma linha e uma coluna validas separadas por hifen (por exemplo: 1-3): ");
      scanf("%d-%d",&linha,&coluna); 
    }
    linha--;
    coluna--;
    m[linha][coluna] = valorDado;
    printf("\n----------------------------------------------------------------------------------------------------------\n");
    pontuacao = pontuacao + verificarTabuleiroPontuacao(m,linha,coluna);
    
    valorDado = dado();
  }
  printf("O valor do dado nesse momento eh %d.",valorDado);
  printf("\nO tabuleiro ficou assim:");
  imprimirTabuleiro(m);
  printf("Nao ha mais como preencher o tabuleiro com o valor do dado %d.\n",valorDado);
  printf("Voce fez %d pontos.",pontuacao);
  return 0;
}