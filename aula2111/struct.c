#include <stdio.h>
#include <stdlib.h>

struct aluno {
  char nome[10];
  float n1;
  float n2;
  float media;
};

void calcula_media_de_1(struct aluno *a)
{
  a->media = (a->n1+a->n2)/2;
}

void grava_maiores(char nome[],struct aluno t[],int n, float limite)
{
  FILE *a;
  a = fopen(nome,"w");
  if (a == NULL) {
    printf("Nao consegui abrir arquivo de saida\n");
    exit(1);
  }
  int i;
  for (i=0;i<n;i++) {
    if (t[i].media >= limite) fprintf(a, "%s %.2f %.2f %.2f\n", t[i].nome,t[i].n1,t[i].n2,t[i].media);
  }
  fclose(a);
}


int le_alunos(char nome[],struct aluno t[])
{
  FILE *a;
  a = fopen(nome,"r");
  if (a == NULL) {
    printf("Nao consegui abrir arquivo\n");
    exit(1);
  }
  int i;
  for (i=0;i<30;i++) {
    if (3 != fscanf(a, "%s%f%f", t[i].nome,&t[i].n1,&t[i].n2)) {
      break;
    }
  }
  fclose(a);
  return i;
}

float calcula_medias(struct aluno t[],int n)
{
  int i;
  for (i=0;i<n;i++) {
    calcula_media_de_1(&t[i]);
  }
  float s=0;
  for (i=0;i<n;i++) {
    s += t[i].media;
  }
  return s/n;
}

int main(void)
{
  struct aluno turma[30];
  int nalunos;
  float media;
  nalunos = le_alunos("alunos",turma);
  media = calcula_medias(turma,nalunos);
  printf("%f\n",media);

  grava_maiores("saida",turma,nalunos,media);
}