# genetic-algorithm

**Implementação de um algoritmo genético para a disciplina de Inteligência Artificial.**

Detalhes do algoritmo genético:

* Função fitness: f(x) = x2 - y2 + 2xy -5
* X pertence ao intervalo [-100, 100]
* X codificado como vetor binário
* População inicial com 10 indivíduos
* Mutação com taxa de 1%
* Crossover com taxa de 60%
* Seleção por torneio.
* 15 gerações.

Instruções para execução do programa:

1. Clone este repositório.

2. Abra o terminal e mude para a localização do mesmo utilizando o comando `cd`.

* Por exemplo: se o repositório está em C:/, no Windows, acesse-o com `cd C:/genetic-algorithm`.

3. Execute este comando para compilar os códigos fonte e gerar o executável:

* `gcc -Wall headers/* src/* main.c -o main`

4. Por fim, basta iniciar o programa:
`main`
