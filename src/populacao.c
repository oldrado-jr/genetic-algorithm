#include <stdio.h>
#include <stdlib.h>
#include "../headers/macro.h"
#include "../headers/populacao.h"

// Função para criar uma população, devidamente inicializada, retornando a referência da mesma.
Populacao* criarPopulacao()
{
    Populacao* populacao = (Populacao*) malloc(sizeof(Populacao));

    if (populacao)
    {
        populacao->individuos = (Individuo**) malloc(sizeof(Individuo*[MAX_INDIVIDUOS]));

        if (populacao->individuos)
        {
            int i;

            for (i = 0; i < MAX_INDIVIDUOS; i++)
                populacao->individuos[i] = NULL;
        }

        populacao->somatorioFitness = 0;
    }

    return populacao;
}

/* Função para adicionar um indivíduo em uma população. Recebe como
 * parâmetros o indivíduo a ser incluído e a população onde ele será
 * inserido. A função retorna a referência da população, com o indivíduo
 * devidamente adicionado.
 */
Populacao* adicionarIndividuo(Individuo* individuo, Populacao* populacao)
{
    if (populacao)
    {
        if (populacao->individuos)
        {
            int i;

            for (i = 0; i < MAX_INDIVIDUOS && populacao->individuos[i]; i++)
                ;

            populacao->individuos[i] = individuo;
        }

        populacao->somatorioFitness += individuo->fitness;
    }

    return populacao;
}

/* Função para procurar valores de X e Y dentro da população. Recebe como
 * parâmetros os valores a serem procurados e a população onde será feita
 * a busca. A função retorna 1 se encontrar pelo menos um dos valores na
 * população ou 0, caso contrário.
 */
int buscarNaPopulacao(int x, int y, Populacao* populacao)
{
    if (populacao)
    {
        if (populacao->individuos)
        {
            int i;

            for (i = 0; i < MAX_INDIVIDUOS && populacao->individuos[i]; i++)
                if (populacao->individuos[i]->x == x && populacao->individuos[i]->y == y)
                    return 1;
        }
    }

    return 0;
}

/* Procedimento para imprimir os dados da população. Recebe como
 * parâmetro a população, cujos dados serão exibidos.
 */
void imprimirPopulacao(Populacao* populacao)
{
    if (populacao)
    {
        int i;

        printf("----------------------------------\n");

        for (i = 0; i < MAX_INDIVIDUOS; i++)
            imprimirIndividuo(populacao->individuos[i]);


        printf("Somatorio fitness da populacao: %d\n", populacao->somatorioFitness);
        printf("----------------------------------\n");
    }
}

/* Procedimento para destruir uma população. Recebe como parâmetro a
 * população a ser destruída, liberando todos os recursos utilizados.
 */
void destruirPopulacao(Populacao** populacao)
{
    if (*populacao)
    {
        if ((*populacao)->individuos)
        {
            free((*populacao)->individuos);
            (*populacao)->individuos = NULL;
        }

        free(*populacao);
        *populacao = NULL;
    }
}
