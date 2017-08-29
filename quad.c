#include <stdio.h>
#include <locale.h>

main()
{
	float lado1, lado2;
	float area;
	
	setlocale(LC_ALL,"Portuguese_Brazil");
	
	printf("Informe os lados do retângulo:\n");
	scanf("%f", &lado1);
	scanf("%f", &lado2);

	area = lado1 * lado2;

	printf("area: %.2f\n", area);
}
