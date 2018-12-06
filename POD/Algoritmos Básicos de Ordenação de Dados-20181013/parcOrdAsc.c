/*
* Ordenador parcial baseado no Shell Sort
* Este programa gera uma saida parcialmente ordenada em ordem ascendente
* Parametros: número elementos a serem lidos da entrada padrão
*/

#include <stdio.h>
#include <stdlib.h>

void imprime(int *vetor, int tam){
  int cont;
  for(cont=0; cont<tam; cont++)
	printf("%d\n", vetor[cont]);
  return;
}

int *parcOrd(int *vet, int tam){
  int i, j, k=0, temp;
  int gaps[8]={701,301,132,57,23,10,4};
  while (gaps[k] > ((tam/2)-1))
	k++;
  while( gaps[k] >= 1 ){
    for(i = gaps[k]; i<tam; i++){
	temp = vet[i];
        j = i - gaps[k];
	while( j >= 0 && temp < vet[j]){
		vet[j+gaps[k]] = vet[j];
		j -= gaps[k];
	}
	vet[j+gaps[k]] = temp;
    }
    k++;
  }
  return vet;
}

main(int argc, char *argv[]){
  int  i;
  int *vet;
  char linha[16];
  int tamVet;
  int maior = -1;

  if(argc < 2){
    printf("Uso: %s <numero de elementos a ordenar>\n", argv[0]);
    exit(0);
  }
  tamVet = atoi(argv[1]);
  vet = (int *) malloc(sizeof(int) * tamVet);

  for(i=0; i<tamVet; i++){
	fgets(linha, 16, stdin);
	sscanf(linha, "%d", &vet[i]);
	if(vet[i] > maior)
		maior = vet[i];
  }

  parcOrd(vet, tamVet);
  imprime(vet, tamVet);

  exit(0);
}
