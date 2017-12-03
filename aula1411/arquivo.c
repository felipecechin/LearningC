#include <stdio.h>
int main(){
  FILE *a;
  char lin[100];
  char nome[100];
  printf("Digite o nome de um arquivo\n");
  scanf("%s", nome);
  a = fopen(nome, "r");
  if(a == NULL){
    printf("Nao consegui abrir o arquivo\n");
    return 1;
  }
  while(fgets(lin, 100, a) != NULL){
    printf("%s\n", lin);
  }
  fclose(a);
  return 0;
}