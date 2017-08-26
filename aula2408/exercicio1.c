#include <stdio.h>
#include <math.h>

main() {
	float raio;
	float area;

	printf("Informe o raio do círculo: ");
	scanf("%f",&raio);

	area = M_PI * raio * raio;

	printf("A área do círculo é %.2f\n", area);
}