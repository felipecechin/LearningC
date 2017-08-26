#include <stdio.h>

main() {
	int numero,unidade,dezena,centena;

	printf("Informe um número inteiro: ");
	scanf("%d",&numero);

	if (numero<100) {
		unidade = numero % 10;
		dezena = numero / 10;

		printf("O número invertido é %d%d\n", unidade,dezena);
	} else if (numero<1000) {
		unidade = numero % 10;
		dezena = (numero / 10) % 10;
		centena = (numero / 10) / 10;
		printf("O número invertido é %d%d%d\n", unidade,dezena,centena); 
	} else {
		printf("O número informado deve ser menor que 1000\n");
	}
}