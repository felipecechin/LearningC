#include <stdio.h>
#include <ctype.h>

FILE *le_nome_e_abre_arquivo_com_modo(char modo[],char mensagem[])
{
  char nome[100];
  FILE *arq;
  do {
    printf("Arquivo de %s: ",mensagem);
    scanf("%s",nome);
    arq = fopen(nome, modo);
    if (arq == NULL) {
      printf("Nao foi possivel abrir o arquivo \"%s\"\n",nome);
    }
  } while (arq == NULL);
  return arq;
}


int cripta(int c, int chave) 
{
  if (c<'A' || c> 'z') return c;
  if (c>='A' && c<='Z') {
    c += chave;
    if (c>'Z') c -= 26;
    if (c<'A') c += 26;
  } else if (c>= 'a' && c<='z') {
    c +=chave;
    if (c>'z') c -= 26;
    if (c<'a') c += 26;
  }
  return c;
}

int main(void)
{
  char nome1[100],nome2[100],linha[100];
  FILE *arq1, *arq2;
  int chave;
  int ch;

//   char caractere;
// scanf("%c",&caractere);
// printf("Voce digitou: %d",caractere);

  arq1 = le_nome_e_abre_arquivo_com_modo("r","entrada");
  arq2 = le_nome_e_abre_arquivo_com_modo("w","saida");

  do {
    printf("Chave: ");
    scanf("%d",&chave);
  } while (chave<-25 || chave>25);

  
  for(;;) {
    ch = fgetc(arq1);
    if (ch==EOF) break;
    ch = cripta(ch,chave);
    ch = fputc(ch,arq2);
    if (ch == EOF) {
      printf("erro na gravacao\n");
      break;
    }
  }


  fclose(arq1);
  fclose(arq2);
  return 0;
}