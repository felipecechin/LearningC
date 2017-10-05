#include <stdio.h>
#define TAM 5
main()
{
  int numero,i;
  printf("Digite um numero: ");
  scanf("%d",&numero);
  
  while(numero>0) {
    
    for (i=1;i<numero;i++) {
      if (numero%i) {
      	cont++;
	  }
	}
    if (cont>1) {
      quadPerfeito = false;
	}
	
	printf("Digite um numero: ");
    scanf("%d",&numero);
  
  }
}
