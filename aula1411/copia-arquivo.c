#include <stdio.h>
int main(){
  FILE *ae;
  FILE *as;
  char lin[100];
  char nome1[100];
  char nome2[100];
  printf("Digite o nome de um arquivo a copiar\n");
  scanf("%s", nome1);
  printf("Digite o nome do arquivo a gravar\n");
  scanf("%s", nome2);
  ae = fopen(nome1, "r");
  if(ae == NULL){
    printf("Nao consegui abrir o arquivo\n");
    return 1;
  }
  as = fopen(nome2, "w");
  if(as == NULL){
    printf("Nao consegui abrir o arquivo\n");
    return 1;
  }
  while(fgets(lin, 100, ae) != NULL){
    fprintf(as,"%s\n", lin);
  }
  fclose(ae);
  fclose(as);
  return 0;
}