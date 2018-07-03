#include <stdio.h>
#include <stdlib.h>

int main(){
    int l, c, p;
	int i,j,k;
	printf("informe prof: ");
	scanf("%d", &p);
	printf("informe col: ");
	scanf("%d", &c);
	printf("informe lin: ");
	scanf("%d", &l);

// alocar
  int ***mat=malloc(p*sizeof(int **));
	for(i=0;i<p;i++){
		mat[i]=malloc(l*sizeof(int *));
		for(j=0;j<l;j++){
		    mat[i][j]=malloc(c*sizeof(int));
		}
	}

// ler
	for(i=0;i<p;i++){
		mat[i]=malloc(l*sizeof(int *));
		for(j=0;j<l;j++){
		    mat[i][j]=malloc(c*sizeof(int));
			for(k=0;k<c;k++){
				printf("informe o valor de mat[%i][%i][%i]: ", i,j,k);
				scanf("%d", &mat[i][j][k]);
			}
		}
	}

// imprimir
	for(i=0;i<p;i++){
		for(j=0;j<l;j++){
			for(k=0;k<c;k++){
				printf("%i\t", mat[i][j][k]);
			}
		    printf("\n");
		}
	    printf("\n");
	}
    printf("\n");

}
