#include <stdio.h>
#include <stdlib.h>

int fatorial(int n) {
  if (n==0) {
    return 1;
  } else {
    return n*fatorial(n-1);
  }
}

int fibonacci(int n) {
  if (n == 2 || n == 3) 
    return 1;
  else 
    return fibonacci(n-1) + fibonacci(n-2);
}

int soma(int n) {
  if (n==1) {
    return n;
  } else {
    return n+soma(n-1);
  }
}

int main() {
  int fat = fatorial(4);


  printf("%d\n", fibonacci(12));
  printf("%d\n", soma(4));
}