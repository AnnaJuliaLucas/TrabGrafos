#ifndef GRAFO_H
#define GRAFO_H

#include "Defines.h"
#include "No.h"

typedef struct Grafo {
    size_t numero_de_nos;
    size_t numero_de_arestas;
    int direcionado;
    int arestas_ponderadas;
    int nos_ponderados;
    No *primeiro;
    No *ultimo;
    No **adj;

} Grafo;

void inicializar_grafo(Grafo *grafo);
void inicializar_grafo_com_arquivo(Grafo *grafo, FILE *instance);
void destruir_grafo(Grafo *grafo);
void remover_no(Grafo *grafo, size_t id_no);
void remover_aresta(Grafo *grafo, size_t id_no_1, size_t id_no_2);
void adicionar_no(Grafo *grafo, size_t id_no, float peso);
void adicionar_aresta(Grafo *grafo, size_t id_no_1, size_t id_no_2, float peso);
void imprimir_grafo_em_arquivo(Grafo *grafo, FILE *output_file);
void imprimir_grafo_console(Grafo *grafo);
void imprimir_grafo(Grafo *grafo);
int conectado(Grafo *grafo, size_t id_no_1, size_t id_no_2);

// Funções adicionadas
void inicializa_graus(Grafo *grafo);
No *encontrar_no_por_id(Grafo *grafo, unsigned int id);
void busca_prof(Grafo *grafo);
void busca_prof_visit(Grafo *grafo, unsigned int u, int *visitados, int *vertices_visitados, int *contador_visitados);
void busca_prof_visit_inversa(Grafo *grafo, unsigned int u, int *visitados, int *vertices_visitados, int *contador_visitados);
void fecho_transitivo_direto(Grafo *grafo, unsigned int u);
void fecho_transitivo_indireto(Grafo *grafo, unsigned int u);
int comparar(const void *a, const void *b);

#endif  // GRAFO_H