#include "../include/Grafo.h"
#include "../include/Defines.h"
#include "../include/No.h"
#include "../include/Fila.h"
#include "../include/Lista.h"
#include "../include/Pilha.h"
#include "../include/Vetor_Subgrafos.h"
#include "../include/Algoritmos_Gulosos.h"

#define INF FLT_MAX

/* =======================================================
*               COPIA GRAFO
*---------------------------------------------------------
* Função: Copia um grafo a fim de realizar operações sem alterar o original
* Recebe: grafo - grafo a ser copiado    
* Retorno: Grafo* - ponteiro para o grafo copiado
* ======================================================*/
Grafo* copia_grafo(Grafo grafo) {
    printf("Iniciando a copia do grafo\n");

    // Aloca memória para o novo grafo
    Grafo* novo = (Grafo *)malloc(sizeof(Grafo));
    if (novo == NULL) {
        printf("Erro: falha ao alocar memoria para o novo grafo\n");
        return NULL;
    }

    // Copia as propriedades básicas do grafo
    novo->numero_de_nos = grafo.numero_de_nos;
    novo->direcionado = grafo.direcionado;
    novo->arestas_ponderadas = grafo.arestas_ponderadas;
    novo->nos_ponderados = grafo.nos_ponderados;
    novo->primeiro = NULL;
    novo->ultimo = NULL;

    printf("Grafo original: %u nos, %u arestas \n", grafo.numero_de_nos, grafo.arestas_ponderadas);

    // Copia os nós
    No* aux = grafo.primeiro;
    unsigned int contador_nos = 0;

    while (aux != NULL && contador_nos < grafo.numero_de_nos) {
       // printf("Copiando no %u \n");
        adicionar_no(novo, aux->id, aux->peso);  // Copia o nó
        aux = aux->proximo_no;
        contador_nos++;
    }

    // Copia as arestas
    aux = grafo.primeiro;
    unsigned int contador_arestas = 0;
    for (unsigned int i = 0; i < grafo.numero_de_nos; i++) {
        if (aux == NULL) {
            printf("Erro: no %u eh NULL, impossivel copiar arestas\n", i);
            break;
        }

        Aresta* aresta = aux->primeira_aresta;
        while (aresta != NULL) {
            //printf("Copiando aresta de %u para %u \n", aux->id, aresta->id_alvo, aresta->peso);
            adicionar_aresta(novo, aux->id, aresta->id_alvo, aresta->peso);  // Copia a aresta
            aresta = aresta->prox_aresta;
            contador_arestas++;
        }
        aux = aux->proximo_no;
    }

    printf("Copia do grafo finalizada. Nos copiados: %u, arestas copiadas: %u\n", contador_nos, contador_arestas);

    return novo;
}


/* =======================================================
*               CRIA MENOR GAP
*---------------------------------------------------------
* Função: Cria uma lista de prioridades com os nós que possuem o menor gap
* Recebe: grafo - grafo a ser analisado
*         n_subs - número de subgrafos
* Retorno: Lista* - ponteiro para a lista de prioridades
* ======================================================*/
Grafo MGGPP_guloso(Grafo *grafo, int n_sub){

    Timer timer; // Declaração do timer
    startTimer(&timer);

    Grafo* subs = NULL;

    //Se o número de subgrafos eh maior que o número de nos acabou o algoritmo
    if ((unsigned int)n_sub > grafo->numero_de_nos/2){
        return *subs;
    }
    
    //Copia o grafo para subs:
    subs = copia_grafo(*grafo);

    if (subs == NULL) {
        printf("Erro: copia do grafo retornou NULL\n");
        exit(1);  // Se copia_grafo falhar, é um erro crítico
    }
   
    //Percorre todos o grafo para criar a lista de prioridades
    Lista *l;
    l = cria_menor_gap(*grafo);
    Vetor* vetor = cria_v((int)grafo->numero_de_nos);
    No_l* maior;
    No *origem, *destino;

    while (vetor->n_subs<n_sub && !vazia_l(*l)){
        //remove maior gap da lista e o seu recíproco
        maior = remove_l(l);
        remover_aresta(subs, maior->origem, maior->destino);  

        //Se o nó origem ou o de destino ficaram com apenas 1 aresta, remove ela e a recíproca
        origem = encontrar_no_por_id(subs, maior->origem);
        if (origem->numero_de_arestas<2){ //Toda aresta tem a recíproca
            remover_no_l(l, origem->id);
        }
        destino = encontrar_no_por_id(subs, maior->destino);
        if (destino->numero_de_arestas<2){ //Toda aresta tem a recíproca
            remover_no_l(l, destino->id);
        }

        redividir_subs(vetor,*subs,*origem,*destino);
    }

    stopTimer(&timer);
    return *subs;
}


/* =======================================================
*               CRIA MENOR GAP
*---------------------------------------------------------
* Função: Cria uma lista de prioridades com os nós que possuem o menor gap
* Recebe: grafo - grafo a ser analisado
* Retorno: Lista* - ponteiro para a lista de prioridades
* ======================================================*/
int inicializar_grafo_MGGPP(Grafo *grafo, FILE *file) {
    int p;

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char line[1024];
    //int i = 0;

    // Ler o parâmetro 'p'
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "param p := %d ;", &p) == 1) {
            break;
        }
    }


    // Ler o conjunto V (vertices)
    grafo->primeiro = grafo->ultimo = NULL;
    grafo->numero_de_arestas = 0;
    int nos[grafo->numero_de_nos];


    // Ler os pesos 'w'
    int vertex, weight;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "param w :=")) {
            while (fgets(line, sizeof(line), file) && !strstr(line, ";")) {
                sscanf(line, "%d %d", &vertex, &weight);
                nos[vertex-1] = weight;
            }
            break;
        }
    }

    for (unsigned int i=0;i<grafo->numero_de_nos;i++){
        adicionar_no(grafo,i+1,nos[i]);
    }
    
    // Ler as arestas 'E'
    
    //int i = 0;
    int id_no_1, id_no_2;
    char *ptr;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "set E :=")) {
            while (fgets(line, sizeof(line), file) && !strstr(line, ";")) {
                // Ponteiro para percorrer a linha
                ptr = line;
                // Ler múltiplos pares numa linha
                while (1){
                    ptr = strchr(ptr + 1, '(');
                    if (ptr == NULL) {
                        break; // Não há mais pares na linha
                    }
                    sscanf(ptr, " (%d,%d)", &id_no_1, &id_no_2) ;
                    adicionar_aresta(grafo, id_no_1, id_no_2, 0);
                    adicionar_aresta(grafo, id_no_2, id_no_1, 0);

                    // Avançar o ponteiro para o próximo par
                    
                }
            }
        }
    }
    
    //add anna
    //MGGPP_guloso(grafo,p);
    
    fclose(file);
    return 0;

}