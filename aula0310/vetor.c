#include <stdio.h>
#define TAM 4

int main(void)
{
  int v[TAM];
  int i;
  
  for (i=0;i<TAM;i++) {
    scanf("%d",&v[i]);
  }
  
  int s = 0;
  for (i=0;i<TAM;i++) {
    s = s + v[i];
  }
  float m;
  m = (float) s/TAM;
  for (i=0;i<TAM;i++) {
    if (v[i]> m) {
      printf("%d ",v[i]);
	}
  }

}
