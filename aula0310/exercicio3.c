//O número 3025 é interessante: 30 + 25 = 55 e 55^2 = 3025. Faça uma função que recebe um número e e retorna um bool 
//que diz se esse número tem essa mesma interessância. Faça um programa que usa essa função e um comando for para 
//imprimir todos os números de 4 dígitos que tenham essa mesma característica.
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
