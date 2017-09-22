#include <stdio.h>
#include <math.h>

int fatorial(int n)
{
  int resultado;
  int i;
  resultado = 1;
  for (i=1;i<=n;i++) {
    resultado = resultado * i;
  }
  return resultado;
}

double seno(double x, int n) 
{	
  return (pow(x,n)/fatorial(n));
}

double cosseno(double x, int n)
{	
  return (pow(x,n)/fatorial(n));
}

main(void) 
{
  double angulo,anguloEmGraus;
  int n,j;
  double resultadoSeno, resultadoCosseno;
  
  for (anguloEmGraus=1;anguloEmGraus<90;anguloEmGraus++) {
  	
    angulo = (anguloEmGraus * M_PI)/180;
    n = 1;
    j = 1;
    resultadoSeno = 0;
    resultadoCosseno = 0;
  
    
    while(j > 0) {
  	  if (seno(angulo,n) < pow(10,-6)) {
  	    j = 0;	
	  } else {
	    if (j % 2 == 0) {
	      resultadoSeno = resultadoSeno - seno(angulo,n);
	    } else {
	  	  resultadoSeno = resultadoSeno + seno(angulo,n);
	    }
	    n = n+2;
  	    j++;
	  }
    }
  	
    printf("Resultado seno: %Lf",resultadoSeno);
  	
  	j = 1;
  	n = 0;
  	
    while(j > 0) {
  	  if (cosseno(angulo,n) < pow(10,-6)) {
  	    j = 0;	
	  } else {
	    if (j % 2 == 0) {
	      resultadoCosseno = resultadoCosseno - cosseno(angulo,n);
	    } else {
	  	  resultadoCosseno = resultadoCosseno + cosseno(angulo,n);
	    }
	    n = n+2;
  	    j++;
	  }
    }
  
    printf("\nResultado cosseno: %Lf",resultadoCosseno);
  
    printf("A tg eh %Lf",resultadoSeno/resultadoCosseno);
  }
  
}
