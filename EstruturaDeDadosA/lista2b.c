#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct no{
  struct no *anterior;
  int valor;
  struct no *proximo;
};

int main() {
  struct l_descr_circ lista1;
  struct l_descr_circ lista2;

  inicializa_lista_circ(&lista1);
  inicializa_lista_circ(&lista2);

  insere_fim_circ(&lista1,20);
  insere_fim_circ(&lista1,40);
  insere_fim_circ(&lista2,30);
  insere_fim_circ(&lista2,50);
  // copia_inv(&lista2,&lista1);
  intercala(&lista1,&lista2);
  imprime_lista_circ(&lista1);
  // printf("--------------------------\n");
  // imprime_lista_circ(&lista2);
  // printf("-----------------\n");
  // imprime_lista_circ(&lista2);
}