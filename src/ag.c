#include <stdlib.h>
#include "../headers/conversor.h"
#include "../headers/macro.h"
#include "../headers/ag.h"

/* Função para realizar mutação dos genes de um indivíduo. Recebe
 * como parâmetro os genes a sofrerem mutação. Cada gene tem
 * probabilidade de 1% de sofrer mutação, ou seja, de um bit ser
 * alterado. A função retorna a referência dos genes já alterados.
 */
int* mutacao(int* genes)
{
    if (genes)
    {
        const float PROB_MUTACAO = 0.01;
        int i;

        for (i = 0; i < MAX_GENES; i++)
        {
            float prob = (float) rand() / RAND_MAX;  // Sorteia um valor entre 0 e 1.

            if (prob < PROB_MUTACAO)
                genes[i] = genes[i] == 0 ? 1 : 0;
        }
    }

    return genes;
}

/* Função para modelar um indivíduo após o crossover, mantendo-o dentro
 * das restrições. Recebe como parâmetro o indivíduo a ser modelado e,
 * em seguida, retorna-se a referência do mesmo.
 */
Individuo* modelar(Individuo* individuo)
{
    individuo->genesX = mutacao(individuo->genesX);
    int dec = binToDec(individuo->genesX, individuo->negativoX);

    // Evita que o valor de X fique fora do intervalo determinado previamente.
    if (dec >= MAX_INTERVALO)
        individuo->negativoX = 1;
    else if (dec <= -MAX_INTERVALO || dec == 0)
        individuo->negativoX = 0;

    individuo->genesY = mutacao(individuo->genesY);
    dec = binToDec(individuo->genesY, individuo->negativoY);

    // Evita que o valor de Y fique fora do intervalo determinado previamente.
    if (dec >= MAX_INTERVALO)
        individuo->negativoY = 1;
    else if (dec <= -MAX_INTERVALO || dec == 0)
        individuo->negativoY = 0;

    return individuo;
}

/* Função para realizar o crossover entre dois indivíduos pré-selecionados.
 * Recebe como parâmetros os indivíduos que vão gerar novos descendentes.
 * O crossover tem 60% de chances de ocorrer, ou seja, haverá troca de genes
 * entre os pais para gerar novos filhos. Caso contrário, os filhos serão
 * simplesmente cópias de seus pais. A função retorna a referência de uma
 * população, contendo os dois novos indivíduos na mesma.
 */
Populacao* crossover(Individuo* pai1, Individuo* pai2, Populacao* populacao)
{
    if (pai1 && pai2 && populacao)
    {
        if (pai1->cromossomo && pai2->cromossomo)
        {
            const float PROB_CROSSOVER = 0.6;
            int i, corte;
            Individuo* filho;

            /* Em ambos os casos, a combinação será feita duas vezes: pai1 e pai2, e depois,
             * pai2 e pai1. Cada combinação terá uma certa probabilidade de ser um crossover.
             */
            float prob = (float) rand() / RAND_MAX;

            if (prob < PROB_CROSSOVER)
            {
                for (i = 0; i < MAX_FILHOS; i++)
                {
                    filho = criarIndividuo();

                    if (filho)
                    {
                        if (i == 0)
                        {
                            corte = rand() % MAX_CORTES;
                            filho->genesX = transferirGenes(pai1->genesX, pai2->genesX, filho->genesX, corte);
                            filho->genesY = transferirGenes(pai1->genesY, pai2->genesY, filho->genesY, corte);
                        }
                        else
                        {
                            filho->genesX = transferirGenes(pai2->genesX, pai1->genesX, filho->genesX, corte);
                            filho->genesY = transferirGenes(pai2->genesY, pai1->genesY, filho->genesY, corte);
                        }

                        filho = modelar(filho);
                        filho = atualizarIndividuo(filho);
                        populacao = adicionarIndividuo(filho, populacao);
                    }
                }
            }
            else
            {
                for (i = 0; i < MAX_FILHOS; i++)
                {
                    filho = criarIndividuo();

                    if (filho)
                    {
                        // Nesse caso, como os filhos serão clones dos pais, então terão o mesmo sinal.
                        if (i == 0)
                        {
                            filho->genesX = pai1->genesX;
                            filho->genesY = pai1->genesY;
                            filho->negativoX = pai1->negativoX;
                            filho->negativoY = pai1->negativoY;
                        }
                        else
                        {
                            filho->genesX = pai2->genesX;
                            filho->genesY = pai2->genesY;
                            filho->negativoX = pai2->negativoX;
                            filho->negativoY = pai2->negativoY;
                        }

                        filho = modelar(filho);
                        filho = atualizarIndividuo(filho);
                        populacao = adicionarIndividuo(filho, populacao);
                    }
                }
            }
        }
    }

    return populacao;
}

/* Função para realizar uma seleção por torneio entre dois indivíduos da população,
 * escolhidos aleatoriamente. Recebe como parâmetro a população onde será feito o
 * torneio. A função retorna o indivíduo que possuir o melhor índice fitness.
 */
Individuo* torneio(Populacao* populacao)
{
    Individuo *candidato1, *candidato2;
    candidato1 = populacao->individuos[rand() % MAX_INDIVIDUOS];

    do
        candidato2 = populacao->individuos[rand() % MAX_INDIVIDUOS];
    while (candidato1 == candidato2);  // Evita que o mesmo candidato seja sorteado.

    return candidato1->fitness > candidato2->fitness ? candidato1 : candidato2;
}

/* Função para copiar genes dos pais para o filho. Recebe como parâmetros
 * os genes dos pais, a referência dos genes do filho, onde serão armazenados
 * e a posição do corte. A função retorna a referência dos genes do filho,
 * devidamente preenchido.
 */
int* transferirGenes(int* genesPai1, int* genesPai2, int* genesFilho, int corte)
{
    if (genesPai1 && genesPai2 && genesFilho)
    {
        int i;

        for (i = 0; i < MAX_GENES; i++)
            genesFilho[i] = i <= corte ? genesPai1[i] : genesPai2[i];
    }

    return genesFilho;
}
