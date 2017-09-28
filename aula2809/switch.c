#include <stdio.h>

int calcula(int v1, char op, int v2)
{
  int resultado = 0;
  switch(op) {
  	case '+':
  	  resultado = v1 + v2;
  	  break;
  	case '-':
  	  resultado = v1 - v2;
  	  break;
  	case '*':
  	  resultado = v1 * v2;
  	  break;
  	case '/':
  	  resultado = v1/v2;
  	  break;
  }
  return resultado;
}

main(void)
{
  int a,b;
  char o;
  
  
  scanf("%d %c %d",&a,&o,&b);
  
  
  printf("%d %c %d = %d",a,o,b,calcula(a,o,b));
  //printf("\n%d",o);
}
