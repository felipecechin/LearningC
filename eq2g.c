#include <stdio.h>
#include <math.h>

main() 
{
  float a,b,c;
  float r1,y1;
  float delta;
  
  printf("Informe o a, o b e o c da equação\n");
  scanf("%f%f%f",&a,&b,&c);
  
  //calcula raizes
  delta = (b*b) - (4*a*c);
  
  
  if (delta > 0) {
    float r2;   
    r1 = (-b - sqrt(delta))/(2*a);
  	r2 = (-b + sqrt(delta))/(2*a);	
  	printf("As raizes da equacao sao %f e %f\n",r1,r2);
	float y2;
	y1 = a*r1*r1 + b*r1 + c;
	y2 = a*r2*r2 + b*r2 + c;
	printf("Os valores de y sao %f e %f",y1,y2);
  } else if (delta == 0) {
    r1 = (-b + sqrt(delta))/(2*a);
	printf("A unica raiz da equacao e %f\n",r1);
	y1 = a*r1*r1 + b*r1 + c;
	printf("O valor de y eh %f",y1);	    
  } else {
  	printf("A equacao nao tem raizes reais");
  }
   
}
