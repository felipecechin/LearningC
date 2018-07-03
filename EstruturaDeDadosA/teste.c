#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int main(){
  
  // char palavra1[10];
  // char palavra2[10];

  // strcpy(palavra1,"aab122");
  // strcpy(palavra2,"aaa1221");
  // printf("%d\n", strcmp(palavra1,palavra2));

  // char x[256];
  // char letra[2];
  // int codAscii = 97;
  // letra[0] = codAscii;
  // letra[1] = 0;
  // int i,j;
  // strcpy(x,"");
  // for(i=1;i<20;i++) {
  //     for(j=0;j<i%254;j++){
  //         strcat(x, letra);
  //         printf("x:%s\n",x);
  //     }
  //     letra[0]++;
  //     strcpy(x,"");
  // 
  srand(time(NULL));
  int num = rand()%2147483647;
  printf("%011d\n",num);
  return 0;
}