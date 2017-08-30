#include <stdio.h>
#include <math.h>

main() 
{
  float a,b,c;
  float r1,y1;
  float delta;
  
  printf("Informe o a, o b e o c da equacao\n");
  scanf("%f%f%f",&a,&b,&c);
  
  //calcula raizes
  delta = (b*b) - (4*a*c);
  
  
  if (delta > 0) {
    float r2;   
    r1 = (-b - sqrt(delta))/(2*a);
  	r2 = (-b + sqrt(delta))/(2*a);	
  	printf("As raizes da equacao sao %.2f e %.2f\n", r1, r2);
	float y2;
	y1 = a*r1*r1 + b*r1 + c;
	y2 = a*r2*r2 + b*r2 + c;
	printf("Os valores de y sao %.2f e %.2f", y1, y2);
  } else if (delta == 0) {
    r1 = (-b + sqrt(delta))/(2*a);
	printf("A unica raiz da equacao e %.2f\n", r1);
	y1 = a*r1*r1 + b*r1 + c;
	printf("O valor de y eh %.2f", y1);	    
  } else {
  	float r2;
  	printf("A equacao nao tem raizes reais, somente imaginarias\n");
  	r1 = -b/(2*a); 
  	r2 = sqrt(-delta)/(2*a);
	printf("As raizes da equacao sao (%.2f - %.2fi) e (%.2f + %.2fi)\n",r1,r2,r1,r2);
	float y2;
	y1 = a*((r1*r1) +2*(r1*r2) - (r2*r2)) + (b*r1)+(b*r2) + c;
	y2 = a*((r1*r1) -2*(r1*r2) - (r2*r2)) + (b*r1)+(b*-r2) + c;
	printf("Os valores de y sao %.2f e %.2f", y1, y2); 
		
  }
   
}
