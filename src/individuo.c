#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../headers/individuo.h"
#include "../headers/macro.h"
#include "../headers/conversor.h"

// Função para criar um indivíduo, devidamente inicializado, retornando a referência do mesmo.
Individuo *criarIndividuo() {
    Individuo *individuo = (Individuo *)malloc(sizeof(Individuo));

    if (!individuo)
        return NULL;

    individuo->x = MAX_INTERVALO + 1; // X é iniciado com um valor fora do intervalo.
    individuo->y = MAX_INTERVALO + 1; // Y é iniciado com um valor fora do intervalo.
    individuo->negativoX = 0;
    individuo->negativoY = 0;
    individuo->fitness = 0;
    individuo->genesX = criarGenes(MAX_GENES);
    individuo->genesY = criarGenes(MAX_GENES);
    individuo->cromossomo = criarGenes(MAX_CROMOSSOMO);

    return individuo;
}

/* Função para criar um array inicializado de genes. Recebe como parâmetro o tamanho
 * do array e retorna uma referência do mesmo.
 */
int *criarGenes(int tamanho) {
    int *genes = (int *)malloc(sizeof(int[tamanho]));

    if (!genes)
        return NULL;

    for (int i = 0; i < tamanho; i++)
        genes[i] = -1;

    return genes;
}

/* Função para configurar um indivíduo, a partir do valor de X.
 * Recebe como parâmetros os valores de X e Y, previamente sorteados
 * e o indivíduo que será configurado. A função retorna a referência
 * do indivíduo, devidamente configurado.
 */
Individuo *configurarIndividuo(int x, int y, Individuo *individuo) {
    if (!individuo)
        return NULL;

    individuo->x = x;
    individuo->y = y;
    individuo->negativoX = x < 0;
    individuo->negativoY = y < 0;
    individuo->fitness = calcularFitness(individuo->x, individuo->y);

    if (individuo->genesX)
        individuo->genesX = decToBin(individuo->x, individuo->genesX);

    if (individuo->genesY)
        individuo->genesY = decToBin(individuo->y, individuo->genesY);

    individuo->cromossomo = atualizarCromossomo(individuo);

    return individuo;
}

/* Função para atualizar um indivíduo. Recebe como parâmetro a
 * referência do indivíduo, retornando-o devidamente atualizado.
 */
Individuo *atualizarIndividuo(Individuo *individuo) {
    if (!individuo)
        return NULL;

    individuo->x = binToDec(individuo->genesX, individuo->negativoX);
    individuo->y = binToDec(individuo->genesY, individuo->negativoY);
    individuo->fitness = calcularFitness(individuo->x, individuo->y);
    individuo->cromossomo = atualizarCromossomo(individuo);

    return individuo;
}

/* Função para atualizar um cromossomo. Recebe como parâmetro a
 * referência do indivíduo, retornando-o com o cromossomo
 * devidamente atualizado.
 */
int *atualizarCromossomo(Individuo *individuo) {
    if (!individuo->cromossomo)
        return NULL;

    for (int i = 0; i < MAX_CROMOSSOMO; i++) {
        int j = i % MAX_GENES;
        individuo->cromossomo[i] = i < MAX_GENES ? individuo->genesX[j] : individuo->genesY[j];
    }

    return individuo->cromossomo;
}

/* Função para calcular a função fitness do indivíduo. Recebe como
 * parâmetros os valores de X e Y do indivíduo. A função retorna o
 * resultado da função fitness do mesmo.
 */
int calcularFitness(int x, int y) {
    return pow(x, 2) - pow(y, 2) + 2 * x * y - 5;
}

/* Procedimento para imprimir os dados de um indivíduo. Recebe como
 * parâmetro o indivíduo cujos dados serão exibidos.
 */
void imprimirIndividuo(Individuo *individuo) {
    if (!individuo)
        return;

    printf("X: %d\n", individuo->x);
    printf("Y: %d\n", individuo->y);
    printf("Fitness: %d\n", individuo->fitness);
    printf("Cromossomo (X e Y): ");

    for (int i = 0; i < MAX_CROMOSSOMO; i++)
        printf("%d ", individuo->cromossomo[i]);

    printf("\n\n");
}

/* Procedimento para destruir os genes de um indivíduo. Recebe como
 * parâmetro os genes a ser destruído, liberando todos os recursos
 * utilizados.
 */
void destruirGenes(int **genes) {
    if (!(*genes))
        return;

    free(*genes);
    *genes = NULL;
}

/* Procedimento para destruir um indivíduo. Recebe como parâmetro o
 * indivíduo a ser destruído, liberando todos os recursos utilizados.
 */
void destruirIndividuo(Individuo **individuo) {
    if (!(*individuo))
        return;

    destruirGenes(&(*individuo)->genesX);
    destruirGenes(&(*individuo)->genesY);
    destruirGenes(&(*individuo)->cromossomo);
    free(*individuo);
    *individuo = NULL;
}
