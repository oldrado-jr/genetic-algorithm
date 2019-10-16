#ifndef AG_H_INCLUDED
#define AG_H_INCLUDED

// Definições dos protótipos das funções para o Algoritmo Genético.

// Inclui o arquivo das definições de uma população.
#include "populacao.h"

int* mutacao(int*);
Individuo* modelar(Individuo*);
Populacao* crossover(Individuo*, Individuo*, Populacao*);
Individuo* torneio(Populacao*);
int* transferirGenes(int*, int*, int*, int);

#endif // AG_H_INCLUDED
