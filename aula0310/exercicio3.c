//O n�mero 3025 � interessante: 30 + 25 = 55 e 55^2 = 3025. Fa�a uma fun��o que recebe um n�mero e e retorna um bool 
//que diz se esse n�mero tem essa mesma interess�ncia. Fa�a um programa que usa essa fun��o e um comando for para 
//imprimir todos os n�meros de 4 d�gitos que tenham essa mesma caracter�stica.
#include <stdio.h>
#include <stdbool.h>

bool verificarNumero(int numero) 
{
  int parte1,parte2,soma;
  parte1 = numero % 100;
  parte2 = numero/100;
  soma = parte1 + parte2;
  if (soma*soma == numero) {
    return true;
  } else {
	return false;	
  }
}

int main(void)
{
  int i;
  for (i=1000;i<=9999;i++) {
    if (verificarNumero(i)) {
      printf("%d\n",i);
    }
  }
  return 0;	
}
