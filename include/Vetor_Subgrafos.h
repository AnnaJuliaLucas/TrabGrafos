#ifndef vetor_subgrafos_h
#define vetor_subgrafos_h

#include "Defines.h"
#include "Grafo.h"

typedef struct Vetor{
    int *sub;
    int n_subs;
}Vetor;

Vetor* cria_v(int n);
void redividir_subs(Vetor *vetor,Grafo subs,No no1, No no2);


#endif /* vetor_subgrafos_h */
