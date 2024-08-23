#ifndef ARESTA_H
#define ARESTA_H

#include "Defines.h"

typedef struct Aresta {
    struct Aresta *prox_aresta;
    float peso;
    unsigned int id_alvo;
}Aresta;

typedef struct ArestaDFS {
    unsigned int origem;
    unsigned int destino;
    struct ArestaDFS *prox_aresta;
} ArestaDFS;

#endif /* ARESTA_H */
