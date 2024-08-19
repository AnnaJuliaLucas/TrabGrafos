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
No_l* remove_l(Lista *l);
int vazia_l(Lista l);
int destroi_l(Lista *l);
void mostra_l(Lista l);
#endif /* LISTA_h */
