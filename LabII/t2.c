#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <unistd.h> 
#include <math.h>

    //Aluno: Felipe Cechin Mello

    // Os dados devem ser armazenados em listas em memória (não será usado acesso a BD neste trabalho).
    // Deve ser possível cadastrar alunos, professores, disciplinas, turmas e avaliações. Cada cadastro deve possibilitar inclusão, exclusão e busca.
    // Deve ser possível cadastrar cursos.
    // Deve ser possível matricular alunos em uma turma.
    // Uma turma pode ter mais de um professor associado.
    // Uma turma não deve ter mais de 50 alunos.
    // Cada aluno deve ter os seguintes dados: matrícula, nome, curso.
    // Cada professor deve ter os seguintes dados: siape, nome, área de atuação, titulação.
    // Cada disciplina deve ter os seguintes dados: código, curso, nome, carga horária, pré-requisitos.
    // Deve ser possível lançar notas para as avaliações dos alunos.
    // Deve ser possível lançar aulas ministradas. Cada aula ministrada possui os seguintes dados: data, conteúdo ministrado.
    // Deve ser possível lançar as faltas para as aulas ministradas para uma turma.
    // Deve ser possível gerar um relatório mostrando os alunos aprovados, reprovados, ou reprovados por frequência (segundo as regras da UFSM).


struct curso {
  char nome[50];
};

typedef struct curso curso;

struct no_curso {
  curso *curso;
  struct no_curso *proximo;
};

struct lista_cursos {
  struct no_curso *inicio;
  int cont;
  struct no_curso *fim;
};

struct aluno {
  long int matricula;
  char nome[50];
  char curso[50];
};

typedef struct aluno aluno;

struct no_aluno {
  aluno *aluno;
  struct no_aluno *proximo;
};

struct lista_alunos {
  struct no_aluno *inicio;
  int cont;
  struct no_aluno *fim;
};

struct professor {
  long int siape;
  char nome[50];
  char area_atuacao[30];
  char titulacao[50];
};

typedef struct professor professor;

struct no_professor {
  professor *professor;
  struct no_professor *proximo;
};

struct lista_professores {
  struct no_professor *inicio;
  int cont;
  struct no_professor *fim;
};

struct disciplina {
  char codigo[10];
  char curso[50];
  char nome[30];
  int carga_horaria;
  char pre_requisitos[100];
};

typedef struct disciplina disciplina;

struct no_disciplina {
  disciplina *disciplina;
  struct no_disciplina *proximo;
};

struct lista_disciplinas {
  struct no_disciplina *inicio;
  int cont;
  struct no_disciplina *fim;
};

struct lista_professores_turma {
  struct no_professor *inicio;
  int cont;
  struct no_professor *fim;
};

struct lista_alunos_turma {
  struct no_aluno *inicio;
  int cont;
  struct no_aluno *fim;
};

struct avaliacao {
  long int matricula;
  float nota1;
  float nota2;
};

typedef struct avaliacao avaliacao;

struct no_avaliacao {
  avaliacao *avaliacao;
  struct no_avaliacao *proximo;
};

struct lista_avaliacoes_turma {
  struct no_avaliacao *inicio;
  int cont;
  struct no_avaliacao *fim;
};

struct lista_alunos_faltas {
  struct no_aluno *inicio;
  int cont;
  struct no_aluno *fim;
};

struct data {
  int dia;
  int mes;
  int ano;
};

struct aula_ministrada {
  struct data data;
  char conteudo_ministrado[50];
  struct lista_alunos_faltas faltas_alunos;
};

typedef struct aula_ministrada aula_ministrada;

struct no_aula_ministrada {
  aula_ministrada *aula_ministrada;
  struct no_aula_ministrada *proximo;
};

struct lista_aulas_turma {
  struct no_aula_ministrada *inicio;
  int cont;
  struct no_aula_ministrada *fim;
};

struct turma {
  int id;
  char codigo[10];
  struct lista_professores_turma professores;
  struct lista_alunos_turma alunos;
  struct lista_avaliacoes_turma avaliacoes;
  struct lista_aulas_turma aulas;
  char disciplina[10];
};

typedef struct turma turma;

struct no_turma {
  turma *turma;
  struct no_turma *proximo;
};

struct lista_turmas {
  struct no_turma *inicio;
  int cont;
  struct no_turma *fim;
};

void inicializa_lista_alunos(struct lista_alunos *lista) {
  lista->inicio=NULL;
  lista->cont=0;
  lista->fim=NULL;
}

void inicializa_lista_cursos(struct lista_cursos *lista) {
  lista->inicio=NULL;
  lista->cont=0;
  lista->fim=NULL;
}

void inicializa_lista_alunos_faltas(struct lista_alunos_faltas *lista) {
  lista->inicio=NULL;
  lista->cont=0;
  lista->fim=NULL;
}

void inicializa_lista_alunos_turma(struct lista_alunos_turma *lista) {
  lista->inicio=NULL;
  lista->cont=0;
  lista->fim=NULL;
}

void inicializa_lista_professores(struct lista_professores *lista) {
  lista->inicio=NULL;
  lista->cont=0;
  lista->fim=NULL;
}

void inicializa_lista_professores_turma(struct lista_professores_turma *lista) {
  lista->inicio=NULL;
  lista->cont=0;
  lista->fim=NULL;
}

void inicializa_lista_disciplinas(struct lista_disciplinas *lista) {
  lista->inicio=NULL;
  lista->cont=0;
  lista->fim=NULL;
}

void inicializa_lista_avaliacoes_turma(struct lista_avaliacoes_turma *lista) {
  lista->inicio=NULL;
  lista->cont=0;
  lista->fim=NULL;
}

void inicializa_lista_aulas_turma(struct lista_aulas_turma *lista) {
  lista->inicio=NULL;
  lista->cont=0;
  lista->fim=NULL;
}

void inicializa_lista_turmas(struct lista_turmas *lista) {
  lista->inicio=NULL;
  lista->cont=0;
  lista->fim=NULL;
}

void imprime_lista_alunos(struct lista_alunos *lista) 
{
  struct no_aluno *aux = lista->inicio;
  printf("MATRICULA | NOME | CURSO\n");
  while(aux!=NULL) {
    printf("%ld | ",aux->aluno->matricula);
    printf("%s | ",aux->aluno->nome);
    printf("%s\n",aux->aluno->curso);
    aux = aux->proximo;
  }
}

void imprime_lista_alunos_turma(struct lista_alunos_turma *lista) 
{
  struct no_aluno *aux = lista->inicio;
  printf("NOME | MATRICULA | CURSO\n");
  while(aux!=NULL) {
    printf("%s | ",aux->aluno->nome);
    printf("%ld | ",aux->aluno->matricula);
    printf("%s\n",aux->aluno->curso);
    aux = aux->proximo;
  }
}

void insere_lista_alunos_nula(struct lista_alunos *lista, aluno *aluno) {
  lista->inicio = malloc(sizeof(struct no_aluno));
  lista->inicio->aluno = aluno;
  lista->inicio->proximo = NULL;
  lista->cont = 1;
  lista->fim = lista->inicio;
}

void insere_lista_alunos_fim(struct lista_alunos *lista, aluno *aluno) {
  if (lista->inicio == NULL) {
    insere_lista_alunos_nula(lista,aluno);
  } else {
    lista->fim->proximo = malloc(sizeof(struct no_aluno));
    lista->fim->proximo->aluno = aluno;
    lista->fim->proximo->proximo = NULL;
    lista->fim = lista->fim->proximo;
    lista->cont++;
  }
}

void insere_lista_alunos_turma_nula(struct lista_alunos_turma *lista, aluno *aluno) {
  lista->inicio = malloc(sizeof(struct no_aluno));
  lista->inicio->aluno = aluno;
  lista->inicio->proximo = NULL;
  lista->cont = 1;
  lista->fim = lista->inicio;
}

void insere_lista_alunos_turma_fim(struct lista_alunos_turma *lista, aluno *aluno) {
  if (lista->inicio == NULL) {
    insere_lista_alunos_turma_nula(lista,aluno);
  } else {
    lista->fim->proximo = malloc(sizeof(struct no_aluno));
    lista->fim->proximo->aluno = aluno;
    lista->fim->proximo->proximo = NULL;
    lista->fim = lista->fim->proximo;
    lista->cont++;
  }
}

void insere_lista_avaliacoes_turma_nula(struct lista_avaliacoes_turma *lista, avaliacao *avaliacao) {
  lista->inicio = malloc(sizeof(struct no_avaliacao));
  lista->inicio->avaliacao = avaliacao;
  lista->inicio->proximo = NULL;
  lista->cont = 1;
  lista->fim = lista->inicio;
}

void insere_lista_avaliacoes_turma_fim(struct lista_avaliacoes_turma *lista, avaliacao *avaliacao) {
  if (lista->inicio == NULL) {
    insere_lista_avaliacoes_turma_nula(lista,avaliacao);
  } else {
    lista->fim->proximo = malloc(sizeof(struct no_avaliacao));
    lista->fim->proximo->avaliacao = avaliacao;
    lista->fim->proximo->proximo = NULL;
    lista->fim = lista->fim->proximo;
    lista->cont++;
  }
}

void insere_lista_alunos_faltas_aula_nula(struct lista_alunos_faltas *lista, aluno *aluno) {
  lista->inicio = malloc(sizeof(struct no_aluno));
  lista->inicio->aluno = aluno;
  lista->inicio->proximo = NULL;
  lista->cont = 1;
  lista->fim = lista->inicio;
}

void insere_lista_alunos_faltas_aula_fim(struct lista_alunos_faltas *lista, aluno *aluno) {
  if (lista->inicio == NULL) {
    insere_lista_alunos_faltas_aula_nula(lista,aluno);
  } else {
    lista->fim->proximo = malloc(sizeof(struct no_aluno));
    lista->fim->proximo->aluno = aluno;
    lista->fim->proximo->proximo = NULL;
    lista->fim = lista->fim->proximo;
    lista->cont++;
  }
}

void insere_lista_aulas_turma_nula(struct lista_aulas_turma *lista, struct aula_ministrada *aula_ministrada) {
  lista->inicio = malloc(sizeof(struct no_aula_ministrada));
  lista->inicio->aula_ministrada = aula_ministrada;
  lista->inicio->proximo = NULL;
  lista->cont = 1;
  lista->fim = lista->inicio;
}

void insere_lista_aulas_turma_fim(struct lista_aulas_turma *lista, struct aula_ministrada *aula_ministrada) {
  if (lista->inicio == NULL) {
    insere_lista_aulas_turma_nula(lista,aula_ministrada);
  } else {
    lista->fim->proximo = malloc(sizeof(struct no_aula_ministrada));
    lista->fim->proximo->aula_ministrada = aula_ministrada;
    lista->fim->proximo->proximo = NULL;
    lista->fim = lista->fim->proximo;
    lista->cont++;
  }
}

void insere_lista_professores_turma_nula(struct lista_professores_turma *lista, professor *professor) {
  lista->inicio = malloc(sizeof(struct no_professor));
  lista->inicio->professor = professor;
  lista->inicio->proximo = NULL;
  lista->cont = 1;
  lista->fim = lista->inicio;
}

void insere_lista_professores_turma_fim(struct lista_professores_turma *lista, professor *professor) {
  if (lista->inicio == NULL) {
    insere_lista_professores_turma_nula(lista,professor);
  } else {
    lista->fim->proximo = malloc(sizeof(struct no_professor));
    lista->fim->proximo->professor = professor;
    lista->fim->proximo->proximo = NULL;
    lista->fim = lista->fim->proximo;
    lista->cont++;
  }
}

void imprime_lista_cursos(struct lista_cursos *lista) 
{
  struct no_curso *aux = lista->inicio;
  while(aux!=NULL) {
    printf("%s\n",aux->curso->nome);
    aux = aux->proximo;
  }
}

void insere_lista_cursos_nula(struct lista_cursos *lista, curso *curso) {
  lista->inicio = malloc(sizeof(struct no_curso));
  lista->inicio->curso = curso;
  lista->inicio->proximo = NULL;
  lista->cont = 1;
  lista->fim = lista->inicio;
}

void insere_lista_cursos_fim(struct lista_cursos *lista, curso *curso) {
  if (lista->inicio == NULL) {
    insere_lista_cursos_nula(lista,curso);
  } else {
    lista->fim->proximo = malloc(sizeof(struct no_curso));
    lista->fim->proximo->curso = curso;
    lista->fim->proximo->proximo = NULL;
    lista->fim = lista->fim->proximo;
    lista->cont++;
  }
}

void imprime_lista_professores(struct lista_professores *lista) 
{
  struct no_professor *aux = lista->inicio;
  printf("SIAPE | NOME | AREA DE ATUACAO | TITULACAO\n");
  while(aux!=NULL) {
    printf("%ld | ",aux->professor->siape);
    printf("%s | ",aux->professor->nome);
    printf("%s | ",aux->professor->area_atuacao);
    printf("%s\n",aux->professor->titulacao);
    aux = aux->proximo;
  }
}

void imprime_lista_professores_turma(struct lista_professores_turma *lista) 
{
  struct no_professor *aux = lista->inicio;
  printf("SIAPE | NOME | AREA DE ATUACAO | TITULACAO\n");
  while(aux!=NULL) {
    printf("%ld | ",aux->professor->siape);
    printf("%s | ",aux->professor->nome);
    printf("%s | ",aux->professor->area_atuacao);
    printf("%s\n",aux->professor->titulacao);
    aux = aux->proximo;
  }
}

void insere_lista_professores_nula(struct lista_professores *lista, professor *professor) {
  lista->inicio = malloc(sizeof(struct no_professor));
  lista->inicio->professor = professor;
  lista->inicio->proximo = NULL;
  lista->cont = 1;
  lista->fim = lista->inicio;
}

void insere_lista_professores_fim(struct lista_professores *lista, professor *professor) {
  if (lista->inicio == NULL) {
    insere_lista_professores_nula(lista,professor);
  } else {
    lista->fim->proximo = malloc(sizeof(struct no_professor));
    lista->fim->proximo->professor = professor;
    lista->fim->proximo->proximo = NULL;
    lista->fim = lista->fim->proximo;
    lista->cont++;
  }
}

void imprime_lista_disciplinas(struct lista_disciplinas *lista) 
{
  struct no_disciplina *aux = lista->inicio;
  printf("CODIGO | NOME | CURSO | CARGA HORARIA | PRE-REQUISITOS\n");
  while(aux!=NULL) {
    printf("%s | ",aux->disciplina->codigo);
    printf("%s | ",aux->disciplina->nome);
    printf("%s | ",aux->disciplina->curso);
    printf("%d | ",aux->disciplina->carga_horaria);
    printf("%s\n",aux->disciplina->pre_requisitos);
    aux = aux->proximo;
  }
}

void insere_lista_disciplinas_nula(struct lista_disciplinas *lista, disciplina *disciplina) {
  lista->inicio = malloc(sizeof(struct no_disciplina));
  lista->inicio->disciplina = disciplina;
  lista->inicio->proximo = NULL;
  lista->cont = 1;
  lista->fim = lista->inicio;
}

void insere_lista_disciplinas_fim(struct lista_disciplinas *lista, disciplina *disciplina) {
  if (lista->inicio == NULL) {
    insere_lista_disciplinas_nula(lista,disciplina);
  } else {
    lista->fim->proximo = malloc(sizeof(struct no_disciplina));
    lista->fim->proximo->disciplina = disciplina;
    lista->fim->proximo->proximo = NULL;
    lista->fim = lista->fim->proximo;
    lista->cont++;
  }
}

void imprime_lista_turmas(struct lista_turmas *lista) 
{
  struct no_turma *aux = lista->inicio;
  printf("ID | CODIGO | DISCIPLINA\n");
  while(aux!=NULL) {
    printf("%d | ",aux->turma->id);
    printf("%s | ",aux->turma->codigo);
    printf("%s\n",aux->turma->disciplina);
    // printf("LISTA DE ALUNOS DA TURMA:\n");
    // imprime_lista_alunos_turma(&(aux->turma->alunos));
    // printf("LISTA DE PROFESSORES DA TURMA:\n");
    // imprime_lista_professores_turma(&(aux->turma->professores));
    aux = aux->proximo;
  }
}

void insere_lista_turmas_nula(struct lista_turmas *lista, turma *turma) {
  turma->id = 1;
  lista->inicio = malloc(sizeof(struct no_turma));
  lista->inicio->turma = turma;
  lista->inicio->proximo = NULL;
  lista->cont = 1;
  lista->fim = lista->inicio;
}

void insere_lista_turmas_fim(struct lista_turmas *lista, turma *turma) {
  if (lista->inicio == NULL) {
    insere_lista_turmas_nula(lista,turma);
  } else {
    turma->id = (lista->cont+1);
    lista->fim->proximo = malloc(sizeof(struct no_turma));
    lista->fim->proximo->turma = turma;
    lista->fim->proximo->proximo = NULL;
    lista->fim = lista->fim->proximo;
    lista->cont++;
  }
}

void imprimir_menu() {
  printf("MENU:\n");
  printf("1 - Alunos\n");
  printf("2 - Professores\n");
  printf("3 - Disciplinas\n");
  printf("4 - Turmas\n");
  printf("5 - Cadastrar cursos\n");
  printf("6 - Avaliacoes\n");
  printf("7 - Matricular alunos em uma turma\n");
  printf("8 - Lancar aulas para uma turma\n");
  printf("9 - Gerar relatorio dos alunos de uma turma\n");
  printf("0 - Sair do programa\n");
}

void imprimir_submenu() {
  printf("SUBMENU:\n");
  printf("1 - Cadastrar\n");
  printf("2 - Excluir\n");
  printf("3 - Buscar\n");
  printf("0 - Voltar ao menu inicial\n");
}

int ler_opcao_menu() {
  int menu = 0;
  printf("Digite sua opcao do menu: \n");
  setbuf(stdin, 0);
  scanf("%d",&menu);
  while(menu<0 || menu>9) {
    setbuf(stdin, 0);
    printf("Digite sua opcao do menu: \n");
    scanf("%d",&menu);
  }
  return menu;
}

int ler_opcao_submenu() {
  int submenu = 0;
  printf("Digite sua opcao do submenu: \n");
  setbuf(stdin, 0);
  scanf("%d",&submenu);
  while(submenu<0 || submenu>3) {
    setbuf(stdin, 0);
    printf("Digite sua opcao do submenu: \n");
    scanf("%d",&submenu);
  }
  return submenu;
}

struct curso *le_curso() {
  char nome[50];
  setbuf(stdin, 0);
  printf("Digite o nome de um curso:\n");
  fgets (nome, 50, stdin);
  char *pos;
  if ((pos=strchr(nome, '\n')) != NULL)
    *pos = '\0';
  while (strlen(nome) == 0) {
    setbuf(stdin, 0);
    printf("Digite o nome de um curso:\n");
    fgets (nome, 50, stdin);
    char *pos;
    if ((pos=strchr(nome, '\n')) != NULL)
      *pos = '\0';
  }
  struct curso *curso;
  curso = malloc(sizeof(struct curso));
  strcpy(curso->nome,nome);
  return curso; 
}

bool curso_inexistente(struct lista_cursos *lista,char *curso) {
  struct no_curso *aux = lista->inicio;
  while(aux!=NULL) {
    if (strcmp(aux->curso->nome,curso) == 0) {
      return false;
    }
    aux = aux->proximo;
  }
  return true;
}

bool disciplina_inexistente(struct lista_disciplinas *lista,char *disciplina) {
  struct no_disciplina *aux = lista->inicio;
  while(aux!=NULL) {
    if (strcmp(aux->disciplina->codigo,disciplina) == 0) {
      return false;
    }
    aux = aux->proximo;
  }
  return true;
}

bool turma_inexistente(struct lista_turmas *lista,int id) {
  struct no_turma *aux = lista->inicio;
  while(aux!=NULL) {
    if (aux->turma->id == id) {
      return false;
    }
    aux = aux->proximo;
  }
  return true;
}

struct turma *busca_turma(struct lista_turmas *lista,int id) {
  struct no_turma *aux = lista->inicio;
  while(aux!=NULL) {
    if (aux->turma->id == id) {
      return aux->turma;
    }
    aux = aux->proximo;
  }
  return NULL;
}

bool professor_inexistente(struct lista_professores *lista,long int siape) {
  struct no_professor *aux = lista->inicio;
  while(aux!=NULL) {
    if (aux->professor->siape == siape) {
      return false;
    }
    aux = aux->proximo;
  }
  return true;
}

bool aluno_inexistente(struct lista_alunos *lista,long int matricula) {
  struct no_aluno *aux = lista->inicio;
  while(aux!=NULL) {
    if (aux->aluno->matricula == matricula) {
      return false;
    }
    aux = aux->proximo;
  }
  return true;
}

void retira_barra_n(char *string) {
  char *pos;
  if ((pos=strchr(string, '\n')) != NULL) {
    *pos = '\0';
  }
}

struct aluno *le_aluno(struct lista_cursos *lista_cursos,struct lista_alunos *lista_alunos) {
  setbuf(stdin, 0);
  char nome[50];
  printf("Digite o nome do aluno:\n");
  fgets (nome, 50, stdin);
  retira_barra_n(nome);
  while (strlen(nome) == 0) {
    setbuf(stdin, 0);
    printf("Digite o nome do aluno:\n");
    fgets (nome, 50, stdin);
    retira_barra_n(nome);
  }

  setbuf(stdin, 0);
  long int matricula;
  printf("Digite a matricula do aluno: \n");
  scanf("%ld",&matricula);
  while (matricula<=0 || !aluno_inexistente(lista_alunos,matricula)) {
    setbuf(stdin, 0);
    printf("Digite a matricula do aluno: \n");
    scanf("%ld",&matricula);
  }

  setbuf(stdin, 0);
  printf("Cursos disponiveis para o aluno:\n");
  imprime_lista_cursos(lista_cursos);
  char curso[50];
  printf("Digite o nome de um curso para o aluno:\n");
  fgets (curso, 50, stdin);
  retira_barra_n(curso);
  while (strlen(curso) == 0 || curso_inexistente(lista_cursos,curso)) {
    setbuf(stdin, 0);
    printf("Digite o nome de um curso para o aluno:\n");
    fgets (curso, 50, stdin);
    retira_barra_n(curso);
  }

  struct aluno *aluno;
  aluno = malloc(sizeof(struct aluno));
  strcpy(aluno->nome,nome);
  aluno->matricula = matricula;
  strcpy(aluno->curso,curso);
  return aluno;
}

struct professor *le_professor(struct lista_professores *lista_professores) {
  setbuf(stdin, 0);
  long int siape;
  printf("Digite o siape do professor: \n");
  scanf("%ld",&siape);
  while (siape<=0 || !professor_inexistente(lista_professores,siape)) {
    setbuf(stdin, 0);
    printf("Digite o siape do professor: \n");
    scanf("%ld",&siape);
  }

  char nome[50];
  setbuf(stdin, 0);
  printf("Digite o nome do professor: (ate 48 caracteres)\n");
  fgets (nome, 50, stdin);
  retira_barra_n(nome);
  while (strlen(nome) == 0) {
    setbuf(stdin, 0);
    printf("Digite o nome do professor: (ate 48 caracteres)\n");
    fgets (nome, 50, stdin);
    retira_barra_n(nome);
  }

  char area_atuacao[30];
  setbuf(stdin, 0);
  printf("Digite a area de atuacao do professor: (ate 28 caracteres)\n");
  fgets (area_atuacao, 30, stdin);
  retira_barra_n(area_atuacao);
  while (strlen(area_atuacao) == 0) {
    setbuf(stdin, 0);
    printf("Digite a area de atuacao do professor: (ate 28 caracteres)\n");
    fgets (area_atuacao, 30, stdin);
    retira_barra_n(area_atuacao);
  }

  char titulacao[50];
  setbuf(stdin, 0);
  printf("Digite a titulacao do professor: (ate 48 caracteres)\n");
  fgets (titulacao, 50, stdin);
  retira_barra_n(titulacao);
  while (strlen(titulacao) == 0) {
    setbuf(stdin, 0);
    printf("Digite a titulacao do professor: (ate 48 caracteres)\n");
    fgets (titulacao, 50, stdin);
    retira_barra_n(titulacao);
  }

  struct professor *professor;
  professor = malloc(sizeof(struct professor));
  strcpy(professor->nome,nome);
  professor->siape = siape;
  strcpy(professor->area_atuacao,area_atuacao);
  strcpy(professor->titulacao,titulacao);
  return professor;
}

struct disciplina *le_disciplina(struct lista_cursos *lista_cursos,struct lista_disciplinas *lista_disciplinas) {
  char codigo[10];
  setbuf(stdin, 0);
  printf("Digite o codigo da disciplina: (ate 8 caracteres)\n");
  fgets (codigo, 10, stdin);
  retira_barra_n(codigo);
  while (strlen(codigo) == 0 || !disciplina_inexistente(lista_disciplinas,codigo)) {
    setbuf(stdin, 0);
    printf("Digite o codigo da disciplina: (ate 8 caracteres)\n");
    fgets (codigo, 10, stdin);
    retira_barra_n(codigo);
  }

  setbuf(stdin, 0);
  printf("Cursos disponiveis:\n");
  imprime_lista_cursos(lista_cursos);
  char curso[50];
  printf("Digite o nome de um curso para a disciplina:\n");
  fgets (curso, 50, stdin);
  retira_barra_n(curso);
  while (strlen(curso) == 0 || curso_inexistente(lista_cursos,curso)) {
    setbuf(stdin, 0);
    printf("Digite o nome de um curso para a disciplina:\n");
    fgets (curso, 50, stdin);
    retira_barra_n(curso);
  }

  char nome[30];
  setbuf(stdin, 0);
  printf("Digite o nome da disciplina: (ate 28 caracteres)\n");
  fgets (nome, 30, stdin);
  retira_barra_n(nome);
  while (strlen(nome) == 0) {
    setbuf(stdin, 0);
    printf("Digite o nome da disciplina: (ate 28 caracteres)\n");
    fgets (nome, 30, stdin);
    retira_barra_n(nome);
  }

  setbuf(stdin, 0);
  int carga_horaria;
  printf("Digite a carga horaria da disciplina em h: \n");
  scanf("%d",&carga_horaria);
  while (carga_horaria<=0) {
    setbuf(stdin, 0);
    printf("Digite a carga horaria da disciplina em h: \n");
    scanf("%d",&carga_horaria);
  }

  char pre_requisitos[100];
  setbuf(stdin, 0);
  printf("Digite os pre-requisitos da disciplina: (ate 98 caracteres)\n");
  fgets (pre_requisitos, 100, stdin);
  retira_barra_n(pre_requisitos);
  while (strlen(pre_requisitos) == 0) {
    setbuf(stdin, 0);
    printf("Digite os pre-requisitos da disciplina: (ate 98 caracteres)\n");
    fgets (pre_requisitos, 100, stdin);
    retira_barra_n(pre_requisitos);
  }

  struct disciplina *disciplina;
  disciplina = malloc(sizeof(struct disciplina));
  strcpy(disciplina->codigo,codigo);
  strcpy(disciplina->curso,curso);
  strcpy(disciplina->nome,nome);
  disciplina->carga_horaria = carga_horaria;
  strcpy(disciplina->pre_requisitos,pre_requisitos);

  return disciplina;
}

bool aluno_esta_na_turma(struct lista_alunos_turma *lista,long int matricula) {
  struct no_aluno *aux = lista->inicio;
  while(aux!=NULL) {
    if (aux->aluno->matricula == matricula) {
      return true;
    }
    aux = aux->proximo;
  }
  return false;
}

bool professor_esta_na_turma(struct lista_professores_turma *lista,long int siape) {
  struct no_professor *aux = lista->inicio;
  while(aux!=NULL) {
    if (aux->professor->siape == siape) {
      return true;
    }
    aux = aux->proximo;
  }
  return false;
}

struct aluno *busca_aluno(struct lista_alunos *lista,long int matricula) {
  struct no_aluno *aux = lista->inicio;
  while(aux!=NULL) {
    if (aux->aluno->matricula == matricula) {
      return aux->aluno;
    }
    aux = aux->proximo;
  }
  return NULL;
}

struct aluno *busca_aluno_lista_alunos_turma(struct lista_alunos_turma *lista,long int matricula) {
  struct no_aluno *aux = lista->inicio;
  while(aux!=NULL) {
    if (aux->aluno->matricula == matricula) {
      return aux->aluno;
    }
    aux = aux->proximo;
  }
  return NULL;
}

struct professor *busca_professor(struct lista_professores *lista,long int siape) {
  struct no_professor *aux = lista->inicio;
  while(aux!=NULL) {
    if (aux->professor->siape == siape) {
      return aux->professor;
    }
    aux = aux->proximo;
  }
  return NULL;
}

bool aluno_tem_avaliacao(struct lista_avaliacoes_turma *lista,long int matricula) {
  struct no_avaliacao *aux = lista->inicio;
  while(aux!=NULL) {
    if (aux->avaliacao->matricula == matricula) {
      return true;
    }
    aux = aux->proximo;
  }
  return false;
}

struct avaliacao *busca_avaliacao_lista_avaliacoes_turma(struct lista_avaliacoes_turma *lista,long int matricula) {
  struct no_avaliacao *aux = lista->inicio;
  while(aux!=NULL) {
    if (aux->avaliacao->matricula == matricula) {
      return aux->avaliacao;
    }
    aux = aux->proximo;
  }
  return NULL;
}

void imprime_lista_avaliacoes_turma(struct lista_avaliacoes_turma *lista) {
  struct no_avaliacao *aux = lista->inicio;
  printf("MATRICULA | NOTA 1 | NOTA 2 | MEDIA\n");
  while(aux!=NULL) {
    printf("%ld | ",aux->avaliacao->matricula);
    printf("%.2f | ",aux->avaliacao->nota1);
    printf("%.2f | ",aux->avaliacao->nota2);
    printf("%.2f\n",(aux->avaliacao->nota1+aux->avaliacao->nota2)/2.0);
    aux = aux->proximo;
  }
}

struct turma *le_turma(struct lista_alunos *lista_alunos,struct lista_professores *lista_professores,
                       struct lista_disciplinas *lista_disciplinas) {

  struct lista_alunos_turma *lista_alunos_turma;
  lista_alunos_turma = malloc(sizeof(struct lista_alunos_turma));
  inicializa_lista_alunos_turma(lista_alunos_turma);

  struct lista_professores_turma *lista_professores_turma;
  lista_professores_turma = malloc(sizeof(struct lista_professores_turma));
  inicializa_lista_professores_turma(lista_professores_turma);

  struct lista_avaliacoes_turma *lista_avaliacoes_turma;
  lista_avaliacoes_turma = malloc(sizeof(struct lista_avaliacoes_turma));
  inicializa_lista_avaliacoes_turma(lista_avaliacoes_turma);

  struct lista_aulas_turma *lista_aulas_turma;
  lista_aulas_turma = malloc(sizeof(struct lista_aulas_turma));
  inicializa_lista_aulas_turma(lista_aulas_turma);

  char codigo[10];
  setbuf(stdin, 0);
  printf("Digite o codigo da turma: (ate 8 caracteres)\n");
  fgets (codigo, 10, stdin);
  retira_barra_n(codigo);
  while (strlen(codigo) == 0) {
    setbuf(stdin, 0);
    printf("Digite o codigo da turma: (ate 8 caracteres)\n");
    fgets (codigo, 10, stdin);
    retira_barra_n(codigo);
  }

  char disciplina[10];
  setbuf(stdin, 0);
  printf("Disciplinas disponiveis para a turma:\n");
  imprime_lista_disciplinas(lista_disciplinas);
  printf("Digite o codigo da disciplina da turma: (ate 8 caracteres)\n");
  fgets (disciplina, 10, stdin);
  retira_barra_n(disciplina);
  while (strlen(disciplina) == 0 || disciplina_inexistente(lista_disciplinas,disciplina)) {
    setbuf(stdin, 0);
    printf("Digite o codigo da disciplina da turma: (ate 8 caracteres)\n");
    fgets (disciplina, 10, stdin);
    retira_barra_n(disciplina);
  }
  printf("\n\n");


  setbuf(stdin, 0);
  printf("Professores cadastrados no sistema:\n");
  imprime_lista_professores(lista_professores);
  printf("Informe o SIAPE do professor para adicionar a turma.\n");
  printf("Informe pelo menos 1 professor.\n");
  printf("Digite 0 para deixar de adicionar professores na turma.\n");
  setbuf(stdin, 0);
  long int siape;
  printf("SIAPE: ");
  scanf("%ld",&siape);
  while (siape>0 || lista_professores_turma->cont==0) {
    bool prof_inex = professor_inexistente(lista_professores,siape);
    bool prof_na_turma = professor_esta_na_turma(lista_professores_turma,siape);
    if (!prof_inex && !prof_na_turma) {
      struct professor *professor = busca_professor(lista_professores,siape);
      insere_lista_professores_turma_fim(lista_professores_turma,professor);
      printf("Professor adicionado a turma com sucesso!\n");
    } else {
      if (prof_inex) {
        printf("Professor nao existe.\n");
      } else if (prof_na_turma) {
        printf("Professor ja esta na turma.\n");
      }
    }
    setbuf(stdin, 0);
    printf("\n\n");
    printf("Professores cadastrados no sistema:\n");
    imprime_lista_professores(lista_professores);
    printf("Digite 0 para deixar de adicionar professores na turma.\n");
    printf("Digite o siape do professor: ");
    scanf("%ld",&siape);
  }


  struct turma *turma;
  turma = malloc(sizeof(struct turma));
  strcpy(turma->codigo,codigo);
  strcpy(turma->disciplina,disciplina);
  turma->professores = *lista_professores_turma;
  turma->alunos = *lista_alunos_turma;
  turma->avaliacoes = *lista_avaliacoes_turma;
  turma->aulas = *lista_aulas_turma;
  return turma;
}

void lancar_notas_turma(struct turma *turma) {
  printf("Alunos matriculados na turma:\n");
  imprime_lista_alunos_turma(&(turma->alunos));
  setbuf(stdin, 0);
  long int matricula;
  printf("Digite a matricula do aluno para inserir uma avaliacao.\n");
  printf("Cada avaliacao inserida contem a nota 1 e a nota 2 do aluno.\n");
  printf("Digite 0 para deixar de inserir avaliacoes aos alunos.\n");
  printf("Matricula: ");
  scanf("%ld",&matricula);
  while (matricula>0) {
    bool aluno_na_turma = aluno_esta_na_turma(&(turma->alunos),matricula);
    bool aluno_avaliacao = aluno_tem_avaliacao(&(turma->avaliacoes),matricula);
    if (aluno_na_turma && !aluno_avaliacao) {
      struct aluno *aluno = busca_aluno_lista_alunos_turma(&(turma->alunos),matricula);
      setbuf(stdin, 0);
      float nota1;
      float nota2;
      printf("Digite a nota 1 de %s: ",aluno->nome);
      scanf("%f",&nota1);
      while(nota1<0 || nota1>10) {
        setbuf(stdin, 0);
        printf("Digite a nota 1 de %s: ",aluno->nome);
        scanf("%f",&nota1);
      }
      setbuf(stdin, 0);
      printf("Digite a nota 2 de %s: ",aluno->nome);
      scanf("%f",&nota2);
      while(nota2<0 || nota2>10) {
        setbuf(stdin, 0);
        printf("Digite a nota 2 de %s: ",aluno->nome);
        scanf("%f",&nota2);
      }
      struct avaliacao *avaliacao = malloc(sizeof(struct avaliacao));
      avaliacao->matricula = matricula;
      avaliacao->nota1 = nota1;
      avaliacao->nota2 = nota2;
      insere_lista_avaliacoes_turma_fim(&(turma->avaliacoes),avaliacao);
      printf("Avaliacao do(a) aluno(a) %s inserida com sucesso!\n",aluno->nome);
    } else {
      if (!aluno_na_turma) {
        printf("Aluno(a) nao esta na turma.\n");
      } else if (aluno_avaliacao) {
        printf("Aluno(a) ja tem avaliacao nessa turma.\n");
      }
    }
    printf("\n\n");
    printf("Alunos matriculados na turma:\n");
    imprime_lista_alunos_turma(&(turma->alunos));
    setbuf(stdin, 0);
    printf("Digite a matricula do aluno para inserir uma avaliacao.\n");
    printf("Cada avaliacao inserida contem a nota 1 e a nota 2 do aluno.\n");
    printf("Digite 0 para deixar de inserir avaliacoes aos alunos.\n");
    printf("Matricula: ");
    scanf("%ld",&matricula);
  }
}

void remove_aluno_lista_turmas_avaliacoes(struct lista_avaliacoes_turma *lista,struct aluno *aluno);


void excluir_notas_turma(struct turma *turma) {
  if (turma->avaliacoes.cont == 0) {
    printf("Nao ha avaliacoes para os alunos dessa turma.\n");
    return;
  }
  printf("Alunos(as) matriculados na turma com avaliacoes:\n");
  imprime_lista_avaliacoes_turma(&(turma->avaliacoes));
  setbuf(stdin, 0);
  long int matricula;
  printf("Digite a matricula do aluno para remover sua avaliacao.\n");
  printf("Digite 0 para deixar de excluir avaliacoes dos alunos.\n");
  printf("Matricula: ");
  scanf("%ld",&matricula);
  while (matricula>0) {
    bool aluno_avaliacao = aluno_tem_avaliacao(&(turma->avaliacoes),matricula);
    if (aluno_avaliacao) {
      struct aluno *aluno = busca_aluno_lista_alunos_turma(&(turma->alunos),matricula);
      remove_aluno_lista_turmas_avaliacoes(&(turma->avaliacoes),aluno);
      printf("Avaliacao do aluno %s excluida com sucesso!\n",aluno->nome);
    } else {
      if (!aluno_avaliacao) {
        printf("Aluno nao tem avaliacao nessa turma.\n");
      }
    }
    printf("\n\n");
    if (turma->avaliacoes.cont == 0) {
      printf("Voce excluiu todas as avaliacoes dos alunos.\n");
      break;
    }
    printf("Alunos(as) matriculados na turma com avaliacoes:\n");
    imprime_lista_avaliacoes_turma(&(turma->avaliacoes));
    setbuf(stdin, 0);
    printf("Digite a matricula do aluno para remover sua avaliacao.\n");
    printf("Digite 0 para deixar de excluir avaliacoes dos alunos.\n");
    printf("Matricula: ");
    scanf("%ld",&matricula);
  }
}

void buscar_notas_turma(struct turma *turma) {
  if (turma->avaliacoes.cont == 0) {
    printf("Nao ha avaliacoes para os alunos dessa turma.\n");
    return;
  }
  setbuf(stdin, 0);
  long int matricula;
  printf("Digite a matricula do aluno para buscar sua avaliacao.\n");
  printf("Digite 0 para deixar de buscar avaliacoes dos alunos.\n");
  printf("Matricula: ");
  scanf("%ld",&matricula);
  while (matricula>0) {
    bool aluno_avaliacao = aluno_tem_avaliacao(&(turma->avaliacoes),matricula);
    if (aluno_avaliacao) {
      struct aluno *aluno = busca_aluno_lista_alunos_turma(&(turma->alunos),matricula);
      struct avaliacao *avaliacao = busca_avaliacao_lista_avaliacoes_turma(&(turma->avaliacoes),matricula);
      printf("ALUNO(A) | NOTA 1 | NOTA 2 | MEDIA\n");
      printf("%s | ",aluno->nome);
      printf("%.2f | ",avaliacao->nota1);
      printf("%.2f | ",avaliacao->nota2);
      printf("%.2f\n",(avaliacao->nota1+avaliacao->nota2)/2.0);
    } else {
      if (!aluno_avaliacao) {
        printf("Aluno nao tem avaliacao nessa turma.\n");
      }
    }
    printf("\n\n");
    setbuf(stdin, 0);
    printf("Digite a matricula do aluno para buscar sua avaliacao.\n");
    printf("Digite 0 para deixar de buscar avaliacoes dos alunos.\n");
    printf("Matricula: ");
    scanf("%ld",&matricula);
  }
}

bool data_incorreta(int dia, int mes, int ano) {
  if (dia>31 || dia<1) {
    return true;
  }
  if (mes>12 || mes<1) {
    return true;
  }
  if (ano<2018) {
    return true;
  }
  return false;
}

bool verifica_se_string_existe_em_string(char *string_procurada,char *pesquisa) {
  int i,j,quantidade=0,conta_letras=0,aux_i=0;
  int t_pesquisa,t_palavra;

  t_palavra= strlen(string_procurada); 
  t_pesquisa = strlen(pesquisa);
  
  for (i=0;i<t_pesquisa;i++) {
    if (string_procurada[0]==pesquisa[i]) {
      aux_i=i;
      conta_letras=0;
      for(j=0;j<t_palavra;j++) {
        if(string_procurada[j]==pesquisa[aux_i]) {
          conta_letras++;
        } else {
          break;
        }
        aux_i++;
      }
      if (conta_letras>=t_palavra) {
        return true;
      }
    }
  }
  
  return false;
}

bool aluno_com_falta(struct lista_alunos_faltas *lista,long int matricula) {
  struct no_aluno *aux = lista->inicio;
  while(aux!=NULL) {
    if (aux->aluno->matricula == matricula) {
      return true;
    }
  }
  return false;
}

struct disciplina *busca_disciplina(struct lista_disciplinas *lista,char *codigo);

void lancar_aulas_turma(struct turma *turma, struct lista_disciplinas *lista_disciplinas) {
  if (turma->alunos.cont == 0) {
    printf("A turma escolhida nao tem alunos matriculados. Por favor, matricule alguns alunos.\n");
    return;
  } else if (turma->professores.cont == 0) {
    printf("A turma escolhida nao tem professores.\n");
    return;
  }

  struct disciplina *disciplina = busca_disciplina(lista_disciplinas,turma->disciplina);
  if (disciplina->carga_horaria == turma->aulas.cont) {
    printf("Voce ja inseriu o numero maximo de aulas para essa disciplina.\n");
    return;
  }


  int dia;
  int mes;
  int ano;
  setbuf(stdin, 0);
  printf("Inserindo aula para a turma de codigo %s da disciplina %s.\n",turma->codigo,turma->disciplina);
  printf("Cada aula ministrada inserida na turma tem a carga horaria de 1h.\n");
  printf("Digite a data da aula no formato dd/mm/aaaa: \n");
  scanf("%d/%d/%d",&dia,&mes,&ano);
  while (data_incorreta(dia,mes,ano)) {
    setbuf(stdin, 0);
    printf("Digite a data da aula no formato dd/mm/aaaa: \n");
    scanf("%d/%d/%d",&dia,&mes,&ano);
  }
  struct data *data = malloc(sizeof(struct data));
  data->dia = dia;
  data->mes = mes;
  data->ano = ano;


  char conteudo_ministrado[50];
  setbuf(stdin, 0);
  printf("Digite o conteudo ministrado da aula: (ate 48 caracteres)\n");
  fgets (conteudo_ministrado, 50, stdin);
  retira_barra_n(conteudo_ministrado);
  while (strlen(conteudo_ministrado) == 0) {
    setbuf(stdin, 0);
    printf("Digite o conteudo ministrado da aula: (ate 48 caracteres)\n");
    fgets (conteudo_ministrado, 50, stdin);
    retira_barra_n(conteudo_ministrado);
  }

  struct lista_alunos_faltas *faltas_alunos = malloc(sizeof(struct lista_alunos_faltas));
  inicializa_lista_alunos_faltas(faltas_alunos);
  printf("Alunos(as) matriculados na turma:\n");
  imprime_lista_alunos_turma(&(turma->alunos));
  setbuf(stdin, 0);
  long int matricula;
  printf("Digite a matricula do aluno para marcar falta a ele nessa aula.\n");
  printf("Digite 0 para deixar de marcar faltas aos alunos.\n");
  printf("Matricula: ");
  scanf("%ld",&matricula);
  while (matricula>0) {
    bool aluno_na_turma = aluno_esta_na_turma(&(turma->alunos),matricula);
    bool aluno_falta = aluno_com_falta(faltas_alunos,matricula);
    if (aluno_na_turma && !aluno_falta) {
      struct aluno *aluno = busca_aluno_lista_alunos_turma(&(turma->alunos),matricula);
      insere_lista_alunos_faltas_aula_fim(faltas_alunos,aluno);
      printf("Falta marcada ao aluno %s.\n",aluno->nome);
    } else {
      if (!aluno_na_turma) {
        printf("Aluno nao esta na turma.\n");
      } else if (aluno_falta) {
        printf("Aluno ja tem falta nessa aula.\n");
      }
    }
    printf("\n\n");
    printf("Alunos(as) matriculados na turma:\n");
    imprime_lista_alunos_turma(&(turma->alunos));
    setbuf(stdin, 0);
    printf("Digite a matricula do aluno para marcar falta a ele nessa aula.\n");
    printf("Digite 0 para deixar de marcar faltas aos alunos.\n");
    printf("Matricula: ");
    scanf("%ld",&matricula);
  }

  struct aula_ministrada *aula_ministrada = malloc(sizeof(struct aula_ministrada));
  aula_ministrada->data = *data;
  strcpy(aula_ministrada->conteudo_ministrado,conteudo_ministrado);
  aula_ministrada->faltas_alunos = *faltas_alunos;
  insere_lista_aulas_turma_fim(&(turma->aulas),aula_ministrada);

  setbuf(stdin, 0);
  int inserir_mais = 0;
  printf("Voce deseja inserir mais aulas para a turma de codigo %s? (digite 1 para sim ou 0 para não) ",turma->codigo);
  scanf("%d",&inserir_mais);
  while(inserir_mais<0 || inserir_mais>1) {
    setbuf(stdin, 0);
    printf("Voce deseja inserir mais aulas para a turma de codigo %s? (digite 1 para sim ou 0 para não) ",turma->codigo);
    scanf("%d",&inserir_mais);
  }
  if (inserir_mais == 1) {
    lancar_aulas_turma(turma,lista_disciplinas);
  } else {
    return;
  }
}

bool aluno_tem_falta_na_aula(struct lista_alunos_faltas *lista_alunos_faltas,long int matricula) {
  struct no_aluno *aux = lista_alunos_faltas->inicio;
  while(aux!=NULL) {
    if (aux->aluno->matricula == matricula) {
      return true;
    }
    aux = aux->proximo;
  }
  return false;
}

int calcula_quantidade_minima_carga_disciplina(struct disciplina *disciplina) {
  double qntd = (75.0*disciplina->carga_horaria)/100.0;
  double result = ceil(qntd);
  return (int) result;
}

bool aluno_rodou_falta(struct lista_aulas_turma *lista_aulas_turma,struct disciplina *disciplina,struct aluno *aluno) {
  struct no_aula_ministrada *aux = lista_aulas_turma->inicio;
  int faltas = 0;
  while(aux!=NULL) {
    if (aluno_tem_falta_na_aula(&(aux->aula_ministrada->faltas_alunos),aluno->matricula)) {
      faltas++;
    }
    aux = aux->proximo;
  }
  int qnd_minima = calcula_quantidade_minima_carga_disciplina(disciplina);
  if (faltas > (disciplina->carga_horaria-qnd_minima)) {
    return true;
  }
  return false;
}

void gerar_relatorio(struct turma *turma,struct lista_disciplinas *lista_disciplinas) {
  if (turma->alunos.cont == 0) {
    printf("Nao ha alunos nessa turma.\n");
    return;
  }
  struct no_aluno *aux = turma->alunos.inicio;
  struct disciplina *disciplina = busca_disciplina(lista_disciplinas,turma->disciplina);
  while(aux!=NULL) {
    if (aluno_rodou_falta(&(turma->aulas),disciplina,aux->aluno)) {
      printf("%ld %s FOI REPROVADO POR FREQUENCIA NA DISCIPLINA.\n",aux->aluno->matricula,aux->aluno->nome);
    }
    aux = aux->proximo;
  }

  if (turma->avaliacoes.cont == 0) {
    printf("Nao ha avaliacoes nessa turma.\n");
    return;
  }
  aux = turma->alunos.inicio;
  printf("MATRICULA | NOME | NOTA 1 | NOTA 2 | MEDIA | SITUACAO\n");
  while(aux!=NULL) {
    if (aluno_tem_avaliacao(&(turma->avaliacoes),aux->aluno->matricula)) {
      struct avaliacao *avaliacao = busca_avaliacao_lista_avaliacoes_turma(&(turma->avaliacoes),aux->aluno->matricula);
      printf("%ld | ",aux->aluno->matricula);
      printf("%s | ",aux->aluno->nome);
      printf("%.2f | ",avaliacao->nota1);
      printf("%.2f | ",avaliacao->nota2);
      float media = (avaliacao->nota1+avaliacao->nota2)/2.0;
      printf("%.2f | ",media);
      if (media>=7.0) {
        printf("APROVADO\n");
      } else {
        printf("REPROVADO\n");
      }
    }
    aux = aux->proximo;
  }

  aux = turma->alunos.inicio;
  while(aux!=NULL) {
    if (!aluno_tem_avaliacao(&(turma->avaliacoes),aux->aluno->matricula) && !aluno_rodou_falta(&(turma->aulas),disciplina,aux->aluno)) {
      printf("%ld %s NAO TEM AVALIACAO NESSA TURMA.\n",aux->aluno->matricula,aux->aluno->nome);
    }
    aux = aux->proximo;
  }
}

int remove_aluno_lista_turmas_alunos_primeiro(struct lista_alunos_turma *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_aluno *segundo = lista->inicio->proximo;
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_aluno_lista_turmas_alunos_ultimo(struct lista_alunos_turma *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_aluno *penultimo = lista->inicio;
      struct no_aluno *ultimo = lista->fim;
      while (penultimo->proximo->proximo != NULL) {
        penultimo = penultimo->proximo;
      }
      penultimo->proximo = NULL;
      lista->fim = penultimo;
      free(ultimo);
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_aluno_lista_turmas_alunos_indice(struct lista_alunos_turma *lista,int indice) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (indice>=lista->cont || indice<0) {
      printf("A lista nao possui valor nesse indice\n");
      return -1;
    } else {
      if (indice==0) {
        return remove_aluno_lista_turmas_alunos_primeiro(lista);
      } else if (indice==lista->cont-1) {
        return remove_aluno_lista_turmas_alunos_ultimo(lista);
      }
      struct no_aluno *valor = lista->inicio;
      int cont=1;
      while(cont<indice){
        valor = valor->proximo;
        cont++;
      }
      struct no_aluno *proximo = valor->proximo->proximo;
      free(valor->proximo);
      valor->proximo = proximo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

bool remove_aluno_lista_turmas_alunos(struct lista_alunos_turma *lista,struct aluno *aluno) {
  struct no_aluno *aux = lista->inicio;
  int indice = 0;
  while(aux!=NULL) {
    if (aux->aluno == aluno) {
      remove_aluno_lista_turmas_alunos_indice(lista,indice);
      return true;
    }
    indice++;
    aux = aux->proximo;
  }
  return false;
}

int remove_aluno_lista_turmas_avaliacoes_primeiro(struct lista_avaliacoes_turma *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio->avaliacao);
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_avaliacao *segundo = lista->inicio->proximo;
      free(lista->inicio->avaliacao);
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_aluno_lista_turmas_avaliacoes_ultimo(struct lista_avaliacoes_turma *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio->avaliacao);
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_avaliacao *penultimo = lista->inicio;
      struct no_avaliacao *ultimo = lista->fim;
      while (penultimo->proximo->proximo != NULL) {
        penultimo = penultimo->proximo;
      }
      penultimo->proximo = NULL;
      lista->fim = penultimo;
      free(ultimo->avaliacao);
      free(ultimo);
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_aluno_lista_turmas_avaliacoes_indice(struct lista_avaliacoes_turma *lista,int indice) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (indice>=lista->cont || indice<0) {
      printf("A lista nao possui valor nesse indice\n");
      return -1;
    } else {
      if (indice==0) {
        return remove_aluno_lista_turmas_avaliacoes_primeiro(lista);
      } else if (indice==lista->cont-1) {
        return remove_aluno_lista_turmas_avaliacoes_ultimo(lista);
      }
      struct no_avaliacao *valor = lista->inicio;
      int cont=1;
      while(cont<indice){
        valor = valor->proximo;
        cont++;
      }
      struct no_avaliacao *proximo = valor->proximo->proximo;
      free(valor->proximo->avaliacao);
      free(valor->proximo);
      valor->proximo = proximo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

void remove_aluno_lista_turmas_avaliacoes(struct lista_avaliacoes_turma *lista,struct aluno *aluno) {
  struct no_avaliacao *aux = lista->inicio;
  int indice = 0;
  while(aux!=NULL) {
    if (aux->avaliacao->matricula == aluno->matricula) {
      remove_aluno_lista_turmas_avaliacoes_indice(lista,indice);
      return;
    }
    indice++;
    aux = aux->proximo;
  }
}

int remove_aluno_lista_turmas_aulas_faltas_primeiro(struct lista_alunos_faltas *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_aluno *segundo = lista->inicio->proximo;
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_aluno_lista_turmas_aulas_faltas_ultimo(struct lista_alunos_faltas *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_aluno *penultimo = lista->inicio;
      struct no_aluno *ultimo = lista->fim;
      while (penultimo->proximo->proximo != NULL) {
        penultimo = penultimo->proximo;
      }
      penultimo->proximo = NULL;
      lista->fim = penultimo;
      free(ultimo);
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_aluno_lista_turmas_aulas_faltas_indice(struct lista_alunos_faltas *lista,int indice) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (indice>=lista->cont || indice<0) {
      printf("A lista nao possui valor nesse indice\n");
      return -1;
    } else {
      if (indice==0) {
        return remove_aluno_lista_turmas_aulas_faltas_primeiro(lista);
      } else if (indice==lista->cont-1) {
        return remove_aluno_lista_turmas_aulas_faltas_ultimo(lista);
      }
      struct no_aluno *valor = lista->inicio;
      int cont=1;
      while(cont<indice){
        valor = valor->proximo;
        cont++;
      }
      struct no_aluno *proximo = valor->proximo->proximo;
      free(valor->proximo);
      valor->proximo = proximo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

void remove_aluno_lista_turmas_aulas_faltas(struct lista_alunos_faltas *lista,struct aluno *aluno) {
  struct no_aluno *aux = lista->inicio;
  int indice = 0;
  while (aux!=NULL) {
    if (aux->aluno == aluno) {
      remove_aluno_lista_turmas_aulas_faltas_indice(lista,indice);
      return;
    }
    indice++;
    aux = aux->proximo;
  }
}

void remove_aluno_lista_turmas_aulas(struct lista_aulas_turma *lista,struct aluno *aluno) {
  struct no_aula_ministrada *aux = lista->inicio;
  while(aux!=NULL) {
    if (aux->aula_ministrada->faltas_alunos.inicio != NULL) {
      remove_aluno_lista_turmas_aulas_faltas(&(aux->aula_ministrada->faltas_alunos),aluno);
    }
    aux = aux->proximo;
  }
}

void remove_aluno_lista_turmas(struct lista_turmas *lista,struct aluno *aluno) {
  struct no_turma *aux = lista->inicio;
  while(aux!=NULL) {
    if (remove_aluno_lista_turmas_alunos(&(aux->turma->alunos),aluno)) {
      remove_aluno_lista_turmas_avaliacoes(&(aux->turma->avaliacoes),aluno);
      remove_aluno_lista_turmas_aulas(&(aux->turma->aulas),aluno);
    }
    aux = aux->proximo;
  }
}

int remove_aluno_lista_alunos_primeiro(struct lista_alunos *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_aluno *segundo = lista->inicio->proximo;
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_aluno_lista_alunos_ultimo(struct lista_alunos *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_aluno *penultimo = lista->inicio;
      struct no_aluno *ultimo = lista->fim;
      while (penultimo->proximo->proximo != NULL) {
        penultimo = penultimo->proximo;
      }
      penultimo->proximo = NULL;
      lista->fim = penultimo;
      free(ultimo);
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_aluno_lista_alunos_primeiro_com_dependencias(struct lista_alunos *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio->aluno);
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_aluno *segundo = lista->inicio->proximo;
      free(lista->inicio->aluno);
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_aluno_lista_alunos_indice(struct lista_alunos *lista,int indice) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (indice>=lista->cont || indice<0) {
      printf("A lista nao possui valor nesse indice\n");
      return -1;
    } else {
      if (indice==0) {
        return remove_aluno_lista_alunos_primeiro(lista);
      } else if (indice==lista->cont-1) {
        return remove_aluno_lista_alunos_ultimo(lista);
      }
      struct no_aluno *valor = lista->inicio;
      int cont=1;
      while(cont<indice){
        valor = valor->proximo;
        cont++;
      }
      struct no_aluno *proximo = valor->proximo->proximo;
      free(valor->proximo);
      valor->proximo = proximo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

void remove_aluno_lista_alunos(struct lista_alunos *lista,struct aluno *aluno) {
  struct no_aluno *aux = lista->inicio;
  int indice = 0;
  while(aux!=NULL) {
    if (aux->aluno == aluno) {
      remove_aluno_lista_alunos_indice(lista,indice);
      return;
    }
    indice++;
    aux = aux->proximo;
  }
}

void remove_aluno(struct lista_alunos *lista_alunos,struct lista_turmas *lista_turmas) {
  // printf("Alunos cadastrados no sistema:\n");
  // imprime_lista_alunos(lista_alunos);
  setbuf(stdin, 0);
  long int matricula;
  printf("Digite a matricula do aluno para exclui-lo completamente do sistema.\n");
  printf("Digite 0 para deixar de excluir alunos.\n");
  printf("Matricula: ");
  scanf("%ld",&matricula);
  while (matricula>0) {
    bool aluno_inex = aluno_inexistente(lista_alunos,matricula);
    if (!aluno_inex) {
      struct aluno *aluno = busca_aluno(lista_alunos,matricula);
      remove_aluno_lista_turmas(lista_turmas,aluno);
      remove_aluno_lista_alunos(lista_alunos,aluno);
      free(aluno);
      printf("Aluno(a) excluido do sistema com sucesso!\n");
    } else {
      if (aluno_inex) {
        printf("Aluno nao existe.\n");
      }
    }
    if (lista_alunos->cont == 0) {
      printf("Voce excluiu todos os alunos do sistema.\n");
      break;
    }
    printf("\n\n");
    // printf("Alunos(as) cadastrados no sistema:\n");
    // imprime_lista_alunos(lista_alunos);
    setbuf(stdin, 0);
    printf("Digite 0 para deixar de excluir alunos(as).\n");
    printf("Digite a matricula do(a) aluno(a): ");
    scanf("%ld",&matricula);
  }
}

void matricular_alunos_turma(struct lista_alunos *lista_alunos,struct turma *turma) {
  if (turma->alunos.cont == 50) {
    printf("A turma tem 50 alunos matriculados.\n");
    return;
  }

  // printf("Alunos cadastrados no sistema:\n");
  // imprime_lista_alunos(lista_alunos);
  setbuf(stdin, 0);
  long int matricula;
  printf("Digite a matricula do aluno para inseri-lo na turma.\n");
  printf("Digite 0 para deixar de matricular alunos.\n");
  printf("Matricula: ");
  scanf("%ld",&matricula);
  while (matricula>0 || turma->alunos.cont==0) {
    bool aluno_inex = aluno_inexistente(lista_alunos,matricula);
    bool aluno_na_turma = aluno_esta_na_turma(&(turma->alunos),matricula);
    if (!aluno_inex && !aluno_na_turma) {
      struct aluno *aluno = busca_aluno(lista_alunos,matricula);
      insere_lista_alunos_turma_fim(&(turma->alunos),aluno);
      printf("Aluno(a) matriculado na turma com sucesso!\n");
      if (turma->alunos.cont==50) {
        printf("A turma atingiu seu limite de alunos.\n");
        break;
      }
    } else {
      if (aluno_inex) {
        printf("Aluno nao existe.\n");
      } else if (aluno_na_turma) {
        printf("Aluno ja esta na turma.\n");
      }
    }
    printf("\n\n");
    // printf("Alunos cadastrados no sistema:\n");
    // imprime_lista_alunos(lista_alunos);
    setbuf(stdin, 0);
    printf("Digite 0 para deixar de matricular alunos.\n");
    printf("Digite a matricula do aluno: ");
    scanf("%ld",&matricula);
  }
}

int remove_professor_lista_professores_primeiro(struct lista_professores *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_professor *segundo = lista->inicio->proximo;
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_professor_lista_professores_ultimo(struct lista_professores *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_professor *penultimo = lista->inicio;
      struct no_professor *ultimo = lista->fim;
      while (penultimo->proximo->proximo != NULL) {
        penultimo = penultimo->proximo;
      }
      penultimo->proximo = NULL;
      lista->fim = penultimo;
      free(ultimo);
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_professor_lista_professores_primeiro_com_dependencias(struct lista_professores *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio->professor);
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_professor *segundo = lista->inicio->proximo;
      free(lista->inicio->professor);
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_professor_lista_professores_indice(struct lista_professores *lista,int indice) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (indice>=lista->cont || indice<0) {
      printf("A lista nao possui valor nesse indice\n");
      return -1;
    } else {
      if (indice==0) {
        return remove_professor_lista_professores_primeiro(lista);
      } else if (indice==lista->cont-1) {
        return remove_professor_lista_professores_ultimo(lista);
      }
      struct no_professor *valor = lista->inicio;
      int cont=1;
      while(cont<indice) {
        valor = valor->proximo;
        cont++;
      }
      struct no_professor *proximo = valor->proximo->proximo;
      free(valor->proximo);
      valor->proximo = proximo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

void remove_professor_lista_professores(struct lista_professores *lista,struct professor *professor) {
  struct no_professor *aux = lista->inicio;
  int indice = 0;
  while(aux!=NULL) {
    if (aux->professor == professor) {
      remove_professor_lista_professores_indice(lista,indice);
      return;
    }
    indice++;
    aux = aux->proximo;
  }
}

int remove_professor_lista_turmas_professores_primeiro(struct lista_professores_turma *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_professor *segundo = lista->inicio->proximo;
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_professor_lista_turmas_professores_ultimo(struct lista_professores_turma *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_professor *penultimo = lista->inicio;
      struct no_professor *ultimo = lista->fim;
      while (penultimo->proximo->proximo != NULL) {
        penultimo = penultimo->proximo;
      }
      penultimo->proximo = NULL;
      lista->fim = penultimo;
      free(ultimo);
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_professor_lista_turmas_professores_indice(struct lista_professores_turma *lista,int indice) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (indice>=lista->cont || indice<0) {
      printf("A lista nao possui valor nesse indice\n");
      return -1;
    } else {
      if (indice==0) {
        return remove_professor_lista_turmas_professores_primeiro(lista);
      } else if (indice==lista->cont-1) {
        return remove_professor_lista_turmas_professores_ultimo(lista);
      }
      struct no_professor *valor = lista->inicio;
      int cont=1;
      while(cont<indice){
        valor = valor->proximo;
        cont++;
      }
      struct no_professor *proximo = valor->proximo->proximo;
      free(valor->proximo);
      valor->proximo = proximo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

bool remove_professor_lista_turmas_professores(struct lista_professores_turma *lista,struct professor *professor) {
  struct no_professor *aux = lista->inicio;
  int indice = 0;
  while(aux!=NULL) {
    if (aux->professor == professor) {
      remove_professor_lista_turmas_professores_indice(lista,indice);
      return true;
    }
    indice++;
    aux = aux->proximo;
  }
  return false;
}

void remove_turma(struct lista_turmas *lista_turmas, struct turma *turma);

void remove_professor_lista_turmas(struct lista_turmas *lista,struct professor *professor) {
  struct no_turma *aux = lista->inicio;
  while(aux!=NULL) {
    if (remove_professor_lista_turmas_professores(&(aux->turma->professores),professor)) {
      if (aux->turma->professores.cont == 0) {
        struct turma *turma = aux->turma;
        aux = aux->proximo;
        printf("A turma de codigo %s da disciplina %s foi excluida devido a exclusao do professor %s.\n",turma->codigo,turma->disciplina,professor->nome);
        remove_turma(lista,turma);
      } else {
        aux = aux->proximo;
      }
    } else {
      aux = aux->proximo;
    }
  }
}

void remove_professor(struct lista_professores *lista_professores,struct lista_turmas *lista_turmas) {
  setbuf(stdin, 0);
  long int siape;
  // printf("Professores cadastrados no sistema:\n");
  // imprime_lista_professores(lista_professores);
  setbuf(stdin, 0);
  printf("Digite o siape do professor a ser excluido totalmente do sistema: \n");
  printf("Digite 0 para deixar de excluir professores.\n");
  printf("SIAPE: ");
  scanf("%ld",&siape);
  while (siape>0) {
    if (!professor_inexistente(lista_professores,siape)) {
      struct professor *professor = busca_professor(lista_professores,siape);
      remove_professor_lista_turmas(lista_turmas,professor);
      remove_professor_lista_professores(lista_professores,professor);
      free(professor);
      printf("Professor excluido do sistema com sucesso!\n");
    }
    if (lista_professores->cont == 0) {
      printf("Voce excluiu todos os professores do sistema.\n");
      break;
    }
    printf("\n\n");
    // printf("Professores cadastrados no sistema:\n");
    // imprime_lista_professores(lista_professores);
    setbuf(stdin, 0);
    printf("Digite o siape do professor a ser excluido totalmente do sistema: \n");
    printf("Digite 0 para deixar de excluir professores.\n");
    printf("SIAPE: ");
    scanf("%ld",&siape);
  }
}

int remove_lista_professores_turma_primeiro(struct lista_professores_turma *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_professor *segundo = lista->inicio->proximo;
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

void remove_lista_professores_turma(struct turma *turma) {
  int cont = turma->professores.cont;
  for (int i=0;i<cont;i++) {
    remove_lista_professores_turma_primeiro(&(turma->professores));
  }
}

int remove_lista_alunos_turma_primeiro(struct lista_alunos_turma *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_aluno *segundo = lista->inicio->proximo;
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

void remove_lista_alunos_turma(struct turma *turma) {
  int cont = turma->alunos.cont;
  for (int i=0;i<cont;i++) {
    remove_lista_alunos_turma_primeiro(&(turma->alunos));
  }
}

int remove_lista_avaliacoes_turma_primeiro(struct lista_avaliacoes_turma *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio->avaliacao);
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_avaliacao *segundo = lista->inicio->proximo;
      free(lista->inicio->avaliacao);
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

void remove_lista_avaliacoes_turma(struct turma *turma) {
  int cont = turma->avaliacoes.cont;
  for (int i=0;i<cont;i++) {
    remove_lista_avaliacoes_turma_primeiro(&(turma->avaliacoes));
  }
}

int remove_lista_faltas_aula_primeiro(struct lista_alunos_faltas *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_aluno *segundo = lista->inicio->proximo;
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

void remove_lista_faltas_aula(struct lista_alunos_faltas *lista) {
  int cont = lista->cont;
  for (int i=0;i<cont;i++) {
    remove_lista_faltas_aula_primeiro(lista);
  }
}

int remove_lista_aulas_turma_primeiro(struct lista_aulas_turma *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      remove_lista_faltas_aula(&(lista->inicio->aula_ministrada->faltas_alunos));
      free(lista->inicio->aula_ministrada);
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_aula_ministrada *segundo = lista->inicio->proximo;
      remove_lista_faltas_aula(&(lista->inicio->aula_ministrada->faltas_alunos));
      free(lista->inicio->aula_ministrada);
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

void remove_lista_aulas_turma(struct turma *turma) {
  int cont = turma->aulas.cont;
  for (int i=0;i<cont;i++) {
    remove_lista_aulas_turma_primeiro(&(turma->aulas));
  }
}

int remove_turma_lista_turmas_primeiro(struct lista_turmas *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_turma *segundo = lista->inicio->proximo;
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_turma_lista_turmas_ultimo(struct lista_turmas *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_turma *penultimo = lista->inicio;
      struct no_turma *ultimo = lista->fim;
      while (penultimo->proximo->proximo != NULL) {
        penultimo = penultimo->proximo;
      }
      penultimo->proximo = NULL;
      lista->fim = penultimo;
      free(ultimo);
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_turma_lista_turmas_primeiro_com_dependencias(struct lista_turmas *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      remove_lista_professores_turma(lista->inicio->turma);
      remove_lista_alunos_turma(lista->inicio->turma);
      remove_lista_avaliacoes_turma(lista->inicio->turma);
      remove_lista_aulas_turma(lista->inicio->turma);
      free(lista->inicio->turma);
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_turma *segundo = lista->inicio->proximo;
      remove_lista_professores_turma(lista->inicio->turma);
      remove_lista_alunos_turma(lista->inicio->turma);
      remove_lista_avaliacoes_turma(lista->inicio->turma);
      remove_lista_aulas_turma(lista->inicio->turma);
      free(lista->inicio->turma);
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_turma_lista_turmas_indice(struct lista_turmas *lista,int indice) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (indice>=lista->cont || indice<0) {
      printf("A lista nao possui valor nesse indice\n");
      return -1;
    } else {
      if (indice==0) {
        return remove_turma_lista_turmas_primeiro(lista);
      } else if (indice==lista->cont-1) {
        return remove_turma_lista_turmas_ultimo(lista);
      }
      struct no_turma *valor = lista->inicio;
      int cont=1;
      while(cont<indice){
        valor = valor->proximo;
        cont++;
      }
      struct no_turma *proximo = valor->proximo->proximo;
      free(valor->proximo);
      valor->proximo = proximo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

void remove_turma(struct lista_turmas *lista_turmas, struct turma *turma) {
  struct no_turma *aux = lista_turmas->inicio;
  remove_lista_professores_turma(turma);
  remove_lista_alunos_turma(turma);
  remove_lista_avaliacoes_turma(turma);
  remove_lista_aulas_turma(turma);
  int indice = 0;
  while (aux!=NULL) {
    if (aux->turma == turma) {
      remove_turma_lista_turmas_indice(lista_turmas,indice);
      break;
    }
    indice++;
    aux = aux->proximo;
  }
  free(turma);
}

void liberar_memoria_lista_turmas(struct lista_turmas *lista_turmas) {
  int cont = lista_turmas->cont;
  for (int i=0;i<cont;i++) {
    remove_turma_lista_turmas_primeiro_com_dependencias(lista_turmas);
  }
}

int remove_curso_lista_cursos_primeiro(struct lista_cursos *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio->curso);
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_curso *segundo = lista->inicio->proximo;
      free(lista->inicio->curso);
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

void liberar_memoria_lista_cursos(struct lista_cursos *lista_cursos) {
  int cont = lista_cursos->cont;
  for (int i=0;i<cont;i++) {
    remove_curso_lista_cursos_primeiro(lista_cursos);
  }
}

void liberar_memoria_lista_professores(struct lista_professores *lista_professores) {
  int cont = lista_professores->cont;
  for (int i=0;i<cont;i++) {
    remove_professor_lista_professores_primeiro_com_dependencias(lista_professores);
  }
}

int remove_disciplina_lista_disciplinas_primeiro_com_dependencias(struct lista_disciplinas *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio->disciplina);
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_disciplina *segundo = lista->inicio->proximo;
      free(lista->inicio->disciplina);
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

void liberar_memoria_lista_disciplinas(struct lista_disciplinas *lista_disciplinas) {
  int cont = lista_disciplinas->cont;
  for (int i=0;i<cont;i++) {
    remove_disciplina_lista_disciplinas_primeiro_com_dependencias(lista_disciplinas);
  }
}

void liberar_memoria_lista_alunos(struct lista_alunos *lista_alunos) {
  int cont = lista_alunos->cont;
  for (int i=0;i<cont;i++) {
    remove_aluno_lista_alunos_primeiro_com_dependencias(lista_alunos);
  }
}

void remove_disciplina_lista_turmas(struct lista_turmas *lista,char *disciplina) {
  struct no_turma *aux = lista->inicio;
  while(aux!=NULL) {
    if (strcmp(aux->turma->disciplina,disciplina) == 0) {
      struct turma *turma = aux->turma;
      aux = aux->proximo;
      remove_turma(lista,turma);
    } else {
      aux = aux->proximo;
    }
  }
}

struct disciplina *busca_disciplina(struct lista_disciplinas *lista,char *codigo) {
  struct no_disciplina *aux = lista->inicio;
  while (aux!=NULL) {
    if (strcmp(aux->disciplina->codigo,codigo) == 0) {
      return aux->disciplina;
    }
  }
  return NULL;
}

int remove_disciplina_lista_disciplinas_primeiro(struct lista_disciplinas *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_disciplina *segundo = lista->inicio->proximo;
      free(lista->inicio);
      lista->inicio = segundo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_disciplina_lista_disciplinas_ultimo(struct lista_disciplinas *lista) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (lista->inicio->proximo == NULL) {
      free(lista->inicio);
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->cont = 0;
      return 1;
    } else {
      struct no_disciplina *penultimo = lista->inicio;
      struct no_disciplina *ultimo = lista->fim;
      while (penultimo->proximo->proximo != NULL) {
        penultimo = penultimo->proximo;
      }
      penultimo->proximo = NULL;
      lista->fim = penultimo;
      free(ultimo);
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

int remove_disciplina_lista_disciplinas_indice(struct lista_disciplinas *lista,int indice) {
  if (lista->inicio == NULL) {
    printf("A lista esta vazia\n");
    return -1;
  } else {
    if (indice>=lista->cont || indice<0) {
      printf("A lista nao possui valor nesse indice\n");
      return -1;
    } else {
      if (indice==0) {
        return remove_disciplina_lista_disciplinas_primeiro(lista);
      } else if (indice==lista->cont-1) {
        return remove_disciplina_lista_disciplinas_ultimo(lista);
      }
      struct no_disciplina *valor = lista->inicio;
      int cont=1;
      while(cont<indice){
        valor = valor->proximo;
        cont++;
      }
      struct no_disciplina *proximo = valor->proximo->proximo;
      free(valor->proximo);
      valor->proximo = proximo;
      lista->cont--;
      return 1;
    }
  }
  return -1;
}

void remove_disciplina_lista_disciplinas(struct lista_disciplinas *lista,struct disciplina *disciplina) {
  struct no_disciplina *aux = lista->inicio;
  int indice = 0;
  while (aux!=NULL) {
    if (aux->disciplina == disciplina) {
      remove_disciplina_lista_disciplinas_indice(lista,indice);
      return;
    }
    indice++;
    aux = aux->proximo;
  }
}

void remove_disciplina(struct lista_disciplinas *lista_disciplinas,struct lista_turmas *lista_turmas) {
  char disciplina[10];
  setbuf(stdin, 0);
  // printf("Disciplinas cadastradas no sistema:\n");
  // imprime_lista_disciplinas(lista_disciplinas);
  printf("Digite o codigo da disciplina: (ate 8 caracteres)\n");
  printf("Digite 0 para deixar de excluir disciplinas\n");
  printf("Codigo: ");
  fgets (disciplina, 10, stdin);
  retira_barra_n(disciplina);
  while (strcmp(disciplina,"0") != 0) {
    if (!disciplina_inexistente(lista_disciplinas,disciplina)) {
      remove_disciplina_lista_turmas(lista_turmas,disciplina);
      struct disciplina *disciplina_ponteiro = busca_disciplina(lista_disciplinas,disciplina);
      remove_disciplina_lista_disciplinas(lista_disciplinas,disciplina_ponteiro);
      free(disciplina_ponteiro);
      printf("Disciplina e turmas associadas excluidos com sucesso!\n");
    }
    setbuf(stdin, 0);
    if (lista_disciplinas->cont == 0) {
      printf("Voce excluiu todas as disciplinas do sistema.\n");
      break;
    }
    // printf("Disciplinas cadastradas no sistema:\n");
    // imprime_lista_disciplinas(lista_disciplinas);
    printf("Digite o codigo da disciplina: (ate 8 caracteres)\n");
    printf("Digite 0 para deixar de excluir disciplinas\n");
    printf("Codigo: ");
    fgets (disciplina, 10, stdin);
    retira_barra_n(disciplina);
  }
}

bool verificar_dependencia_cadastro_cursos(struct lista_cursos *lista_cursos) {
  if (lista_cursos->inicio==NULL) {
    printf("Voce precisa cadastrar algum curso primeiro.\n");
    return false;
  }
  return true;
}

bool verificar_dependencia_cadastro_disciplinas(struct lista_disciplinas *lista_disciplinas) {
  if (lista_disciplinas->inicio==NULL) {
    printf("Voce precisa cadastrar alguma disciplina primeiro.\n");
    return false;
  }
  return true;
}

bool verificar_dependencia_cadastro_alunos(struct lista_alunos *lista_alunos) {
  if (lista_alunos->inicio==NULL) {
    printf("Voce precisa cadastrar algum aluno primeiro.\n");
    return false;
  }
  return true;
}

bool verificar_dependencia_cadastro_turmas(struct lista_turmas *lista_turmas) {
  if (lista_turmas->inicio==NULL) {
    printf("Voce precisa cadastrar alguma turma primeiro.\n");
    return false;
  }
  return true;
}

bool verificar_dependencia_cadastro_professores(struct lista_professores *lista_professores) {
  if (lista_professores->inicio==NULL) {
    printf("Voce precisa cadastrar algum professor primeiro.\n");
    return false;
  }
  return true;
}

void imprimir_titulo_secao(char *secao) {
  printf("- VOCE ESTA NA SECAO DE %s -\n",secao);
}

void imprimir_aluno(struct aluno *aluno) {
  printf("MATRICULA | NOME | CURSO\n");
  printf("%ld | ",aluno->matricula);
  printf("%s | ",aluno->nome);
  printf("%s\n",aluno->curso);
}

void busca_alunos(struct lista_alunos *lista_alunos,struct lista_cursos *lista_cursos) {
  int opcao;
  printf("Como voce deseja pesquisar por um aluno?\n");
  printf("1 - Matricula\n");
  printf("2 - Nome\n");
  printf("3 - Curso\n");
  printf("0 - Sair\n");
  setbuf(stdin, 0);
  scanf("%d",&opcao);
  while (opcao<0 || opcao>3) {
    setbuf(stdin, 0);
    scanf("%d",&opcao);
  }
  struct no_aluno *aux;
  bool encontrou;
  switch(opcao) {
    case 1:
      setbuf(stdin, 0);
      long int matricula;
      printf("Digite a matricula do aluno: \n");
      scanf("%ld",&matricula);
      while (matricula<0 || aluno_inexistente(lista_alunos,matricula) && matricula != 0) {
        setbuf(stdin, 0);
        printf("Matricula nao encontrada. Digite a matricula do aluno: \n");
        printf("Digite 0 para sair.\n");
        scanf("%ld",&matricula);
      }
      if (matricula == 0) {
        break;
      }
      struct aluno *aluno = busca_aluno(lista_alunos,matricula);
      imprimir_aluno(aluno);
      break;
    case 2:
      setbuf(stdin, 0);
      char nome[50];
      printf("Digite o nome do aluno:\n");
      fgets (nome, 50, stdin);
      retira_barra_n(nome);
      while (strlen(nome) == 0) {
        setbuf(stdin, 0);
        printf("Digite o nome do aluno:\n");
        fgets (nome, 50, stdin);
        retira_barra_n(nome);
      }
      aux = lista_alunos->inicio;
      encontrou = false;
      while (aux!=NULL) {
        if (verifica_se_string_existe_em_string(nome,aux->aluno->nome)) {
          encontrou = true;
          imprimir_aluno(aux->aluno);
        }
        aux = aux->proximo;
      }
      if (!encontrou) {
        printf("Nenhum aluno encontrado com esse nome.\n");
      }
      break;
    case 3:
      setbuf(stdin, 0);
      char curso[50];
      printf("Digite o nome de um curso:\n");
      fgets (curso, 50, stdin);
      retira_barra_n(curso);
      while (strlen(curso) == 0 || curso_inexistente(lista_cursos,curso) && (strcmp(curso,"0") != 0)) {
        setbuf(stdin, 0);
        printf("Digite o nome de um curso:\n");
        printf("Digite 0 para sair.\n");
        fgets (curso, 50, stdin);
        retira_barra_n(curso);
      }
      if (strcmp(curso,"0") == 0) {
        break;
      }
      aux = lista_alunos->inicio;
      encontrou = false;
      while (aux!=NULL) {
        if (verifica_se_string_existe_em_string(curso,aux->aluno->curso)) {
          encontrou = true;
          imprimir_aluno(aux->aluno);
        }
        aux = aux->proximo;
      }
      if (!encontrou) {
        printf("Nenhum aluno encontrado com esse curso.\n");
      }
      break;
  }
  if (opcao>0) {
    printf("Deseja fazer nova busca de alunos? (1 para sim, 0 para nao) \n");
    setbuf(stdin, 0);
    int nova_busca;
    scanf("%d",&nova_busca);
    while(nova_busca!=0 && nova_busca!=1) {
      setbuf(stdin, 0);
      scanf("%d",&nova_busca);
    }
    if (nova_busca) {
      busca_alunos(lista_alunos,lista_cursos);
    }
  }
}

void imprimir_professor(struct professor *professor) {
  printf("SIAPE | NOME | AREA DE ATUACAO | TITULACAO\n");
  printf("%ld | ",professor->siape);
  printf("%s | ",professor->nome);
  printf("%s | ",professor->area_atuacao);
  printf("%s\n",professor->titulacao);
}

void busca_professores(struct lista_professores *lista_professores) {
  int opcao;
  printf("Como voce deseja pesquisar por um professor?\n");
  printf("1 - SIAPE\n");
  printf("2 - Nome\n");
  printf("3 - Area de atuacao\n");
  printf("4 - Titulacao\n");
  printf("0 - Sair\n");
  setbuf(stdin, 0);
  scanf("%d",&opcao);
  while (opcao<0 || opcao>3) {
    setbuf(stdin, 0);
    scanf("%d",&opcao);
  }
  struct no_professor *aux;
  bool encontrou;
  switch(opcao) {
    case 1:
      setbuf(stdin, 0);
      long int siape;
      printf("Digite o siape do professor: \n");
      scanf("%ld",&siape);
      while (siape<0 || professor_inexistente(lista_professores,siape) && siape!=0) {
        printf("Siape incorreto. Digite o siape do professor: \n");
        printf("Digite 0 para sair.\n");
        scanf("%ld",&siape);
      }
      if (siape == 0) {
        break;
      }
      struct professor *professor = busca_professor(lista_professores,siape);
      imprimir_professor(professor);
      break;
    case 2:
      setbuf(stdin, 0);
      char nome[50];
      printf("Digite o nome do professor: (ate 48 caracteres)\n");
      fgets (nome, 50, stdin);
      retira_barra_n(nome);
      while (strlen(nome) == 0) {
        setbuf(stdin, 0);
        printf("Digite o nome do professor: (ate 48 caracteres)\n");
        fgets (nome, 50, stdin);
        retira_barra_n(nome);
      }
      aux = lista_professores->inicio;
      encontrou = false;
      while (aux!=NULL) {
        if (verifica_se_string_existe_em_string(nome,aux->professor->nome)) {
          encontrou = true;
          imprimir_professor(aux->professor);
        }
        aux = aux->proximo;
      }
      if (!encontrou) {
        printf("Nenhum professor encontrado com esse nome.\n");
      }
      break;
    case 3:
      setbuf(stdin, 0);
      char area_atuacao[30];
      printf("Digite a area de atuacao do professor: (ate 28 caracteres)\n");
      fgets (area_atuacao, 30, stdin);
      retira_barra_n(area_atuacao);
      while (strlen(area_atuacao) == 0) {
        setbuf(stdin, 0);
        printf("Digite a area de atuacao do professor: (ate 28 caracteres)\n");
        fgets (area_atuacao, 30, stdin);
        retira_barra_n(area_atuacao);
      }
      aux = lista_professores->inicio;
      encontrou = false;
      while (aux!=NULL) {
        if (verifica_se_string_existe_em_string(area_atuacao,aux->professor->area_atuacao)) {
          encontrou = true;
          imprimir_professor(aux->professor);
        }
        aux = aux->proximo;
      }
      if (!encontrou) {
        printf("Nenhum professor encontrado com essa area de atuacao.\n");
      }
      break;
    case 4:
      setbuf(stdin, 0);
      char titulacao[50];
      printf("Digite a titulacao do professor: (ate 48 caracteres)\n");
      fgets (titulacao, 50, stdin);
      retira_barra_n(titulacao);
      while (strlen(titulacao) == 0) {
        setbuf(stdin, 0);
        printf("Digite a titulacao do professor: (ate 48 caracteres)\n");
        fgets (titulacao, 50, stdin);
        retira_barra_n(titulacao);
      }
      aux = lista_professores->inicio;
      encontrou = false;
      while (aux!=NULL) {
        if (verifica_se_string_existe_em_string(titulacao,aux->professor->titulacao)) {
          encontrou = true;
          imprimir_professor(aux->professor);
        }
        aux = aux->proximo;
      }
      if (!encontrou) {
        printf("Nenhum professor encontrado com essa titulacao.\n");
      }
      break;
  }
  if (opcao>0) {
    printf("Deseja fazer nova busca de professores? (1 para sim, 0 para nao) \n");
    int nova_busca;
    setbuf(stdin, 0);
    scanf("%d",&nova_busca);
    while(nova_busca!=0 && nova_busca!=1) {
      setbuf(stdin, 0);
      scanf("%d",&nova_busca);
    }
    if (nova_busca) {
      busca_professores(lista_professores);
    }
  }
}

void imprimir_disciplina(struct disciplina *disciplina) {
  printf("CODIGO | NOME | CURSO | CARGA HORARIA | PRE-REQUISITOS\n");
  printf("%s | ", disciplina->codigo);
  printf("%s | ", disciplina->nome);
  printf("%s | ", disciplina->curso);
  printf("%d | ", disciplina->carga_horaria);
  printf("%s\n", disciplina->pre_requisitos);
}


void busca_disciplinas(struct lista_disciplinas *lista_disciplinas,struct lista_cursos *lista_cursos) {
  int opcao;
  printf("Como voce deseja pesquisar por uma disciplina?\n");
  printf("1 - Codigo\n");
  printf("2 - Nome\n");
  printf("3 - Curso\n");
  printf("0 - Sair\n");
  setbuf(stdin, 0);
  scanf("%d",&opcao);
  while (opcao<0 || opcao>3) {
    setbuf(stdin, 0);
    scanf("%d",&opcao);
  }
  struct no_disciplina *aux;
  bool encontrou;
  switch(opcao) {
    case 1:
      setbuf(stdin, 0);
      char codigo[10];
      printf("Digite o codigo da disciplina: (ate 8 caracteres)\n");
      fgets (codigo, 10, stdin);
      retira_barra_n(codigo);
      while (strlen(codigo) == 0 || disciplina_inexistente(lista_disciplinas,codigo) && (strcmp(codigo,"0") != 0)) {
        setbuf(stdin, 0);
        printf("Codigo da disciplina nao existe. Digite outro: (ate 8 caracteres)\n");
        printf("Digite 0 para sair.\n");
        fgets (codigo, 10, stdin);
        retira_barra_n(codigo);
      }
      if (strcmp(codigo,"0") == 0) {
        break;
      }
      struct disciplina *disciplina = busca_disciplina(lista_disciplinas,codigo);
      imprimir_disciplina(disciplina);
      break;
    case 2:
      setbuf(stdin, 0);
      char nome[30];
      printf("Digite o nome da disciplina:\n");
      fgets (nome, 30, stdin);
      retira_barra_n(nome);
      while (strlen(nome) == 0) {
        setbuf(stdin, 0);
        printf("Digite o nome da disciplina:\n");
        fgets (nome, 30, stdin);
        retira_barra_n(nome);
      }
      aux = lista_disciplinas->inicio;
      encontrou = false;
      while (aux!=NULL) {
        if (verifica_se_string_existe_em_string(nome,aux->disciplina->nome)) {
          encontrou = true;
          imprimir_disciplina(aux->disciplina);
        }
        aux = aux->proximo;
      }
      if (!encontrou) {
        printf("Nenhuma disciplina encontrada com esse nome.\n");
      }
      break;
    case 3:
      setbuf(stdin, 0);
      char curso[50];
      printf("Digite o nome de um curso:\n");
      fgets (curso, 50, stdin);
      retira_barra_n(curso);
      while (strlen(curso) == 0 || curso_inexistente(lista_cursos,curso) && (strcmp(curso,"0") != 0)) {
        setbuf(stdin, 0);
        printf("Digite o nome de um curso:\n");
        printf("Digite 0 para sair.\n");
        fgets (curso, 50, stdin);
        retira_barra_n(curso);
      }
      if (strcmp(curso, "0") == 0) {
        break;
      }
      aux = lista_disciplinas->inicio;
      encontrou = false;
      while (aux!=NULL) {
        if (verifica_se_string_existe_em_string(curso,aux->disciplina->curso)) {
          encontrou = true;
          imprimir_disciplina(aux->disciplina);
        }
        aux = aux->proximo;
      }
      if (!encontrou) {
        printf("Nenhuma disciplina encontrada com esse curso.\n");
      }
      break;
  }
  if (opcao>0) {
    printf("Deseja fazer nova busca de disciplinas? (1 para sim, 0 para nao) \n");
    int nova_busca;
    setbuf(stdin, 0);
    scanf("%d",&nova_busca);
    while(nova_busca!=0 && nova_busca!=1) {
      setbuf(stdin, 0);
      scanf("%d",&nova_busca);
    }
    if (nova_busca) {
      busca_disciplinas(lista_disciplinas,lista_cursos);
    }
  }
}

void imprimir_turma(struct turma *turma) {
  printf("ID | CODIGO | DISCIPLINA\n");
  printf("%d | ",turma->id);
  printf("%s | ",turma->codigo);
  printf("%s\n",turma->disciplina);
  // printf("LISTA DE ALUNOS DA TURMA:\n");
  // imprime_lista_alunos_turma(&(aux->turma->alunos));
  // printf("LISTA DE PROFESSORES DA TURMA:\n");
  // imprime_lista_professores_turma(&(aux->turma->professores));
}

void busca_turmas(struct lista_turmas *lista_turmas,struct lista_disciplinas *lista_disciplinas) {
  int opcao;
  printf("Como voce deseja pesquisar por uma turma?\n");
  printf("1 - Codigo\n");
  printf("2 - Disciplina\n");
  printf("0 - Sair\n");
  setbuf(stdin, 0);
  scanf("%d",&opcao);
  while (opcao<0 || opcao>2) {
    setbuf(stdin, 0);
    scanf("%d",&opcao);
  }
  struct no_turma *aux;
  bool encontrou;
  switch(opcao) {
    case 1: 
      setbuf(stdin, 0);
      char codigo[10];
      printf("Digite o codigo da turma: (ate 8 caracteres)\n");
      fgets (codigo, 10, stdin);
      retira_barra_n(codigo);
      while (strlen(codigo) == 0) {
        setbuf(stdin, 0);
        printf("Digite o codigo da turma: (ate 8 caracteres)\n");
        fgets (codigo, 10, stdin);
        retira_barra_n(codigo);
      }
      aux = lista_turmas->inicio;
      encontrou = false;
      while (aux!=NULL) {
        if (verifica_se_string_existe_em_string(codigo,aux->turma->codigo)) {
          encontrou = true;
          imprimir_turma(aux->turma);
        }
        aux = aux->proximo;
      }
      if (!encontrou) {
        printf("Nenhuma turma encontrada com esse codigo.\n");
      }
      break;
    case 2:
      setbuf(stdin, 0);
      char disciplina[10];
      printf("Digite o codigo da disciplina: (ate 8 caracteres)\n");
      fgets (disciplina, 10, stdin);
      retira_barra_n(disciplina);
      while (strlen(disciplina) == 0 || disciplina_inexistente(lista_disciplinas,disciplina) && (strcmp(disciplina,"0") != 0)) {
        setbuf(stdin, 0);
        printf("Disciplina nao existe. Digite o codigo da disciplina: (ate 8 caracteres)\n");
        printf("Digite 0 para sair.\n");
        fgets (disciplina, 10, stdin);
        retira_barra_n(disciplina);
      }
      if (strcmp(disciplina,"0") == 0) {
        break;
      }
      aux = lista_turmas->inicio;
      encontrou = false;
      while (aux!=NULL) {
        if (verifica_se_string_existe_em_string(disciplina,aux->turma->disciplina)) {
          encontrou = true;
          imprimir_turma(aux->turma);
        }
        aux = aux->proximo;
      }
      if (!encontrou) {
        printf("Nenhuma turma encontrada com essa disciplina.\n");
      }
      break;
  }
  if (opcao>0) {
    printf("Deseja fazer nova busca de turmas? (1 para sim, 0 para nao) \n");
    int nova_busca;
    setbuf(stdin, 0);
    scanf("%d",&nova_busca);
    while(nova_busca!=0 && nova_busca!=1) {
      setbuf(stdin, 0);
      scanf("%d",&nova_busca);
    }
    if (nova_busca) {
      busca_turmas(lista_turmas,lista_disciplinas);
    }
  }
}

int main() {
  int opcao;

  imprimir_menu();
  opcao = ler_opcao_menu();
  struct lista_alunos lista_alunos;
  struct lista_cursos lista_cursos;
  struct lista_professores lista_professores;
  struct lista_disciplinas lista_disciplinas;
  struct lista_turmas lista_turmas;
  inicializa_lista_alunos(&lista_alunos);
  inicializa_lista_cursos(&lista_cursos);
  inicializa_lista_professores(&lista_professores);
  inicializa_lista_disciplinas(&lista_disciplinas);
  inicializa_lista_turmas(&lista_turmas);
  while (opcao>0) {
    if (opcao==1) {
      if (verificar_dependencia_cadastro_cursos(&lista_cursos)) {
        int submenu;
        imprimir_titulo_secao("ALUNOS");
        imprimir_submenu();
        submenu = ler_opcao_submenu();
        while (submenu > 0) {
          if (submenu == 1) {
            //cadastrar aluno
            struct aluno *aluno;
            aluno = le_aluno(&lista_cursos,&lista_alunos);
            insere_lista_alunos_fim(&lista_alunos,aluno);
            printf("Aluno(a) cadastrado com sucesso!\n");
          } else if (submenu == 2) {
            //excluir aluno
            if (verificar_dependencia_cadastro_alunos(&lista_alunos)) {
              remove_aluno(&lista_alunos,&lista_turmas);
            }
          } else if (submenu == 3) {
            if (verificar_dependencia_cadastro_alunos(&lista_alunos)) {
              busca_alunos(&lista_alunos,&lista_cursos);
            }
          }
          imprimir_titulo_secao("ALUNOS");
          imprimir_submenu();
          submenu = ler_opcao_submenu();
        }
      }
    } else if (opcao == 2) {
      int submenu;
      imprimir_titulo_secao("PROFESSORES");
      imprimir_submenu();
      submenu = ler_opcao_submenu();
      while (submenu > 0) {
        if (submenu == 1) {
          //cadastrar professor
          struct professor *professor;
          professor = le_professor(&lista_professores);
          insere_lista_professores_fim(&lista_professores,professor);
          printf("Professor cadastrado com sucesso!\n");
        } else if (submenu == 2) {
          if (verificar_dependencia_cadastro_professores(&lista_professores)) {
            remove_professor(&lista_professores,&lista_turmas);
          }
        } else if (submenu == 3) {
          if (verificar_dependencia_cadastro_professores(&lista_professores)) {
            busca_professores(&lista_professores);
          }
        }
        imprimir_titulo_secao("PROFESSORES");
        imprimir_submenu();
        submenu = ler_opcao_submenu();
      }
    } else if (opcao == 3) {
      if (verificar_dependencia_cadastro_cursos(&lista_cursos)) {
        int submenu;
        imprimir_titulo_secao("DISCIPLINAS");
        imprimir_submenu();
        submenu = ler_opcao_submenu();
        while (submenu > 0) {
          if (submenu == 1) {
            //cadastrar disciplina
            struct disciplina *disciplina;
            disciplina = le_disciplina(&lista_cursos,&lista_disciplinas);
            insere_lista_disciplinas_fim(&lista_disciplinas,disciplina);
            printf("Disciplina cadastrado com sucesso!\n");
          } else if (submenu == 2) {
            if (verificar_dependencia_cadastro_disciplinas(&lista_disciplinas)) {
              remove_disciplina(&lista_disciplinas,&lista_turmas);
            }
          } else if (submenu == 3) {
            if (verificar_dependencia_cadastro_disciplinas(&lista_disciplinas)) {
              busca_disciplinas(&lista_disciplinas,&lista_cursos);
            }
          }
          imprimir_titulo_secao("DISCIPLINAS");
          imprimir_submenu();
          submenu = ler_opcao_submenu();
        }
      }
    } else if (opcao==4) {
      if (verificar_dependencia_cadastro_disciplinas(&lista_disciplinas) && verificar_dependencia_cadastro_professores(&lista_professores)) {
        int submenu;
        imprimir_titulo_secao("TURMAS");
        imprimir_submenu();
        submenu = ler_opcao_submenu();
        while (submenu > 0) {
          if (submenu == 1) {
            //cadastrar turma
            struct turma *turma;
            turma = le_turma(&lista_alunos,&lista_professores,&lista_disciplinas);
            insere_lista_turmas_fim(&lista_turmas,turma);
            printf("Turma cadastrada com sucesso!\n");
          } else if (submenu == 2) {
            if (verificar_dependencia_cadastro_turmas(&lista_turmas)) {
              // printf("Turmas cadastradas no sistema:\n");
              // imprime_lista_turmas(&lista_turmas);
              setbuf(stdin, 0);
              int id_turma;
              printf("Digite o ID da turma que voce deseja excluir: ");
              scanf("%d",&id_turma);
              while (id_turma<1 || turma_inexistente(&lista_turmas,id_turma)) {
                setbuf(stdin, 0);
                printf("Digite o ID da turma que voce deseja excluir: ");
                scanf("%d",&id_turma);
              }
              struct turma *turma;
              turma = busca_turma(&lista_turmas,id_turma);
              remove_turma(&lista_turmas,turma);
              printf("Turma excluida do sistema com sucesso!\n");
            }
          } else if (submenu == 3) {
            if (verificar_dependencia_cadastro_turmas(&lista_turmas)) {
              busca_turmas(&lista_turmas,&lista_disciplinas);
            }
          }
          imprimir_titulo_secao("TURMAS");
          imprimir_submenu();
          submenu = ler_opcao_submenu();
        }
      }
    } else if (opcao==5) {
      //cadastrar curso
      struct curso *curso;
      curso = le_curso();
      insere_lista_cursos_fim(&lista_cursos,curso);
      printf("Curso cadastrado com sucesso!\n");
    } else if (opcao==6) {
      if (verificar_dependencia_cadastro_turmas(&lista_turmas)) {
        int submenu;
        imprimir_titulo_secao("AVALIACOES");
        imprimir_submenu();
        submenu = ler_opcao_submenu();
        while (submenu > 0) {
          if (submenu == 1) {
            //cadastrar avaliacao
            printf("Turmas cadastradas no sistema:\n");
            imprime_lista_turmas(&lista_turmas);
            setbuf(stdin, 0);
            int id_turma;
            printf("Digite o ID da turma que voce deseja lancar notas aos alunos: ");
            scanf("%d",&id_turma);
            while (id_turma<1 || turma_inexistente(&lista_turmas,id_turma)) {
              setbuf(stdin, 0);
              printf("Digite o ID da turma que voce deseja lancar notas aos alunos: ");
              scanf("%d",&id_turma);
            }
            struct turma *turma;
            turma = busca_turma(&lista_turmas,id_turma);
            lancar_notas_turma(turma);
          } else if (submenu == 2) {
            printf("Turmas cadastradas no sistema:\n");
            imprime_lista_turmas(&lista_turmas);
            int id_turma;
            setbuf(stdin, 0);
            printf("Digite o ID da turma que voce deseja excluir alguma avaliacao de algum aluno: ");
            scanf("%d",&id_turma);
            while (id_turma<1 || turma_inexistente(&lista_turmas,id_turma)) {
              setbuf(stdin, 0);
              printf("Digite o ID da turma que voce deseja excluir alguma avaliacao de algum aluno: ");
              scanf("%d",&id_turma);
            }
            struct turma *turma;
            turma = busca_turma(&lista_turmas,id_turma);
            excluir_notas_turma(turma);
          } else if (submenu == 3) {
            printf("Turmas cadastradas no sistema:\n");
            imprime_lista_turmas(&lista_turmas);
            setbuf(stdin, 0);
            int id_turma;
            printf("Digite o ID da turma que voce deseja excluir alguma avaliacao de algum aluno: ");
            scanf("%d",&id_turma);
            while (id_turma<1 || turma_inexistente(&lista_turmas,id_turma)) {
              setbuf(stdin, 0);
              printf("Digite o ID da turma que voce deseja excluir alguma avaliacao de algum aluno: ");
              scanf("%d",&id_turma);
            }
            struct turma *turma;
            turma = busca_turma(&lista_turmas,id_turma);
            buscar_notas_turma(turma);
          }
          imprimir_titulo_secao("AVALIACOES");
          imprimir_submenu();
          submenu = ler_opcao_submenu();
        }
      }
    } else if (opcao==7) {
      if (verificar_dependencia_cadastro_alunos(&lista_alunos) && verificar_dependencia_cadastro_turmas(&lista_turmas)) {
        printf("Turmas cadastradas no sistema:\n");
        imprime_lista_turmas(&lista_turmas);
        setbuf(stdin, 0);
        int id_turma;
        printf("Digite o ID da turma que voce deseja matricular alunos: ");
        scanf("%d",&id_turma);
        while (id_turma<1 || turma_inexistente(&lista_turmas,id_turma)) {
          setbuf(stdin, 0);
          printf("Digite o ID da turma que voce deseja matricular alunos: ");
          scanf("%d",&id_turma);
        }
        struct turma *turma;
        turma = busca_turma(&lista_turmas,id_turma);
        matricular_alunos_turma(&lista_alunos,turma);
      }
    } else if (opcao==8) {
      if (verificar_dependencia_cadastro_turmas(&lista_turmas)) {
        printf("Turmas cadastradas no sistema:\n");
        imprime_lista_turmas(&lista_turmas);
        setbuf(stdin, 0);
        int id_turma;
        printf("Digite o ID da turma que voce deseja lancar aulas: ");
        scanf("%d",&id_turma);
        while (id_turma<1 || turma_inexistente(&lista_turmas,id_turma)) {
          setbuf(stdin, 0);
          printf("Digite o ID da turma que voce deseja lancar aulas: ");
          scanf("%d",&id_turma);
        }
        struct turma *turma;
        turma = busca_turma(&lista_turmas,id_turma);
        lancar_aulas_turma(turma,&lista_disciplinas);
      }
    } else if (opcao==9) {
      if (verificar_dependencia_cadastro_turmas(&lista_turmas)) {
        printf("Turmas cadastradas no sistema:\n");
        imprime_lista_turmas(&lista_turmas);
        setbuf(stdin, 0);
        int id_turma;
        printf("Digite o ID da turma que voce deseja gerar o relatorio: ");
        scanf("%d",&id_turma);
        while (id_turma<1 || turma_inexistente(&lista_turmas,id_turma)) {
          setbuf(stdin, 0);
          printf("Digite o ID da turma que voce deseja gerar o relatorio: ");
          scanf("%d",&id_turma);
        }
        struct turma *turma;
        turma = busca_turma(&lista_turmas,id_turma);
        gerar_relatorio(turma,&lista_disciplinas);
      }
    }
    printf("\n\n");
    imprimir_menu();
    opcao = ler_opcao_menu();
  }
  liberar_memoria_lista_turmas(&lista_turmas);
  liberar_memoria_lista_cursos(&lista_cursos);
  liberar_memoria_lista_professores(&lista_professores);
  liberar_memoria_lista_disciplinas(&lista_disciplinas);
  liberar_memoria_lista_alunos(&lista_alunos);
  printf("FIM DO PROGRAMA\n");
  return 0;
}