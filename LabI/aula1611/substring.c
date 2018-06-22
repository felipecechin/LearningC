//Funcao que recebe 2 strings e retorna true se a segunda for substring da primeira.
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool substr_pos(char s1[],char s2[],int p)
{
  int i=p,j=0;
  for(;;) {
    if (s2[j] == '\0') return true;
    if (s1[i] == '\0') return false;
    if (s1[i] != s2[j]) return false;
    i++;
    j++;
  }
}

bool verifica_palavra(char s1[],char s2[])
{ 
  int pos;
  pos = 0;
  while(s1[pos] != '\0') {
    if (substr_pos(s1,s2,pos)) return true;
    pos++;
  }
  return false;
}


int main(void) 
{
  char texto[100],palavra[100];

  printf("Escreva: ");
  scanf("%s",texto);
  printf("Escreva uma palavra: ");
  scanf("%s",palavra);

  if (verifica_palavra(texto,palavra)) {
    printf("Achou");
  }
  return 0;
}