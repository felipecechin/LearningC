#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>

float distancia(float x1, float y1, float x2, float y2) 
{
  float c1, c2;
  c1 = x1-x2;
  c2 = y1-y2;
  return sqrt(c1*c1 + c2*c2); 
}

bool dentro(float xc, float yc, float r, float xp, float yp)
{
  return distancia(xp,yp,xc,yc) < r;
}

int main(void)
{
  float x=-90;
  float y=-40;
  float r=1;

  for (;;) {
    if (dentro(0,0,r,x,y)) {
  	  printf("*");	
	} else {
	  printf(".");
	}
	x = x + 3;
	if (x >= 90) {
	  y = y+4;
	  x = -90;
	  printf("\n");
	  if (y >= 40) {
	  	break;
//	  	r = r+1;
//	  	if (r>90) {
//	  	  break;
//	    }
//	    x = -90;
//	    y = 40;
//	    usleep(1000000/24);
	    //printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	  }
	}
  }
  
  return 0;
}
