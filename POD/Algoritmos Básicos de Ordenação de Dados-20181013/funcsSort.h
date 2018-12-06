#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <sys/time.h>


void mostra(int *vetor, int tam);
double difTempo(struct timespec t0, struct timespec t1);
int *embaralha(int *vetor, int tam);

