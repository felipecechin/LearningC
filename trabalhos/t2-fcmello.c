//Aluno: Felipe Cechin Mello. Programa criado para calcular a tangente dos angulos entre 0 e 89 graus, utilizando a serie de Taylor para o calculo do seno e do cosseno.
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

double potencia(double x, int n)
{
  return pow(x,n);
}

double termoSerieTaylor(double x, int n) 
{	
  if (n==0) {
    return 1;
  } else if (n==1) {
    return x;
  } else {
    return (potencia(x,n)/fatorial(n));
  }
}

double calculaFuncaoSenoCosseno(int n, double angulo)
{
  int i = 1;
  double resultado = 0;
  while(i>=1) {
  	if (i % 2 == 0) {
	  resultado = resultado - termoSerieTaylor(angulo,n);
	} else {
	  resultado = resultado + termoSerieTaylor(angulo,n);
	}
    if (termoSerieTaylor(angulo,n) < pow(10,-6)) {
  	  break;	
	}
    n = n+2;
    i++;
  }
  return resultado;
}

double cosseno(double angulo) 
{
  return calculaFuncaoSenoCosseno(0, angulo);
}

double seno(double angulo)
{
  return calculaFuncaoSenoCosseno(1, angulo);
}

double tangente(double seno, double cosseno)
{
  return seno/cosseno;
}

main(void) 
{
  double resultadoSeno, resultadoCosseno;
  
  int i = 0;
  int anguloEmGraus = 0;
  double angulo = 0;
  for (i = 1;i<=90;i++) {
  	angulo = (anguloEmGraus * M_PI)/180;
  	resultadoSeno = seno(angulo);
  	resultadoCosseno = cosseno(angulo);
  	
    printf("%2d %.4f    ",anguloEmGraus,tangente(resultadoSeno,resultadoCosseno));
    
	if(i%3==0){
      anguloEmGraus = anguloEmGraus - 59;
      printf("\n");
	}else{
	  anguloEmGraus = anguloEmGraus + 30;
	}
  }
  
}
