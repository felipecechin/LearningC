#include <stdio.h>

float diag(float m[3][3],int c)
{
  return m[0][c]*m[1][(c+1)%3]*m[2][(c+2)%3];
}

float diag2(float m[3][3], int c)
{
  return m[0][c]*m[1][(c+2)%3]*m[2][(c+1)%3];
}

main()
{
  float m[3][3],d;
  int i,j;
  for(i=0;i<3;i++) {
    for(j=0;j<3;j++) {
      scanf("%f",&m[i][j]);
	}
  }
  
  d = diag(m,0) + diag(m,1) + diag(m,2)
      -diag2(m,0) - diag2(m,1) - diag2(m,2);
  
  printf("%f",d);
}
