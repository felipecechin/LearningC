//Aluno: Felipe Cechin Mello. Programa para calcular a distância entre dois pontos da Terra passando pelo interior dela.
#include <stdio.h>
#include <math.h>

main() 
{
  float lat1, long1, lat2, long2, distancia;
  int raio = 6500000;
  
  printf("Digite a latitude de um ponto do planeta Terra: ");
  scanf("%f", &lat1);
  printf("Digite a longitude do ponto: ");
  scanf("%f", &long1);
  printf("Digite a latitude de um outro ponto do planeta Terra: ");
  scanf("%f", &lat2);
  printf("Digite a longitude do ponto: ");
  scanf("%f", &long2);
  
  lat1 = lat1 * M_PI/180;
  long1 = long1 * M_PI/180;
  lat2 = lat2 * M_PI/180;
  long2 = long2 * M_PI/180;
  
  distancia = sqrt((pow(raio,2)+pow(raio,2)) - 2*pow(raio,2)*((cos(lat1)*cos(lat2)*cos(long1 - long2)) + (sin(lat1)*sin(lat2))));
  
  printf("A distancia em metros entre esses dois pontos passando pelo interior da Terra e' %g\n",distancia);
}