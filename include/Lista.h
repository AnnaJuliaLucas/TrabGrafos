#ifndef LISTA_h
#define LISTA_h
#include "Defines.h"
#include "No.h"

typedef struct No_l{
    struct No_l *proximo;
    unsigned int origem, destino;
    float peso;
}No_l;

typedef struct Lista{
    struct No_l *head;
    int tam;
} Lista;

Lista* cria_l(Grafo grafo);
Lista* cria_vazia_l();
No_l* remove_l(Lista *l);
void insere_l(Lista *l,No no, Aresta aresta);
int vazia_l(Lista l);
void destroi_l(Lista *l);
void mostra_l(Lista l);
void insere_menor_gap(Lista *l, unsigned int origem, unsigned int destino, float gap);
Lista* cria_menor_gap(Grafo grafo);
void remover_aresta_l(Lista *l, unsigned int origem, unsigned int destino);
void remover_no_l(Lista *l, unsigned int origem);

#endif /* LISTA_h */