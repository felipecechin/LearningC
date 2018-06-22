#include <stdio.h>

main() {
	int numero1,numero2,numero3;
	float media;

	printf("Informe um número inteiro: ");
	scanf("%d",&numero1);

	printf("Informe outro número inteiro: ");
	scanf("%d",&numero2);

	printf("Informe mais um número inteiro: ");
	scanf("%d",&numero3);

	media = (float) (numero1+numero2+numero3)/3;

	printf("A média dos números inteiros é %f\n", media);
}