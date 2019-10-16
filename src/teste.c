#include <stdlib.h>
#include "../headers/teste.h"
#include "../headers/ag.h"
#include "../headers/macro.h"

// Função para inicializar um array de populações, retornando a respectiva referência.
Populacao** inicializar()
{
    Populacao** populacoes = (Populacao**) malloc(sizeof(Populacao*[MAX_POPULACAO]));

    if (populacoes)
    {
        int i;

        for (i = 0; i < MAX_POPULACAO; i++)
            populacoes[i] = NULL;
    }

    return populacoes;
}

// Função para criar a população inicial, retornando a respectiva referência.
Populacao* populacaoInicial()
{
    Populacao* populacao = criarPopulacao();

    if (populacao)
    {
        int i;

        for (i = 0; i < MAX_INDIVIDUOS; i++)
        {
            Individuo* individuo = criarIndividuo();

            if (individuo)
            {
                int x, y;

                do
                {
                    x = rand() % QTD_ELEMENTOS - MAX_INTERVALO;
                    y = rand() % QTD_ELEMENTOS - MAX_INTERVALO;
                }
                while (buscarNaPopulacao(x, y, populacao));  // Evita o sorteio de dois números iguais.

                individuo = configurarIndividuo(x, y, individuo);
                populacao = adicionarIndividuo(individuo, populacao);
            }
        }
    }

    return populacao;
}

/* Função que gera uma nova população, recebendo como parâmetro a população antecessora
 * e retornando o resultado do crossover entre dois indivíduos selecionados.
 */
Populacao* novaPopulacao(Populacao* antecessora)
{
    const int MAX_SELECAO = MAX_INDIVIDUOS / 2;
    int i;
    Individuo *pai1, *pai2;
    Populacao* nova = criarPopulacao();

    for (i = 0; i < MAX_SELECAO; i++)
    {
        pai1 = torneio(antecessora);

        do
            pai2 = torneio(antecessora);
        while (pai1 == pai2);  // Evita que o mesmo indivíduo seja escolhido.

        nova = crossover(pai1, pai2, nova);
    }

    return nova;
}
