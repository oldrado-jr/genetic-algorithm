#include <math.h>
#include "../headers/macro.h"
#include "../headers/conversor.h"

/* Função para converter um número em decimal para um número em binário.
 * Recebe como parâmetros o número em decimal a ser convertido e a
 * referência do array onde sua representação em binário será armazenada.
 * A função retorna a representação do número em binário.
 */
int* decToBin(int dec, int* bin)
{
    int i;

    /* Se o número for negativo, então procura-se pelo seu "reflexo"
     * positivo. Ex: O nº -10 tem como "reflexo" o nº 6, pois ambos têm
     * a mesma representação binária., desconsiderando o bit de sinal.
     */
    if (dec < 0)
    {
        dec *= -1;
        int dif = dec - pow(2, MAX_GENES - 1);
        dec -= dif * 2;
    }

    for (i = MAX_GENES - 1; i >= 0; i--)
    {
        bin[i] = dec % 2;
        dec /= 2;
    }

    return bin;
}

/* Função para converter um número em binário para um número em decimal.
 * Recebe como parâmetros a referência do array que contém o número em
 * binário a ser convertido e um valor inteiro indicando se ele é negativo
 * ou não. A função retorna o número convertido para a base decimal.
 */
int binToDec(int* bin, int negativo)
{
    int i, j = MAX_GENES - 1, dec = 0;

    for (i = 0; i < MAX_GENES; i++)
    {
        if (bin[i] != 0)
            dec += bin[i] * pow(2, j);

        j--;
    }

    if (negativo)
    {
        int dif = dec - pow(2, MAX_GENES - 1);
        dec -= dif * 2;
        dec *= -1;
    }

    return dec;
}
