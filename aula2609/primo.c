#include <stdio.h>
#include <stdbool.h>

bool primo(int n)
{
  int i;
  for (i =2;i<n;i++) {
    if (n%i==0) return false;
  }
  return true;
}

main()
{
  int i;
  for (i=1;i<1000;i++) {
    if (primo(i)) {
      printf("%d  ",i);
    }
  }
}
