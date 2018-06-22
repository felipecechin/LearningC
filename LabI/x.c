#include <stdio.h>
#include <math.h>

main()
{
  int n;
  float raiz;
  printf("digite um numero\n");
  scanf("%d",&n);
  
  raiz = sqrt(n);
  if (raiz>20) {
  	printf("A raiz do numero eh maior que 20");
  } else {
  	printf("A raiz do numero eh menor ou igual a 20");
  }

}
