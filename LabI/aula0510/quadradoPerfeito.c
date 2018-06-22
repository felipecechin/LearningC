//Verificar se um numero eh quadrado perfeito atraves da decomposicao por fatores primos
#include <stdio.h>
#include <stdbool.h>
#define TAM 5

bool numeroPrimo(int numero) 
{
  int i;
  int cont = 0;
  for (i=1;i<numero;i++) {
    if (numero%i == 0) {
      cont++;
	}
  }
  if (cont>1) {
    return false;
  } else {
  	return true;
  }
}

main()
{
  int numero,i;
  printf("Digite um numero: ");
  scanf("%d",&numero);
  
  while(numero>0) {
	
	if (numeroPrimo(numero)) {
	  printf("O numero %d nao eh quadrado perfeito\n",numero);
    } else {
      bool quadPerfeito = true;
	  int numerador = numero;
	  int divisao;
	  int raiz = 1;
	  int j;
	  for (i=2;i<numero;i++) {
	  	int contPrimo = 0;
	    if (numeroPrimo(i)) {
	      for(;;) {
	      	if (numerador%i!=0) {
	      	  break;	
			}
			contPrimo++;
	        divisao = numerador/i;
			numerador = divisao;
			if (numerador == 1) {
			  break;
			}	
		  }   
		  if (contPrimo%2 !=0) {
		    quadPerfeito = false;  
		    break;
		  } else if (numero%i==0) {
		  	contPrimo = contPrimo/2;
		  	for (j=0;j<contPrimo;j++) {
		  	  raiz = raiz*i;  	
			}
		  }
	      if (numerador == 1) {
	        break;	
		  }         
	    }
	  }
	  if (quadPerfeito) {
	  	printf("O numero %d eh quadrado perfeito. Raiz: %d\n",numero,raiz);
	  } else {
	  	printf("O numero %d nao eh quadrado perfeito\n",numero);
	  }
	}
	
	printf("Digite um numero: ");
    scanf("%d",&numero);
  
  }
}
