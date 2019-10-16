#ifndef POPULACAO_H_INCLUDED
#define POPULACAO_H_INCLUDED

// Definições da estrutura e dos protótipos das funções para uma população.

// Inclui o arquivo das definições de um indivíduo.
#include "individuo.h"

typedef struct T_Populacao
{
    Individuo** individuos;  // Array de indivíduos.
    int somatorioFitness;  // Somatório da função fitness de toda população.
} Populacao;

Populacao* criarPopulacao();
Populacao* adicionarIndividuo(Individuo*, Populacao*);
int buscarNaPopulacao(int, int, Populacao*);
void imprimirPopulacao(Populacao*);
void destruirPopulacao(Populacao**);

#endif // POPULACAO_H_INCLUDED
