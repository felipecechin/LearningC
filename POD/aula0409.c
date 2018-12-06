#include <stdio.h>
#include <stdlib.h>

void main(int argc, char ** argv) {
  int n,i;

  n = (int) atoi(argv[1]);
  for (i=0;i<n;i++) {
    fprintf(stdout,"%ld ",random()%n);
  }

  fprintf(stdout, "\n");
}