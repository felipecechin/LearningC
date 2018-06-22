#include<unistd.h> 
#include <stdio.h>
#include <time.h>

int main(void)
{
    
    time_t start = time(NULL);
    sleep(72);
    time_t diff = time(NULL) - start;
    int segundos = (int)diff;
    if (segundos>=60) {
      int minutos = segundos/60;
      while(segundos>=60) {
        segundos = segundos - 60;
      }
      if (segundos != 0) {
        printf("Tempo de jogo:%d min %d s.\n",minutos,segundos);
      } else {
        printf("Tempo de jogo:%d min.\n",minutos);
      }
    } else {
      printf("Tempo de jogo:%d s.\n",segundos);
    }
}