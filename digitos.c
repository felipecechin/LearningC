#include <stdio.h>

main()
{
  int digitos,numero,divisao;
  
  digitos = 0;
  numero = 344315;
  divisao = 1;
  while(divisao > 0) {
    divisao = numero/10;
	numero = divisao;  
	digitos++;
  }
  
  printf("O numero tem %d digitos",digitos);
}
