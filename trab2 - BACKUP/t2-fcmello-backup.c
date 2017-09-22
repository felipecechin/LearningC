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

main() 
{
  double angulo,anguloEmGraus;
  int n,j,k,m;
  double resultadoSeno, resultadoCosseno;
  
  for (anguloEmGraus=1;anguloEmGraus<90;anguloEmGraus++) {
  angulo = (anguloEmGraus * M_PI)/180;
  n = 1;
  j = 1;
  resultadoSeno = 0;
  resultadoCosseno = 0;
  k = 1;
  m = 0;
  
  resultadoSeno = seno(angulo,n);
  while(j > 0) {
  	n = n+2;
  	j++;
  	if (seno(angulo,n) < pow(10,-6)) {
  	  j = 0;	
	} else {
	  if (j % 2 == 0) {
	    resultadoSeno = resultadoSeno - seno(angulo,n);
	  } else {
	  	resultadoSeno = resultadoSeno + seno(angulo,n);
	  }
	}
  }
  
  printf("Resultado seno: %Lf",resultadoSeno);
  
  resultadoCosseno = cosseno(angulo,m);
  while(k > 0) {
  	m = m+2;
  	k++;
  	if (cosseno(angulo,m) < pow(10,-6)) {
  	  k = 0;	
	} else {
	  if (k % 2 == 0) {
	    resultadoCosseno = resultadoCosseno - cosseno(angulo,m);
	  } else {
	  	resultadoCosseno = resultadoCosseno + cosseno(angulo,m);
	  }
	}
  }
  
  printf("\nResultado cosseno: %Lf",resultadoCosseno);
  
  printf("A tg eh %Lf",resultadoSeno/resultadoCosseno);
  }
  
}
