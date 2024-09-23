# TEORIA DOS GRAFOS - DCC059 

## Desenvolvido por
  > Anna Julia de Almeida Lucas

  > Mateus Alves da Silva



## Índice
1. [Primeiro Trabalho](1-trabalho.md)
2. [Segundo Trabalho](2-trabalho.md)




## 2º Trabalho
• Objetivo: Estender seu Tipo Abstrato de Dados - TAD ou classe desenvolvidos no Trabalho 1 de forma a
assegurar que represente grafos conforme sejam definidas as instâncias do problema. Para este
trabalho, o TAD ou a Classe devem apresentar os seguintes algoritmos para o problema:


```
a) Algoritmo guloso
```
b) Algoritmo guloso randomizado adaptativo;
```
c) Algoritmo guloso randomizado adaptativo reativo;
```

Definição do Problema:
• Grafo Não Direcionado: O problema é definido em um grafo não direcionado G=(V,E), onde
V é o conjunto de vértices e E o conjunto de arestas.
• Pesos nos Vértices: Cada vértice v∈V tem um peso associado wv, que é um valor numérico.
Este peso pode, por exemplo, representar algum atributo do vértice, como altura, demanda ou
custo.
• Partição em Subgrafos: O objetivo do MGGPP é particionar o grafo em um número
predefinido p de subgrafos conectados, ou seja, cada subgrafo resultante deve ser conexo e
não pode ser um conjunto vazio de vértices. Todos os subgrafos devem ter, no mínimo, dois
vértices.
• Minimização da Diferença de Pesos (Gap): A característica principal do problema é minimizar
a diferença, chamada de gap, entre o maior e o menor peso dentro de cada subgrafo. Para um
subgrafo �!, o gap �"! é dado pela diferença entre o maior peso �"! e o menor peso �"! dentro
do subgrafo. O objetivo é minimizar a soma dos gaps de todos os subgrafos, ou seja, minimizar
∑ �"!
#
!$%

Regras e Restrições:

1. Número predefinido de subgrafos: O número de subgrafos p é fixo e definido a priori, com a
restrição de que 1<p<n, onde n é o número total de vértices do grafo.
2. Subgrafos Conectados: Todos os subgrafos devem ser conectados, ou seja, deve haver um
caminho entre qualquer par de vértices dentro do mesmo subgrafo.
3. Vértices Desconectados: O problema considera que os subgrafos resultantes não podem ser
desconexos ou compostos por apenas um vértice.
4. Minimização do Gap Total: O objetivo é minimizar a soma dos gaps em todos os subgrafos
da partição, visando obter subgrafos cujas distribuições de pesos sejam o mais homogêneas
possível.
## EXECUÇÃO 
Para executar o programa: