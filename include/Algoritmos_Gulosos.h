#ifndef ALGORITMOS_GULOSOS_H 
#define ALGORITMOS_GULOSOS_H

#include "Defines.h"
#include "No.h"
#include "Pilha.h"


int inicializar_grafo_MGGPP(Grafo *grafo, FILE *file);
Grafo MGGPP_guloso(Grafo *grafo, int n_sub);

#endif /* ALGORITMOS_GULOSOS_H */