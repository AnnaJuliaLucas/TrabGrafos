# 2º Trabalho

*Objetivo:* Estender o TAD ou classe desenvolvidos no Trabalho 1 para representar grafos conforme as instâncias definidas do problema. Este trabalho foca na implementação dos seguintes algoritmos:

### Algoritmos Implementados:

1. **Algoritmo Guloso**
2. **Algoritmo Guloso Randomizado Adaptativo**
3. **Algoritmo Guloso Randomizado Adaptativo Reativo**

### Definição do Problema

- **Grafo Não Direcionado:** O problema é definido em um grafo não direcionado \(G=(V,E)\), onde \(V\) é o conjunto de vértices e \(E\) é o conjunto de arestas.
- **Pesos nos Vértices:** Cada vértice \(v \in V\) tem um peso associado \(w_v\), que pode representar atributos como altura, demanda ou custo.
- **Partição em Subgrafos:** O objetivo é particionar o grafo em um número predefinido \(p\) de subgrafos conectados. Cada subgrafo deve ser conexo e conter ao menos dois vértices.

#### Minimização da Diferença de Pesos (Gap)
O problema é minimizar a diferença, chamada de **gap**, entre os vértices de maior e menor peso dentro de cada subgrafo. O objetivo é minimizar a soma dos gaps de todos os subgrafos.

- **Gap** em um subgrafo \(S_i\): 

   `gap(S_i) = w_max(S_i) - w_min(S_i)`

Onde:
- \(w_max(S_i)\) é o maior peso dentro do subgrafo \(S_i\).
- \(w_min(S_i)\) é o menor peso dentro do subgrafo \(S_i\).

O objetivo geral é minimizar a soma dos gaps de todos os subgrafos:

- **Soma dos Gaps:**
  
  `Soma = Σ gap(S_i) para i = 1 até p`

Onde:
- \(p\) é o número total de subgrafos.


### Regras e Restrições

1. **Número de Subgrafos Predefinido:** O número de subgrafos \(p\) é fixo, com \(1 < p < n\), onde \(n\) é o número total de vértices.
2. **Subgrafos Conectados:** Todos os subgrafos devem ser conexos.
3. **Vértices Desconectados:** Subgrafos não podem ser compostos por apenas um vértice.
4. **Minimização do Gap Total:** O objetivo é minimizar a soma dos gaps de todos os subgrafos, obtendo subgrafos com distribuições de pesos homogêneas.

### Execução
Para executar o programa, utilize o comando:

```bash
.\grafo <arquivo_entrada> <arquivo_saida> <opções>