#ifndef ARESTA_H
#define ARESTA_H

#include "Defines.h"

typedef struct Aresta {
    struct Aresta *prox_aresta;
    float peso;
    unsigned int id_alvo;
}Aresta;

#endif /* ARESTA_H */
