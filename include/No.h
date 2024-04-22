#ifndef NO_H
#define NO_H

#include "Aresta.h"
#include "Grafo.h"
#include "Defines.h"

typedef struct No {
    unsigned int numero_de_arestas;
    unsigned int id;
    double peso;
    struct Aresta *primeira_aresta;
    struct No *proximo_no;
    struct No *no_anterior;
    unsigned int grau_entrada;
    unsigned int grau_saida;
    unsigned int visitado; // 0 = não visitado, 1 = visitado
}No;

#endif  // NO_H