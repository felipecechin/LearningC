#include <stdlib.h>
#include <string.h>
#include <iostream>
#define QUANT 30

using namespace std;
//http://www.cplusplus.com/reference/cstdlib/atoi/
//STRING -> INT
void CharToInt(char string[], int strint[]){
    int i;
    for(i=0;i<QUANT;i++){
        strint[i] = atoi (string[i]);
    }
}

//http://www.cplusplus.com/reference/cstdlib/itoa/
//INT -> STRING
void IntToChar(int strint[], char string[]){
    int i;
    for(i=0;i<QUANT;i++){
        itoa (strint[i],string[i],10);
    }
}

//Ordena na ordem cresente a string de INT
void Ord(int strint[]){
    int i,j,aux;
    for(i=0;i<strlen(strint);i++){
        for(j=i+1;j<strlen(strint);j++){
            if(strint[i]>strint[j]){
                aux = strint[i];
                strint[i] = strint[j];
                strint[j] = aux;
            }
        }
    }
}

main(){
    char string[QUANT];
    int strint[QUANT];

    printf("Escreva o seu nome:\n");
    fgets(string,30,stdin);
    strupr(string);
    printf("Nome: %s\n",string);

    CharToInt(string,strint);
    Ord(strint);
    IntToChar(strint,string);
    printf("Nome: %s\n",string);

    return(0);
}