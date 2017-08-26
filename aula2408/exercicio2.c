#include <stdio.h>

main() 
{
	int numero;
	int dezena;
	int unidade;

	printf("Informe um número inteiro: ");
	scanf("%d",&numero);

	if (numero<100) {
		unidade = numero % 10;
		dezena = numero /10;

		printf("O número invertido é %d%d\n", unidade, dezena);
	} else {
		printf("Você digitou um número maior que 100");
	}

}