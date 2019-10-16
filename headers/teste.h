#ifndef TESTE_H_INCLUDED
#define TESTE_H_INCLUDED

// Definições dos protótipos das funções utilizadas na função principal.

// Inclui o arquivo das definições de uma população.
#include "populacao.h"

Populacao** inicializar();
Populacao* populacaoInicial();
Populacao* novaPopulacao(Populacao*);

#endif // TESTE_H_INCLUDED
