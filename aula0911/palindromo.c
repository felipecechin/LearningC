#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> //usado para a funcao isalpha

//Exercicio para fazer:
//Funcao que recebe uma string e altera para ficar só com as letras

bool palindromo(char s[])
{
  int i,j;
  i = 0;
  j = strlen(s)-1;
  while(i<j) {
    while (s[i]==' ') {
      i++;
    }
    while (s[j]==' ') {
      j--;
    }
    if (s[i]!= s[j]) return false;
    i++;
    j--;
  }
  return true;
}

char maiusc(char c)
{
  if (c<'a' || c>'z') return c;
  return c-'a'+'A';
}

void tira_enter_do_final_se_for_o_caso(char s[])
{
  int p = strlen(s)-1;
  if (s[p] == '\n') {
    s[p] = '\0';
  }
}

void troca(char *c1,char *c2)
{
  char t;
  t = *c1;
  *c1 = *c2;
  *c2 = t;
}

void inverte(char s[])
{
  int i = 0;
  int j = strlen(s)-1;
  char aux;
  while(i<j) {
    troca(&s[i],&s[j]);
    i++;
    j--;
  }
}

bool verifica_letra(char c) 
{
  if (c>='a' || c<='z') return true;
  return false;
}

void remove_tralha(char s[])
{
  int i,j;
  i = 0;
  j = 0;
  while(s[j]!='\0') {
    if (isalpha(s[j])) {
      s[i++] = s[j];
    }
    j++;
  }
  s[i] = '\0';
}

int main()
{
  char f[10];
  printf("Digite uma frase\n");
  fgets(f,10,stdin);
  tira_enter_do_final_se_for_o_caso(f);
  if (palindromo(f)) {
    printf("Eh um palindromo\n");
  } else {
    printf("Nao eh\n");
  }

  remove_tralha(f);
  printf("%s",f);

  // if (isalpha(2)) {
  //   printf("o fernando eh gay e puto");
  // } else {
  //   printf("nao eh");
  // }

  //printf("\n\n%c",maiusc('b'));

  return 0;
}