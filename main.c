#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers/macro.h"
#include "headers/teste.h"

int main()
{
    // Define a semente do sorteio, utilizando o tempo do sistema em milisegundos.
    srand((unsigned) time(NULL));
    Populacao* inicial = populacaoInicial();

    if (!inicial)
    {
        printf("Memoria insuficiente!\n");
        return 1;
    }

    printf("Populacao inicial\n");
    imprimirPopulacao(inicial);

    Populacao** populacoes = inicializar();

    if (!populacoes)
    {
        printf("Memoria insuficiente!\n");
        return 1;
    }

    populacoes[0] = novaPopulacao(inicial);

    int i;

    for (i = 1; i < MAX_POPULACAO; i++)
        populacoes[i] = novaPopulacao(populacoes[i - 1]);

    for (i = 0; i < MAX_POPULACAO; i++)
    {
        printf("Populacao %d\n", i + 1);
        imprimirPopulacao(populacoes[i]);
    }

    destruirPopulacao(&inicial);

    if (populacoes)
    {
        free(populacoes);
        populacoes = NULL;
    }

    system("pause");
    return 0;
}
