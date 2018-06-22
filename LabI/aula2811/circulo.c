#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>



typedef struct {
  float x;
  float y;
} ponto;

typedef struct {
  ponto centro;
  float raio;
  int cor;
  float dx;
  float dy;
} circulo;

float distancia(ponto a,ponto b)
{
  float dx,dy;
  dx = a.x - b.x;
  dy = a.y - b.y;
  return sqrt(dx*dx + dy*dy);
}

bool ponto_dentro_do_circulo(ponto p,circulo c) 
{
  return distancia(p,c.centro) <= c.raio;
}

circulo *acertou(circulo *inimigos,int n_inimigos,ponto bala)
{
  circulo *inimigo;
  // int i;
  // inimigo = inimigos;
  // for (i=0;i<n_inimigos,i++) {
  //   if (ponto_dentro_do_circulo(bala,*inimigo)) {
  //     return inimigo;
  //   }
  //   inimigo++;
  // }
  for (inimigo = inimigos;inimigo<&inimigos[n_inimigos];inimigo++) {
    if (ponto_dentro_do_circulo(bala,*inimigo)) {
      return inimigo;
    }
  }

  return NULL;
}

void explode_inimigo(circulo *c)
{
  c->raio = 0;
}

void move_bala(ponto *bala)
{
  bala->y -= 3;
  if (bala->y<=10) {
    bala->x = rand()%400+20;
    bala->y = 650;
  }
}

void move_inimigos(circulo *inimigos,int n_inimigos) 
{
  int i;
  for (i=0;i<n_inimigos;i++) {
    inimigos[i].centro.x += inimigos[i].dx;
    if (inimigos[i].centro.x<10 || inimigos[i].centro.x>390) {
      inimigos[i].dx *= -1;
    }
  }
  for (i=0;i<n_inimigos;i++) {
    inimigos[i].centro.y += inimigos[i].dy;
    if (inimigos[i].centro.y<10 || inimigos[i].centro.y>550) {
      inimigos[i].dy *= -1;
    }
  }
}

void desenha_tela(circulo *inimigos,int n_inimigos,ponto bala)
{
  tela_inicia_desenho();
  int i;
  for (i=0;i<n_inimigos;i++) {
    if (inimigos[i].raio>0) {
      tela_circulo(inimigos[i].centro.x,inimigos[i].centro.y,inimigos[i].raio,
                   2,azul,inimigos[i].cor);
    }
  }
  tela_circulo(bala.x,bala.y,3,1,verde,vermelho);
  tela_termina_desenho();
}

main()
{
  srand(time(NULL));
  tela_inicio(440,600,"oiii");
  int n_inim = 10;
  circulo inimigos[10];
  int i;
  for (i=0;i<10;i++) {
    inimigos[i].centro.x = rand()%400+20;
    inimigos[i].centro.y = rand()%500+50;
    inimigos[i].raio = rand()%20+5;
    inimigos[i].cor = rand()%10+1;
    inimigos[i].dx = (rand()%100-50)/10.0;
  }
  ponto bala = {200,550};
  circulo *i;
  while (true) {
    desenha_tela(inimigos,n_inim,bala);
    i = acertou(inimigos,n_inim,bala);
    if (i!=NULL) {
      explode_inimigo(i);
      bala.y = 0;
    }
    move_bala(&bala);
    move_inimigos()
  }
  tela_fim();
  return 0;

}