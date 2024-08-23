#ifndef GRAFO_H
#define GRAFO_H

#include "Defines.h"
#include "No.h"

typedef struct No No;
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
typedef struct {
    int *vertices;
    int tamanho;
} Fecho;

typedef struct {
    unsigned int numero_de_nos;
    No *primeiro;
} SubGrafo;

void gerar_arquivo_dot(Grafo *grafo, const char *nome_arquivo);
void gerar_arquivo_dot_arvore_dfs(int *arvore_dfs, int num_arestas_arvore, int *arestas_retorno, int num_arestas_retorno, const char *nome_arquivo);

void inicializar_grafo(Grafo *grafo);
void inicializar_grafo_com_arquivo(Grafo *grafo, FILE *instance);
void destruir_grafo(Grafo *grafo);
void remover_no(Grafo *grafo, unsigned int  id_no);
void remover_aresta(Grafo *grafo, unsigned int  id_no_1, unsigned int  id_no_2);
void adicionar_no(Grafo *grafo, unsigned int  id_no, float peso);
void adicionar_aresta(Grafo *grafo, unsigned int  id_no_1, unsigned int  id_no_2, float peso);
void imprimir_grafo_em_arquivo(Grafo *grafo, FILE *output_file);
void imprimir_grafo_console(Grafo *grafo);
void imprimir_grafo(Grafo *grafo);
int conectado(Grafo *grafo, unsigned int  id_no_1, unsigned int  id_no_2);

// Funções adicionadas
void inicializa_graus(Grafo *grafo);
No *encontrar_no_por_id(Grafo *grafo, unsigned int u);
Aresta *encontrar_antecessor_aresta(Grafo *grafo, unsigned int id_origem, unsigned int id_destino);
void busca_prof(Grafo *grafo);
void busca_prof_visit(Grafo *grafo, unsigned int u, int *visitados, int *vertices_visitados, int *contador_visitados);
void busca_prof_visit_inversa(Grafo *grafo, unsigned int u, int *visitados, int *vertices_visitados, int *contador_visitados);
int comparar(const void *a, const void *b);

// Funções relacionadas ao fecho transitivo
Fecho fecho_transitivo_direto(Grafo *grafo, unsigned int u);
Fecho fecho_transitivo_indireto(Grafo *grafo, unsigned int u);
void imprimir_fecho(Grafo *grafo, unsigned int u, const char *tipo_str);

// Funções do caminho mínimo
Grafo caminho_Dijkstra(Grafo *grafo, unsigned int o, unsigned int d );
Grafo caminho_Floyd_Warshall(Grafo *grafo, unsigned int o, unsigned int d );
Grafo AGM_Kruskal(Grafo grafo);
Grafo AGM_Prim(Grafo grafo);
int grafo_vazio(Grafo grafo);

void unir(int *pais, int *rank, int x, int y);
int encontrar(int *pais, int i);


#endif // GRAFO_H
