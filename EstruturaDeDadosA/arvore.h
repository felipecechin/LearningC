
struct no {
  int valor;
  int alt;
  struct no* esq;
  struct no* dir;
};

typedef struct no arvore;

arvore *cria_vazia();
arvore *cria_arvore(int valor, arvore *sae, arvore *sad);
int esta_vazia(arvore *a);
arvore *desaloca_arvore(arvore *a);
int existe_valor(int valor, arvore *a);
void imprime(arvore *a);
