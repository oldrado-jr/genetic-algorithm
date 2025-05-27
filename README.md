# genetic-algorithm

**Implementação de um algoritmo genético em C, para a disciplina de Inteligência Artificial, durante o Bacharelado em Sistemas de Informação, no Cefet/RJ.**

**Detalhes do algoritmo genético:**

* Função fitness: f(x) = x2 - y2 + 2xy -5
* X pertence ao intervalo [-100, 100]
* X codificado como vetor binário
* População inicial com 10 indivíduos
* Mutação com taxa de 1%
* Crossover com taxa de 60%
* Seleção por torneio.
* 15 gerações.

**Comandos (Linux):**

```bash
# Para compilar o programa e gerar o executável:
gcc -Wall -c src/* && gcc *.o -o main -lm

# Para rodar o programa:
./main

# Para excluir os arquivos-objeto e o executável:
rm -f *.o main
```

* O projeto também poderá ser executado em IDEs, como CodeBlocks e Dev C++.
