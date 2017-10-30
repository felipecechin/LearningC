//Aluno: Felipe Cechin Mello. O programa eh um jogo de tabuleiro. O usuario deve preencher o tabuleiro de 10 posicoes de forma nao decrescente com o valor do dado para ganhar.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int dado() 
{
  int num;
  num = rand()%6;
  if (num == 0) {
  	return 6;
  } else {
  	return num;
  }
}


bool verificaTabuleiro(int valorDado,int tabuleiro[])
{
  int i,j,posicaoValorMenor = -1,posicaoValorMaior = -1,cont = 0;
  bool tabuleiroOk = true,temPosicaoNaoP = false;
  
  for (i=0;i<10;i++) {
    if (tabuleiro[i] != 0) {
      cont++;
	}
  }
  
  if (cont==1 && tabuleiro[0]!=0 && valorDado<tabuleiro[0]) {
    tabuleiroOk = false;
  } else if (tabuleiro[9]!=0 && valorDado>tabuleiro[9]) {
  	tabuleiroOk = false;
  } else {
    switch(valorDado) {
      case 1:
        for (i=0;i<10;i++) {
          if (tabuleiro[i] == 1) {
            posicaoValorMenor = i;  
            break;
	      }
	    }
        j = 2;
	    while (posicaoValorMaior == -1 && j<7) {
          for (i=0;i<10;i++) {
            if (tabuleiro[i] == j) {
              posicaoValorMaior = i;
			  break;  
		    }
	      }
	      j++;
	    }
	    if (posicaoValorMenor != -1 && posicaoValorMaior != -1 && posicaoValorMenor == 0) {  
          for (i=posicaoValorMenor+1;i<posicaoValorMaior;i++) {
            if (tabuleiro[i] == 0) {
		      temPosicaoNaoP = true;  
		      break;
		    }
	      }
	      if (!temPosicaoNaoP) {
	        tabuleiroOk = false;
	      }
	    } else if (posicaoValorMaior != -1 && posicaoValorMenor == -1) {
	      for (i=0;i<posicaoValorMaior;i++) {
            if (tabuleiro[i] == 0) {
		      temPosicaoNaoP = true;  
		      break;
		    }
	      }
	      if (!temPosicaoNaoP) {
	        tabuleiroOk = false;
	      }
	    } 
        break;
      case 2:
        for (i=0;i<10;i++) {
          if (tabuleiro[i] == 1) {
            posicaoValorMenor = i;  
		  }
	    }
	    j = 3;
	    while (posicaoValorMaior == -1 && j<7) {
          for (i=0;i<10;i++) {
            if (tabuleiro[i] == j) {
              posicaoValorMaior = i;  
              break;
		    }
	      }
	      j++;
	    }
	    if (posicaoValorMenor != -1 && posicaoValorMaior != -1) {  
          for (i=posicaoValorMenor+1;i<posicaoValorMaior;i++) {
            if (tabuleiro[i] == 0) {
		      temPosicaoNaoP = true;  
		      break;
		    }
	      }
	      if (!temPosicaoNaoP) {
	        tabuleiroOk = false;
	      }
	    }
        break;
      case 3:
        j = 2;
	    while (posicaoValorMenor == -1 && j>0) {
          for (i=0;i<10;i++) {
            if (tabuleiro[i] == j) {
              posicaoValorMenor = i;  
		    }
	      }
	      j--;
	    }
        j = 4;
	    while (posicaoValorMaior == -1 && j<7) {
          for (i=0;i<10;i++) {
            if (tabuleiro[i] == j) {
              posicaoValorMaior = i;  
              break;
		    }
	      }
	      j++;
	    }
	    if (posicaoValorMenor != -1 && posicaoValorMaior != -1) {  
          for (i=posicaoValorMenor+1;i<posicaoValorMaior;i++) {
            if (tabuleiro[i] == 0) {
		      temPosicaoNaoP = true;  
		      break;
		    }
	      }
	      if (!temPosicaoNaoP) {
	        tabuleiroOk = false;
	      }
	    }
        break;
      case 4:
        j = 3;
	    while (posicaoValorMenor == -1 && j>0) {
          for (i=0;i<10;i++) {
            if (tabuleiro[i] == j) {
              posicaoValorMenor = i;  
		    }
	      }
	      j--;
	    }
        j = 5;
	    while (posicaoValorMaior == -1 && j<7) {
          for (i=0;i<10;i++) {
            if (tabuleiro[i] == j) {
              posicaoValorMaior = i;  
              break;
		    }
	      }
	      j++;
	    }
	    if (posicaoValorMenor != -1 && posicaoValorMaior != -1) {  
          for (i=posicaoValorMenor+1;i<posicaoValorMaior;i++) {
            if (tabuleiro[i] == 0) {
		      temPosicaoNaoP = true;  
		      break;
		    }
	      }
	      if (!temPosicaoNaoP) {
	        tabuleiroOk = false;
	      }
	    }	
        break;
      case 5:
        j = 4;
	    while (posicaoValorMenor == -1 && j>0) {
          for (i=0;i<10;i++) {
            if (tabuleiro[i] == j) {
              posicaoValorMenor = i;  
		    }
	      }
	      j--;
	    }
        for (i=0;i<10;i++) {
          if (tabuleiro[i] == 6) {
            posicaoValorMaior = i;
		    break;  
		  }
	    }
	    if (posicaoValorMenor != -1 && posicaoValorMaior != -1) {  
          for (i=posicaoValorMenor+1;i<posicaoValorMaior;i++) {
            if (tabuleiro[i] == 0) {
		      temPosicaoNaoP = true;  
		      break;
		    }
	      }
	      if (!temPosicaoNaoP) {
	        tabuleiroOk = false;
	      }
	    }
        break;
      case 6:
        j = 5;
	    while (posicaoValorMenor == -1 && j>0) {
          for (i=0;i<10;i++) {
            if (tabuleiro[i] == j) {
              posicaoValorMenor = i;  
		    }
	      }
	      j--;
	    }
        for (i=0;i<10;i++) {
          if (tabuleiro[i] == 6) {
            posicaoValorMaior = i;
	      }
	    }
	    if (posicaoValorMenor != -1 && posicaoValorMaior != -1 && posicaoValorMaior == 9) {  
          for (i=posicaoValorMenor+1;i<posicaoValorMaior;i++) {
            if (tabuleiro[i] == 0) {
		      temPosicaoNaoP = true;  
		      break;
		    }
	      }
	      if (!temPosicaoNaoP) {
	        tabuleiroOk = false;
	      }
	    } else if (posicaoValorMenor != -1 && posicaoValorMaior == -1) {
	      for (i=posicaoValorMenor+1;i<10;i++) {
            if (tabuleiro[i] == 0) {
		      temPosicaoNaoP = true;  
		      break;
		    }
	      }
	      if (!temPosicaoNaoP) {
	        tabuleiroOk = false;
	      }	
	    }
        break;
    }
  }
  return tabuleiroOk;
}

bool verificaValorDigitado(int valorDigitado,int tabuleiro[])
{
  if (valorDigitado>10 || valorDigitado<=0) {
    return false;
  }

  if (tabuleiro[valorDigitado-1]!=0) {
    return false;
  } 
  return true;
}

int main()
{
  int i,valorDado,valorDigitado,j;
  int tabuleiro[10];
  bool perdeu;
  //Funcao colocada abaixo para gerar o valor do dado de forma aleatoria. Sem a funcao, o dado gera quase sempre o mesmo valor.
  srand(time(NULL));
  
  for (i=0;i<10;i++) {
    tabuleiro[i] = 0;
  }
  
  printf("Objetivo do jogo: \n");
  printf("Voce deve preencher um tabuleiro de 10 posicoes com numeros lancados de um dado\n");
  printf("de modo que o tabuleiro fique com uma ordem nao decrescente.\n");
  printf("--------------------------------------------------------------------------------------\n");
  
  for (i=0;i<10;i++) {
    valorDado = dado();
    printf("O valor do dado nesse momento eh %d.\n",valorDado);
    printf("--------------------------------------------------------------------------------------\n");
  	printf("TABULEIRO:\n");
  	for (j=0;j<10;j++) {
  	  if (tabuleiro[j] == 0) {
  	    printf("Posicao %2d - NAO PREENCHIDA\n",j+1);
	  } else {
	  	printf("Posicao %2d - %d\n",j+1,tabuleiro[j]);	
	  }      	
	}
	
	printf("--------------------------------------------------------------------------------------\n");
	
	if (!verificaTabuleiro(valorDado,tabuleiro)) {
	  printf("Nao eh possivel preencher o tabuleiro em ordem nao decrescente com o valor do dado %d.\nVoce perdeu!",valorDado);
 	  perdeu = true; 
      break;
	}
	
	printf("Em qual posicao nao preenchida do tabuleiro voce quer colocar o valor do dado? ");
	scanf("%d",&valorDigitado);

	
	while (!verificaValorDigitado(valorDigitado,tabuleiro)) {
	  printf("Digite uma posicao nao preenchida para colocar o valor do dado: ");
	  scanf("%d",&valorDigitado);
	}

	printf("\n-------------------------------------------------------------------------------------\n");
	valorDigitado--;
	tabuleiro[valorDigitado] = valorDado;
	
	perdeu = false;
	for (j=0;j<valorDigitado;j++) {
	  if (tabuleiro[j] > tabuleiro[valorDigitado]) {
	    printf("Algum valor anterior da posicao escolhida eh maior.\nVoce perdeu.");
	    perdeu = true;
	    break;
	  }	
	}
	
	for (j=valorDigitado;j<10;j++) {
	  if (tabuleiro[j] != 0 && tabuleiro[j] < tabuleiro[valorDigitado]) {
	    printf("Algum valor posterior da posicao escolhida eh menor.\nVoce perdeu.");
	    perdeu = true;
	    break;
	  }	
	}
	
	if (perdeu) {
	  break;
	}
  }
  if (!perdeu) {
    printf("Voce ganhou. Parabens!\n");
    for (j=0;j<10;j++) {
	  printf("Posicao %2d - %d\n",j+1,tabuleiro[j]);      	
	} 
  }
  return 0;  
}
