#include <stdio.h>
#include <string.h>
#include <math.h>

int main(){
  
  char palavra1[10];
  char palavra2[10];

  strcpy(palavra1,"aab122");
  strcpy(palavra2,"aaa1221");
  printf("%d\n", strcmp(palavra1,palavra2));
}