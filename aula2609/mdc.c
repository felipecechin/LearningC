#include <stdio.h>

main()
{
  int n1,n2,resto,menor,maior,mmc;
  
  printf("Digite um numero: ");
  scanf("%d",&n1);

  printf("Digite um numero: ");
  scanf("%d",&n2);

  
  if (n1>n2) {
    maior = n1;
    menor = n2;
  } else {
    maior = n2;
    menor = n1;
  }

  for(;;) {
   resto = maior-menor;
   if (resto == menor) break;
   maior = menor;
   menor = resto;
  }

  mmc = (n1*n2)/menor;

  printf("O maximo divisor comum de %d e %d eh %d\n",n1,n2,menor);
  printf("O mmc de %d e %d eh %d\n",n1,n2,mmc);

}
