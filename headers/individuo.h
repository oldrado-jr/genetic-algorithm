#ifndef INDIVIDUO_H_INCLUDED
#define INDIVIDUO_H_INCLUDED

// Definições da estrutura e dos protótipos das funções para um indivíduo.

typedef struct T_Individuo
{
    int x;           // Valor de X.
    int y;           // Valor de Y;
    int negativoX;   // Valor para definir se o valor de X é negativo ou não.
    int negativoY;   // Valor para definir se o valor de Y é negativo ou não.
    int fitness;     // Valor da função fitness.
    int *genesX;     // Array para representar os genes X do indivíduo.
    int *genesY;     // Array para representar os genes Y do indivíduo.
    int *cromossomo; // Array para representar o cromossomo do indivíduo.
} Individuo;

Individuo *criarIndividuo();
int *criarGenes(int);
Individuo *configurarIndividuo(int, int, Individuo *);
Individuo *atualizarIndividuo(Individuo *);
int *atualizarCromossomo(Individuo *);
int calcularFitness(int, int);
void imprimirIndividuo(Individuo *);
void destruirGenes(int **);
void destruirIndividuo(Individuo **);

#endif // INDIVIDUO_H_INCLUDED
