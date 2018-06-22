#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "tela.h"

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

float distancia(ponto a, ponto b)
{
  float dx, dy;
  dx = a.x - b.x;
  dy = a.y - b.y;
  return sqrt(dx*dx + dy*dy);
}

bool ponto_dentro_do_circulo(ponto p, circulo c)
{
  return distancia(p, c.centro) < c.raio;
}

// retorna o primeiro inimigo acertado pela bala, ou NULL se errou de todos.
// inimigos é um vetor com n_inimigos elementos.
circulo *acertou(circulo *inimigos, int n_inimigos, ponto bala)
{
  circulo *inimigo;
  // para cada inimigo no vetor
  for (inimigo = inimigos; inimigo < &inimigos[n_inimigos]; inimigo++) {
  //  se bala acerta o inimigo
    if (ponto_dentro_do_circulo(bala, *inimigo)) {
  //   retorna o inimigo acertado
      return inimigo;
    }
  }
  // nao acertou ninguem, returna NULL
  return NULL;
}

void explode_inimigo(circulo *c)
{
  c->raio = 0;
}

void move_bala(ponto *bala)
{
  bala->y -= 3;
  if (bala->y <= 10) {
    bala->x = rand()%400+20;
    bala->y = 550;
  }
}

void desenha_tela(circulo *inimigos, int n_inimigos, ponto bala)
{
  tela_inicia_desenho();
  int i;
  for (i=0; i<n_inimigos; i++) {
    if (inimigos[i].raio > 0) {
      tela_circulo(inimigos[i].centro.x, inimigos[i].centro.y, inimigos[i].raio,
                   2, azul, inimigos[i].cor);
    }
  }
  tela_circulo(bala.x, bala.y, 3, 1, verde, vermelho);
  tela_termina_desenho();
}

void move_inimigos(circulo *inimigos, int n_inimigos)
{
  int i;
  for (i=0; i<n_inimigos; i++) {
    inimigos[i].centro.x += inimigos[i].dx;
    if (inimigos[i].centro.x < 10 || inimigos[i].centro.x > 390) {
      inimigos[i].dx *= -1;
    }
    inimigos[i].centro.y += inimigos[i].dy;
    if (inimigos[i].centro.y < 10 || inimigos[i].centro.y > 550) {
      inimigos[i].dy *= -1;
    }
  }
}
  

int main(void)
{
  srand(time(0));
  tela_inicio(440, 600, "bala nos inimigos!!!");
  int n_inim = 10;
  circulo inimigos[10];
  int i;
  for (i=0; i<10; i++) {
    inimigos[i].centro.x = rand()%400+20;
    inimigos[i].centro.y = rand()%500+50;
    inimigos[i].raio = rand()%20+5;
    inimigos[i].cor = rand()%10;
    inimigos[i].dx = (rand()%100-50)/10.0;
    inimigos[i].dy = (rand()%100-50)/10.0;
  }
  ponto bala = {200, 550};
  circulo *in;
  while (true) {
    desenha_tela(inimigos, n_inim, bala);
    in = acertou(inimigos, n_inim, bala);
    if (in!=NULL) {
      explode_inimigo(in);
      bala.y = 0;
    }
    move_bala(&bala);
    move_inimigos(inimigos, n_inim);
  }
  tela_fim();
  return 0;
}
