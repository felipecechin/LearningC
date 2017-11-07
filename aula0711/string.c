#include <stdio.h>
#include <string.h>

void meustrcpy(char s1[],char s2[])
{
  int i;

  for (i=0;;i++) {
    s1[i] = s2[i];
    if (s1[i]=='\0') break;
  }
}

void meustrcat(char s1[],char s2[])
{
  int i;
  int tamanhos1 = strlen(s1);
  for (i=0;;i++) {
    s1[tamanhos1+i] = s2[i];
    if (s1[tamanhos1+i]=='\0') break;
  }
}

int main()
{
  char s[10];
  meustrcpy(s,"Joao");
  printf("nome=%s\n",s);
  meustrcat(s," da Silva");
  printf("nome=%s\n",s);
  printf("%d",strlen(s));
  return 0;
}
