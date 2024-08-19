#include "../include/Grafo.h"
#include "../include/Defines.h"
#include "../include/No.h"
#include "../include/Fila.h"
#include "../include/Lista.h"



// =============================================================================================================================================================================
//                                                                            ESTRUTURA BÁSICA DE UM GRAFO
// =============================================================================================================================================================================

/*======================================================
*           CONSTRUTOR INSTÂNCIA
* Função: Inicializar um grafo
* Recebe: ponteiro para um grafo e um ponteiro para um arquivo
* Retorno: void
* ======================================================*/
void inicializar_grafo_com_arquivo(Grafo *grafo, FILE *instance) {

    printf("\n Iniciando o grafo...\n\n");
    // Inicializando o grafo
    grafo->primeiro = NULL;
    grafo->ultimo = NULL;

    grafo->numero_de_nos = grafo->numero_de_arestas = 0;

    // Lendo o arquivo de instância
    if (instance != NULL) {
        char linha[100];

        // Lê a primeira linha do arquivo de instância
        if (fgets(linha, 100, instance) != NULL) 
        {
            sscanf(linha, "%d", &(grafo->numero_de_nos));
        } else {
            printf("Erro ao LER o nº total de nos!\n");
            return;
        }

        for(unsigned int i = 1; i <= grafo->numero_de_nos; i++)
        {
            adicionar_no(grafo, i, 0);
        }

        // Enquanto houver linhas no arquivo
        while (fgets(linha, 100, instance) != NULL) {
            // Armazena os valores da linha: ids dos nós e o peso da aresta
            unsigned int  id_no_1, id_no_2;
            float peso;

            // Verifica ponderações
            if(grafo->arestas_ponderadas == 1)
            {
                if (sscanf(linha, "%d %d %f", &id_no_1, &id_no_2, &peso) != 3) {
                    printf("Erro ao LER o arquivo de instancia\n");
                    break;
                }

                // Adiciona os nós e as arestas no grafo
                adicionar_aresta(grafo, id_no_1, id_no_2, peso);

                if (grafo->direcionado == 0){
                    adicionar_aresta(grafo, id_no_2, id_no_1, peso);
                } 
            } else {
                if (sscanf(linha, "%d %d", &id_no_1, &id_no_2) != 2) {
                    printf("Erro ao LER o arquivo de instancia\n");
                    break;
                }

                // Adiciona os nós e as arestas no grafo
                adicionar_aresta(grafo, id_no_1, id_no_2, 0);

                if (grafo->direcionado == 0){
                    adicionar_aresta(grafo, id_no_2, id_no_1, 0);
                } 
            }
        }

        // Inicializa os graus de entrada e saída dos nós
        //inicializa_graus(grafo); 
        //printf("Graus de entrada: %d", grafo->adj[0]->grau_entrada);

    } else {
        printf("Erro ao ABRIR o arquivo de instancia\n");
    }
}

/*======================================================
*           CONSTRUTOR PADRÃO 
* Função: Inicializar um grafo
* Recebe: ponteiro para um grafo
* Retorno: void
* ======================================================*/
void inicializar_grafo(Grafo *grafo) {
    grafo->numero_de_nos = 0;
    grafo->numero_de_arestas = 0;
    grafo->direcionado = 0;
    grafo->arestas_ponderadas = 0;
    grafo->nos_ponderados = 0;
    grafo->primeiro = NULL;
    grafo->ultimo = NULL;
}

/*======================================================
*                   DESTRUTOR  
* Função: Destruir um grafo
* Recebe: ponteiro para um grafo
* Retorno: void
* ======================================================*/
void destruir_grafo(Grafo *grafo) {
    No *no_atual = grafo->primeiro;

    // Enquanto houver nós no grafo
    while (no_atual != NULL) {
        No *proximo_no = no_atual->proximo_no;
        Aresta *aresta_atual = no_atual->primeira_aresta;
        while (aresta_atual != NULL) {
            Aresta *proximo_aresta = aresta_atual->prox_aresta;
            free(aresta_atual);
            aresta_atual = proximo_aresta;
        }
        free(no_atual);
        no_atual = proximo_no;
    }
}

/*====================================================== 
*                    REMOVER NÓ 
* Função: remove um nó do grafo
* Recebe: id_no - id do nó a ser removido
* Retorno: void
* ======================================================*/
void remover_no(Grafo *grafo, unsigned int  id_no){
    // Verifica se o grafo e a lista de nós existem
    if (grafo == NULL || grafo->primeiro == NULL) {
        return;
    }


    No *no_atual = grafo->primeiro;
    No *no_remover = NULL;

    // Encontrar o nó a ser removido
    while (no_atual) {
        if (no_atual->id == id_no) {
            no_remover = no_atual;
            break;
        }
        no_atual = no_atual->proximo_no;
    }

    if (!no_remover) return; // Nó não encontrado

    // Remover todas as arestas que apontam para o nó a ser removido
    No *no_iter = grafo->primeiro;
    while (no_iter) {
        Aresta *aresta_atual = no_iter->primeira_aresta;
        Aresta *aresta_anterior = NULL;
        while (aresta_atual) {
            if (aresta_atual->id_alvo == id_no) {
                if (aresta_anterior) {
                    aresta_anterior->prox_aresta = aresta_atual->prox_aresta;
                } else {
                    no_iter->primeira_aresta = aresta_atual->prox_aresta;
                }
                free(aresta_atual);
                no_iter->numero_de_arestas--;
                break;
            }
            aresta_anterior = aresta_atual;
            aresta_atual = aresta_atual->prox_aresta;
        }
        no_iter = no_iter->proximo_no;
    }

    // Remover todas as arestas do nó a ser removido
    Aresta *aresta_atual = no_remover->primeira_aresta;
    while (aresta_atual) {
        Aresta *prox_aresta = aresta_atual->prox_aresta;
        free(aresta_atual);
        aresta_atual = prox_aresta;
    }

    // Ajustar os ponteiros do grafo
    if (no_remover->no_anterior) {
        no_remover->no_anterior->proximo_no = no_remover->proximo_no;
    } else {
        grafo->primeiro = no_remover->proximo_no;
    }
    if (no_remover->proximo_no) {
        no_remover->proximo_no->no_anterior = no_remover->no_anterior;
    } else {
        grafo->ultimo = no_remover->no_anterior;
    }

    // Liberar a memória do nó
    free(no_remover);

    // Atualizar os contadores do grafo
    grafo->numero_de_nos--;
}

/*====================================================== 
*                    REMOVER ARESTA
* Função: remove uma aresta do grafo
* Recebe: id_no_1 - id do nó 1
*         id_no_2 - id do nó 2
* Retorno: void
* ======================================================*/
void remover_aresta(Grafo *grafo, unsigned int  id_no_1, unsigned int  id_no_2) {

    // 1. Encontra o nó de origem
    No *no_origem = encontrar_no_por_id(grafo, id_no_1); 
    if (no_origem == NULL) {
        printf("Erro: No de origem %zu nao encontrado.\n", id_no_1);
        return;
    }

    Aresta *aresta_atual = no_origem->primeira_aresta;
    Aresta *aresta_anterior = NULL;

    //2. Percorre a lista de arestas do nó de origem até encontrar a aresta que leva ao nó de destino
    while (aresta_atual != NULL && aresta_atual->id_alvo != id_no_2) {
        aresta_anterior = aresta_atual;
        aresta_atual = aresta_atual->prox_aresta;
    }

    if (aresta_atual == NULL) {
        printf("Erro: Aresta de %zu para %zu nao encontrada.\n", id_no_1, id_no_2);
        return;
    }

    // 3. Remove a aresta ajustando os ponteiros da lista encadeada
    if (aresta_anterior == NULL) {
        no_origem->primeira_aresta = aresta_atual->prox_aresta;
    } else {
        aresta_anterior->prox_aresta = aresta_atual->prox_aresta;
    }

    free(aresta_atual);
    grafo->numero_de_arestas--;

    // 4. Se o grafo não for direcionado, repete o processo para a aresta no nó destino
    if (!grafo->direcionado) {
        // Remover a aresta correspondente no nó de destino
        no_origem = encontrar_no_por_id(grafo, id_no_2);
        if (no_origem == NULL) {
            printf("Erro: Nó de destino %zu não encontrado.\n", id_no_2);
            return;
        }

        aresta_atual = no_origem->primeira_aresta;
        aresta_anterior = NULL;

        while (aresta_atual != NULL && aresta_atual->id_alvo != id_no_1) {
            aresta_anterior = aresta_atual;
            aresta_atual = aresta_atual->prox_aresta;
        }

        if (aresta_atual == NULL) {
            printf("Erro: Aresta de %zu para %zu não encontrada.\n", id_no_2, id_no_1);
            return;
        }

        if (aresta_anterior == NULL) {
            no_origem->primeira_aresta = aresta_atual->prox_aresta;
        } else {
            aresta_anterior->prox_aresta = aresta_atual->prox_aresta;
        }

        free(aresta_atual);
    }
}



/*======================================================= 
*                      ADICIONAR NÓ  
* Função: adiciona um nó ao grafo
* Recebe: id_no - id do nó a ser adicionado
*         peso - peso do nó
* Retorno: void
* =======================================================*/
void adicionar_no(Grafo *grafo, unsigned int  id_no, float peso)
{
    // Verifica se o nó já existe no grafo
    No *no_atual = grafo->primeiro;
    while(no_atual != NULL) 
    {
        
        if(no_atual->id == id_no) // Se o nó já existe no grafo
        {
            printf("Já existe o no %d\n",id_no);
            return;
        }
        no_atual = no_atual->proximo_no; 
    }

    // O nó não existe, então podemos adicioná-lo ao grafo 

    if(grafo->primeiro == NULL) // grafo vazio
    {
        grafo->primeiro = (No*)malloc(sizeof(No)); 
        grafo->primeiro->id = id_no;
        grafo->primeiro->peso = peso;
        grafo->primeiro->proximo_no = NULL;
        //-->direcionar o anterior
        grafo->primeiro->no_anterior = NULL;
        grafo->primeiro->primeira_aresta = NULL;
        grafo->ultimo = grafo->primeiro;
        
    }
    else // grafo não vazio
    {
        No *novo_no = (No*)malloc(sizeof(No)); // cria um novo nó
        novo_no->id = id_no; 
        novo_no->peso = peso;
        novo_no->proximo_no = NULL;
        novo_no->primeira_aresta = NULL;
        
        grafo->ultimo->proximo_no = novo_no; 
        novo_no->no_anterior = grafo->ultimo; 
        grafo->ultimo = novo_no;    
    }
}

/*======================================================= 
*                      ADICIONAR ARESTA 
* Função: adiciona uma aresta ao grafo
* Recebe: id_no_1 - id do nó 1
*         id_no_2 - id do nó 2
*         peso - peso da aresta
* Retorno: void
* =======================================================*/
void adicionar_aresta(Grafo *grafo, unsigned int id_no_1, unsigned int  id_no_2, float peso)
{
    Aresta *nova_aresta = (Aresta*)malloc(sizeof(Aresta)); // cria uma nova aresta
    
    if (nova_aresta == NULL) 
    {
        printf("Erro ao alocar memoria para a nova aresta\n");
        return;
    }

    nova_aresta->id_alvo = id_no_2; 
    nova_aresta->peso = peso;
    nova_aresta->prox_aresta = NULL;
    
    No *no_origem = NULL;
    No *no_destino = NULL;

    // Verifica se o nó de origem existe no grafo
    No *no_atual = grafo->primeiro; 
  
    while (no_atual != NULL) 
    {
        if (no_atual->id == id_no_1) 
        {
            no_origem = no_atual; 
            break;
        }
        no_atual = no_atual->proximo_no; 
    }
  
    // Verifica se o nó de destino existe no grafo
    no_atual = grafo->primeiro; 
    while (no_atual != NULL) 
    {
        if (no_atual->id == id_no_2) 
        {
            no_destino = no_atual; 
            break;
        }
        no_atual = no_atual->proximo_no; 
    }

    // Se o nó de origem não existir no grafo
    if (no_origem == NULL) 
    {
        adicionar_no(grafo, id_no_1, 0);
        no_origem = grafo->ultimo; 
    }

    // Se o nó de destino não existir no grafo
    if (no_destino == NULL) 
    {

        adicionar_no(grafo, id_no_2, 0);
        no_destino = grafo->ultimo; 
    }
 
    // Se a alocação de memória falhou ou se algum dos nós não foi encontrado
    //-->Se a alocação de memória falhou, ele já fez o return lá em cima
    if (no_origem == NULL || no_destino == NULL) {
        free(nova_aresta); // Libera a memória alocada para a nova aresta
        return; // Sai do método se houver falha
    }

    // Se o nó de origem não tiver nenhuma aresta
    if (no_origem->primeira_aresta == NULL) 
    {
        no_origem->primeira_aresta = nova_aresta; 
    }
    else
    {
        Aresta *aresta_atual = no_origem->primeira_aresta;
        while (aresta_atual->prox_aresta != NULL) 
        {
            aresta_atual = aresta_atual->prox_aresta; 
        }
        aresta_atual->prox_aresta = nova_aresta; 
    }
}


/*======================================================
*                  GRAFO VAZIO
* Função: Verifica se o grafo está vazio
* Recebe: grafo - ponteiro para o grafo
* Retorno: 1 se o grafo estiver vazio, 0 caso contrário
* ======================================================*/
int grafo_vazio(Grafo grafo){
    return  (grafo.primeiro == NULL);
}


/*======================================================= 
*                  IMPRIMIR GRAFO 
* Função: imprime o grafo
* Recebe: grafo - ponteiro para o grafo
* Retorno: void
* =======================================================*/
void imprimir_grafo(Grafo *grafo)
{
   // Verifica se o grafo está vazio
    if (grafo->primeiro == NULL) {
        printf("O grafo esta vazio!\n");
        return;
    }
   
    No *no_atual = grafo->primeiro; // o nó atual é o primeiro nó do grafo

    if(grafo->arestas_ponderadas == 1)
    {
        // Enquanto houver nós no grafo
        while (no_atual != NULL) {
            printf("|%d|", no_atual->id);  // Imprime o id do nó - Lista encadeada de nós
            
            if (no_atual->primeira_aresta != NULL) 
            {
                Aresta *aresta_atual = no_atual->primeira_aresta;

                // Percorre todas as arestas do nó atual
                while (aresta_atual != NULL) {
                    // Imprime o ID do nó de origem e as informações da aresta
                    if (grafo->direcionado == 0){
                        printf(" - (%d, %.f)", aresta_atual->id_alvo, aresta_atual->peso);
                    } else {
                        printf(" -> (%d, %.f)", aresta_atual->id_alvo, aresta_atual->peso);
                    }
                    aresta_atual = aresta_atual->prox_aresta;
                }
            } else {
                printf(" -|");
            }

            printf("\n");
            no_atual = no_atual->proximo_no;
        }
    } 
    else {
       // Enquanto houver nós no grafo
        while (no_atual != NULL) {
            printf("|%d|", no_atual->id);  // Imprime o id do nó - Lista encadeada de nós
            
            if (no_atual->primeira_aresta != NULL) 
            {
                Aresta *aresta_atual = no_atual->primeira_aresta;
                // Percorre todas as arestas do nó atual
                while (aresta_atual != NULL) {
                    // Imprime o ID do nó de origem e as informações da aresta
                    printf(" - (%d)", aresta_atual->id_alvo);
                    aresta_atual = aresta_atual->prox_aresta;
                }
            } else {
                printf(" -|");
            }

            printf("\n");
            no_atual = no_atual->proximo_no;
        }  
    }
}


/*====================================================== 
*           IMPRIMIR GRAFO EM ARQUIVO
---------------------------------------------------------
* Função: imprime o grafo em um arquivo
* Recebe: grafo - ponteiro para o grafo
*         output_file - ponteiro para o arquivo de saída
* Retorno: void
====================================================== */
void imprimir_grafo_em_arquivo(Grafo *grafo, FILE *output_file)
{
    // Verifica se o arquivo foi aberto corretamente
    if (output_file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    No *no_atual = grafo->primeiro;

    if (grafo->arestas_ponderadas == 1) {
        // Enquanto houver nós no grafo
        while (no_atual != NULL) {
            fprintf(output_file, "|%d|", no_atual->id);  // Imprime o id do nó - Lista encadeada de nós

            if (no_atual->primeira_aresta != NULL) {
                Aresta *aresta_atual = no_atual->primeira_aresta;

                // Percorre todas as arestas do nó atual
                while (aresta_atual != NULL) {
                    // Imprime o ID do nó de origem e as informações da aresta
                    if (grafo->direcionado == 0) {
                        fprintf(output_file, " - (%d, %.f)", aresta_atual->id_alvo, aresta_atual->peso);
                    } else {
                        fprintf(output_file, " -> (%d, %.f)", aresta_atual->id_alvo, aresta_atual->peso);
                    }
                    aresta_atual = aresta_atual->prox_aresta;
                }
            } else {
                fprintf(output_file, " -|");
            }

            fprintf(output_file, "\n");
            no_atual = no_atual->proximo_no;
        }
    } else {
        // Enquanto houver nós no grafo
        while (no_atual != NULL) {
            fprintf(output_file, "|%d|", no_atual->id);  // Imprime o id do nó - Lista encadeada de nós

            if (no_atual->primeira_aresta != NULL) {
                Aresta *aresta_atual = no_atual->primeira_aresta;
                // Percorre todas as arestas do nó atual
                while (aresta_atual != NULL) {
                    // Imprime o ID do nó de origem e as informações da aresta
                    fprintf(output_file, " - (%d)", aresta_atual->id_alvo);
                    aresta_atual = aresta_atual->prox_aresta;
                }
            } else {
                fprintf(output_file, " -|");
            }

            fprintf(output_file, "\n");
            no_atual = no_atual->proximo_no;
        }
    }
    
    // Fecha o arquivo
    fclose(output_file);
}

/*====================================================== 
*                      CONECTADO 
---------------------------------------------------------
* Função: verifica se dois nós estão conectados
* Parametros: id_no_1 - id do nó 1
*             id_no_2 - id do nó 2
* Retorno: 1 se os nós estão conectados, 0 caso contrário
======================================================*/
int conectado(Grafo *grafo, unsigned int  id_no_1, unsigned int  id_no_2)
{
    if (grafo == NULL) {
        return 0;
    }

    No *no_1 = encontrar_no_por_id(grafo, id_no_1);
    No *no_2 = encontrar_no_por_id(grafo, id_no_2);

    if (no_1 == NULL || no_2 == NULL) {
        return 0;
    }

    // Inicializa vetor de visitados
    int *visitados = (int *)malloc(grafo->numero_de_nos * sizeof(int));
    for (size_t i = 0; i < grafo->numero_de_nos; i++) {
        visitados[i] = 0;
    }

    // Vetor para armazenar vértices visitados em ordem crescente durante a busca
    int *vertices_visitados = (int *)malloc(grafo->numero_de_nos * sizeof(int));
    int contador_visitados = 0;

    // Realiza busca em profundidade a partir de id_no_1
    busca_prof_visit(grafo, id_no_1, visitados, vertices_visitados, &contador_visitados);

    // Verifica se id_no_2 foi marcado como visitado durante a busca
    int conectado = 0;
    for (int i = 0; i < contador_visitados; i++) {
        // Convertendo id_no_2 para int para evitar comparação entre signed e unsigned
        if (vertices_visitados[i] == (int)id_no_2) {
            conectado = 1;
            break;
        }
    }

    free(visitados);
    free(vertices_visitados);

    return conectado;
}


// =============================================================================================================================================================================
//                                                                        ESTRUTURA COMPLEMENTAR DE UM GRAFO
// =============================================================================================================================================================================

/*====================================================== 
*               ENCONTRAR NÓ POR ID
---------------------------------------------------------
* Função: Encontra um nó no grafo a partir de um id
* Parametros: grafo - ponteiro para o grafo
*             id - id do nó
* Retorno: ponteiro para o nó encontrado
======================================================*/
No *encontrar_no_por_id(Grafo *grafo, unsigned int u) {
    No *target = grafo->primeiro;
    while (target != NULL) {
        if (target->id == u) {
            return target;
        }
        target = target->proximo_no;
    }
    if(target->id == u)
    {
        return target;
    }
    return NULL;
}

/*====================================================== 
*               INICIALIZA GRAUS
---------------------------------------------------------
* Função: Inicializa os graus de entrada e saída de todos os nós
* Parametros: grafo - ponteiro para o grafo
* Retorno: void
======================================================*/
void inicializa_graus(Grafo *grafo)
{
    // Inicializa os graus de entrada e saída de todos os nós
    No* tmp_iterator = grafo->primeiro;

    // Zera os graus de entrada e saída de todos os nós
    while (tmp_iterator != NULL)
    {
        tmp_iterator->grau_entrada = 0;
        tmp_iterator->grau_saida = 0;
        tmp_iterator = tmp_iterator->proximo_no;
    }

    // Conta os graus de entrada e saída de cada nó
    tmp_iterator = grafo->primeiro;
    while (tmp_iterator != NULL)
    {
        Aresta *aresta_atual = tmp_iterator->primeira_aresta;
        while (aresta_atual != NULL)
        {
            // Incrementa o grau de saída do nó atual
            tmp_iterator->grau_saida++;

            // Encontra o nó de destino da aresta e incrementa o grau de entrada dele
            No *no_alvo = encontrar_no_por_id(grafo, aresta_atual->id_alvo);
            if (no_alvo != NULL)
                no_alvo->grau_entrada++;

            aresta_atual = aresta_atual->prox_aresta;
        }

        tmp_iterator = tmp_iterator->proximo_no;
    }

}


/*====================================================== 
*              COMPARAR ARESTAS
---------------------------------------------------------
* Função: Compara duas arestas 
* Parametros: a e b - ponteiros para as arestas
* Retorno: void
======================================================*/
int comparar(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

/*====================================================== 
*               BUSCA EM PROFUNDIDADE
---------------------------------------------------------
* Função: realiza a busca em profundidade 
* Parametros: grafo - ponteiro para o grafo
*             u - nó de origem
*             visitados - vetor de marcação, rastreia se um nó foi visitado durante a busca
*             vertices_visitados - vetor que armazena os ids dos vértices visitados em ordem crescente durante a busca 
*             contador_visitados - contador de vértices visitados
* Retorno: void
======================================================*/
void busca_prof_visit(Grafo *grafo, unsigned int u, int *visitados, int *vertices_visitados, int *contador_visitados) {
    visitados[u] = 1;
    vertices_visitados[(*contador_visitados)++] = u;

    No *no = encontrar_no_por_id(grafo, u);
    if (no == NULL) {
        return;  // Caso não encontre o nó, retorna
    }

    Aresta *aresta_atual = no->primeira_aresta; // Aresta atual é a primeira aresta do nó

    // Enquanto houver arestas, chama a busca em profundidade para o nó de destino
    while (aresta_atual != NULL) {
        unsigned int v = aresta_atual->id_alvo; 
        if (!visitados[v])  {
            busca_prof_visit(grafo, v, visitados, vertices_visitados, contador_visitados);
        }
        aresta_atual = aresta_atual->prox_aresta;
    }
}


/*====================================================== 
*      BUSCA EM PROFUNDIDADE INVERSA
---------------------------------------------------------
* Função: realiza a busca em profundidade inversa, ou seja, a partir do nó de destino
* Parametros: grafo - ponteiro para o grafo
*             u - nó de origem
* Retorno: void
======================================================*/
void busca_prof_visit_inversa(Grafo *grafo, unsigned int u, int *visitados, int *vertices_visitados, int *contador_visitados) {
    visitados[u] = 1;
    vertices_visitados[(*contador_visitados)++] = u;

    for (No *tmp = grafo->primeiro; tmp != NULL; tmp = tmp->proximo_no) {
        Aresta *aresta_atual = tmp->primeira_aresta;
        while (aresta_atual != NULL) {
            if (aresta_atual->id_alvo == u && !visitados[tmp->id]) {
                busca_prof_visit_inversa(grafo, tmp->id, visitados, vertices_visitados, contador_visitados);
            }
            aresta_atual = aresta_atual->prox_aresta;
        }
    }
}


/*====================================================== 
*        BUSCA EM PROFUNDIDADE EM TODO O GRAFO
---------------------------------------------------------
* Função: realiza a busca em profundidade no grafo inteiro
* Parametros: grafo - ponteiro para o grafo
* Retorno: void
======================================================*/
void busca_prof(Grafo *grafo) {
    No *tmp_iterator = grafo->primeiro; // Iterador para percorrer os nós
    while (tmp_iterator != NULL) {
        tmp_iterator->visitado = 0; // Inicializa todos os vértices como não visitados
        tmp_iterator = tmp_iterator->proximo_no;
    }

    tmp_iterator = grafo->primeiro;
    int *visitados = (int *)calloc(grafo->numero_de_nos, sizeof(int));  // Aloca vetor de visitados uma vez
    if (visitados == NULL) {
        printf("Erro ao alocar memoria\n");
        return;
    }

    // Percorre todos os nos do grafo
    while (tmp_iterator != NULL) {
        if (visitados[tmp_iterator->id] == 0) {
            int *vertices_visitados = (int *)malloc(grafo->numero_de_nos * sizeof(int)); 
            int contador_visitados = 0; //
            if (vertices_visitados == NULL) {
                printf("Erro ao alocar memoria\n");
                free(visitados);
                return;
            }

            busca_prof_visit(grafo, tmp_iterator->id, visitados, vertices_visitados, &contador_visitados);

            // Ordena os vertices visitados
            qsort(vertices_visitados, contador_visitados, sizeof(int), comparar);

            // Imprime os vertices em ordem crescente
            for (int i = 0; i < contador_visitados; i++) {
                printf("%d ", vertices_visitados[i]);
            }
            printf("\n");

            free(vertices_visitados);
        }
        tmp_iterator = tmp_iterator->proximo_no;
    }
    free(visitados);  // Libera a memória do vetor de visitados após a busca
}


/*====================================================== 
*        FECHO TRANSITIVO DIRETO
---------------------------------------------------------
* Função: realiza o fecho transitivo direto de um nó
* Parametros: grafo - ponteiro para o grafo
*             u - nó de origem
* Retorno: void
======================================================*/
Fecho fecho_transitivo_direto(Grafo *grafo, unsigned int u) {
    Fecho fecho = {NULL, 0};
    No *no = encontrar_no_por_id(grafo, u);
    if (no == NULL) {
        printf("O vertice %u nao existe no grafo\n", u);
        return fecho;
    }

    int *visitados = (int *)calloc(grafo->numero_de_nos, sizeof(int));
    int *vertices_visitados = (int *)malloc(grafo->numero_de_nos * sizeof(int));
    int contador_visitados = 0;

    if (visitados == NULL || vertices_visitados == NULL) {
        printf("Erro ao alocar memoria\n");
        free(visitados);
        free(vertices_visitados);
        return fecho;
    }

    busca_prof_visit(grafo, u, visitados, vertices_visitados, &contador_visitados);

    if (!grafo->direcionado) {
        for (unsigned int i = 1; i <= grafo->numero_de_nos; i++) { 
            if (i != u && encontrar_no_por_id(grafo, i) != NULL && !visitados[i]) {
                busca_prof_visit(grafo, i, visitados, vertices_visitados, &contador_visitados);
            }
        }
    }

    // Ordenar os vértices visitados
    qsort(vertices_visitados, contador_visitados, sizeof(int), comparar);

    // Atualizar o fecho transitivo direto
    fecho.vertices = vertices_visitados;
    fecho.tamanho = contador_visitados;

    free(visitados);
    return fecho;
}


/*====================================================== 
*        FECHO TRANSITIVO INDIRETO
---------------------------------------------------------
* Função: realiza o fecho transitivo indireto de um nó
* Parametros: grafo - ponteiro para o grafo
*             u - nó de origem
* Retorno: void
======================================================*/
Fecho fecho_transitivo_indireto(Grafo *grafo, unsigned int u) {
    Fecho fecho = {NULL, 0};
    No *no = encontrar_no_por_id(grafo, u);
    if (no == NULL) {
        printf("O vertice %u nao existe no grafo\n", u);
        return fecho;
    }

    int *visitados = (int *)calloc(grafo->numero_de_nos, sizeof(int));
    int *vertices_visitados = (int *)malloc(grafo->numero_de_nos * sizeof(int));
    int contador_visitados = 0;

    if (visitados == NULL || vertices_visitados == NULL) {
        printf("Erro ao alocar memoria\n");
        free(visitados);
        free(vertices_visitados);
        return fecho;
    }

    busca_prof_visit_inversa(grafo, u, visitados, vertices_visitados, &contador_visitados);

    if (!grafo->direcionado) {
        for (unsigned int i = 1; i <= grafo->numero_de_nos; i++) {
            if (i != u && encontrar_no_por_id(grafo, i) != NULL && !visitados[i]) {
                busca_prof_visit_inversa(grafo, i, visitados, vertices_visitados, &contador_visitados);
            }
        }
    }

    // Ordenar os vértices visitados
    qsort(vertices_visitados, contador_visitados, sizeof(int), comparar);

    // Atualizar o fecho transitivo indireto
    fecho.vertices = vertices_visitados;
    fecho.tamanho = contador_visitados;

    free(visitados);
    return fecho;
}


/*====================================================== 
*           IMPRIMIR FECHOS TRANSITIVOS
---------------------------------------------------------
* Função: imprime o fecho transitivo direto ou indireto de um nó
* Parametros: grafo - ponteiro para o grafo
*             u - nó de origem
*             tipo_str - tipo de fecho (direto ou indireto)
* Retorno: void
======================================================*/
void imprimir_fecho(Grafo *grafo, unsigned int u, const char *tipo_str) {
    Fecho fecho;

    // Verificar se o tipo de fecho é válido
    if (strcmp(tipo_str, "Direto") == 0) {
        fecho = fecho_transitivo_direto(grafo, u);
    } else if (strcmp(tipo_str, "Indireto") == 0) {
        fecho = fecho_transitivo_indireto(grafo, u);
    } else {
        printf("Tipo de fecho desconhecido.\n");
        return;
    }

    // Imprimir o fecho transitivo
    if (fecho.vertices != NULL) {
        printf("Fecho Transitivo %s a partir do V%u: ", tipo_str, u);
        for (int i = 0; i < fecho.tamanho; i++) {
            printf("%d ", fecho.vertices[i]);
        }
        printf("\n");
        free(fecho.vertices);
    } else {
        printf("Nenhum vertice encontrado.\n");
    }
}


/*======================================================
*               CAMINHO MÍNIMO - DIJKSTRA
---------------------------------------------------------
* Função: Encontra o caminho mínimo entre dois nós utilizando
*         o algoritmo de Dijkstra
* Parametros: grafo - ponteiro para o grafo
*             o - Identificador do nó de origem
*             d - Identificador do nó de destino
* Retorno: grafo com o caminho mínimo
======================================================*/
Grafo caminho_Dijkstra(Grafo *grafo, unsigned int o, unsigned int d ){
    
    Grafo resposta;
    inicializar_grafo(&resposta);
    resposta.direcionado = grafo->direcionado;
    resposta.arestas_ponderadas = grafo->arestas_ponderadas;
    
    //Procura os nós do caminho
    No *no_atual = encontrar_no_por_id(grafo,d);
    if (no_atual==NULL){
        printf("Identificador de destino não encontrado no grafo.\n");
        return resposta;
    }
    no_atual = encontrar_no_por_id(grafo,o);
    if (no_atual==NULL){
        printf("Identificador de origem não encontrado no grafo.\n");
        return resposta;
    }
    //Verificações
    if (o==d){
        printf("Origem e destino iguais.\n");
        return resposta;
    }
    
    //Cria os vetores de distância e de predecessor
    float *distancia = (float *)malloc(grafo->numero_de_nos*sizeof(float));
    int *predecessor = (int *)malloc(grafo->numero_de_nos*sizeof(int));
    Fila *visitados = cria_f();
    
    // atribuindo à todos os elementos de distância um valor muito grande
    for (unsigned int i=0;i<grafo->numero_de_nos;i++){
        distancia[i] = INT_MAX;
        predecessor[i]=-1;
    }
    
    //iniciando o algoritmo
    distancia[o-1]=0; //*
    No *prox_no;

    do {
        Aresta *aresta = no_atual->primeira_aresta;
        while (aresta!=NULL){
            prox_no = encontrar_no_por_id(grafo,aresta->id_alvo);
            //enfila
            if (!contem_f(*visitados,prox_no->id)){
                //getchar();
                if ((distancia[no_atual->id-1]+aresta->peso)<distancia[aresta->id_alvo-1]){ //*
                    distancia[aresta->id_alvo-1] = distancia[no_atual->id-1]+aresta->peso;  //*
                    insere_f(visitados,prox_no);
                    predecessor[aresta->id_alvo-1] = no_atual->id;
                }
            }
            aresta = aresta->prox_aresta;
        }
        no_atual = remove_f(visitados);
        
    }while (no_atual!=NULL); //fila vazia

    //deletando a fila visitados
    destroi_f(visitados);
    
    //imprimindo a tabela para conferência apenas
    /*
     for (int i=0;i<grafo->numero_de_nos;i++){
        printf("%d - %f - %d\n",i+1,distancia[i],predecessor[i]);
    }
    */
    //inserindo os nós no grafo resposta
    adicionar_no(&resposta,d,d);
    //resposta.numero_de_nos++;
    No* atual = encontrar_no_por_id(grafo,d);
    No* prev = encontrar_no_por_id(grafo,predecessor[atual->id-1]);
    if (prev==NULL){
        return resposta;
    }
    while(atual->id!=o){
        adicionar_no(&resposta,prev->id,prev->peso);
        resposta.numero_de_nos++;
        adicionar_aresta(&resposta,atual->id,prev->id,distancia[atual->id-1]-distancia[prev->id-1]);
        atual = prev;
        prev = encontrar_no_por_id(grafo,predecessor[atual->id-1]);
    }
    return resposta;

}

/*======================================================
*                 CAMINHO MÍNIMO - FLOYD
---------------------------------------------------------
* Função: Encontra o caminho mínimo entre dois nós utilizando
*         o algoritmo de Floyd
* Parametros: grafo - ponteiro para o grafo
*             o - Identificador do nó de origem
*             d - Identificador do nó de destino
* Retorno: grafo com o caminho mínimo
======================================================*/
Grafo caminho_Floyd_Warshall(Grafo *grafo, unsigned int o, unsigned int d ){
    Grafo resposta;
    inicializar_grafo(&resposta);
    resposta.direcionado = grafo->direcionado;
    resposta.arestas_ponderadas = grafo->arestas_ponderadas;
    
    //Procura os nós do caminho
    No *no_atual = encontrar_no_por_id(grafo,d);
    if (no_atual==NULL){
        printf("Identificador de destino não encontrado no grafo.\n");
        return resposta;
    }
    no_atual = encontrar_no_por_id(grafo,o);
    if (no_atual==NULL){
        printf("Identificador de origem não encontrado no grafo.\n");
        return resposta;
    }
    //Verificações
    if (o==d){
        printf("Origem e destino iguais.\n");
        return resposta;
    }
    
    //montar a matriz de distâncias distancia
    float distancia[grafo->numero_de_nos][grafo->numero_de_nos];
    int predecessor[grafo->numero_de_nos][grafo->numero_de_nos];
    
    //Monta a matriz distancia com as distâncias iniciais com zero da diagonal principal e infinto no resto
    for (unsigned int lin=0;lin<grafo->numero_de_nos;lin++)
        for (unsigned int col=0;col<grafo->numero_de_nos;col++){
            if (lin==col){
                distancia[lin][col] = 0;
                predecessor[lin][col] = lin;
                
            }else{
                distancia[lin][col] = FLT_MAX;
                predecessor[lin][col] = -1;
            }
        }
    
    //Colocando as distâncias
    No *v_lin = grafo->primeiro;
    Aresta *v_col;
    while (v_lin!=NULL){
        v_col = v_lin->primeira_aresta;
        while (v_col != NULL){
            
            distancia[v_lin->id-1][v_col->id_alvo-1] = v_col->peso;
            predecessor[v_lin->id-1][v_col->id_alvo-1] = v_lin->id-1;
            v_col = v_col->prox_aresta;
        }
        v_lin = v_lin->proximo_no;
    }
    
    //Método
    for (unsigned int k=0;k<grafo->numero_de_nos;k++){
        for (unsigned int i=0; i<grafo->numero_de_nos; i++){
            for (unsigned int j=0; j<grafo->numero_de_nos; j++){
                if (distancia[i][j] > distancia[i][k] + distancia[k][j]){
                    distancia[i][j] = distancia[i][k] + distancia[k][j];
                    predecessor[i][j] = predecessor[k][j];
                }
            }
        }
    }
    //Caminho:
     if (predecessor[o-1][d-1] == -1){
         return resposta;
     }
    
    //inserindo os nós no grafo resposta
    adicionar_no(&resposta,d,d);
    No* atual = encontrar_no_por_id(grafo,d);
    No* prev = encontrar_no_por_id(grafo,predecessor[o-1][d-1]+1);
    while(atual->id!=o){
        adicionar_no(&resposta,prev->id,prev->peso);
        adicionar_aresta(&resposta,atual->id,prev->id,distancia[atual->id-1][prev->id-1]);
        atual = prev;
        prev = encontrar_no_por_id(grafo,predecessor[o-1][atual->id-1]+1);
    }
    return resposta;
}

/*======================================================
*              VERIFICA SE ESTA ENTRE
---------------------------------------------------------
* Função: Verifica se um elemento está entre um vetor
* Parametros: vetor - vetor de inteiros
*             elemento - elemento a ser verificado
* Retorno: 1 se o elemento está no vetor, 0 caso contrário
======================================================*/
int esta_entre(unsigned int* vetor, unsigned int elemento){
    int tam = sizeof(vetor) / sizeof(int);
    for(int i=0;i<tam;i++){
        if (elemento==vetor[i])
            return 1;
    }
    return 0;
}

/*======================================================
*        ÁRVORE GERADORA MÍNIMA - KRUSKAL
---------------------------------------------------------
* Função: Encontra a árvore geradora mínima de um grafo
*         utilizando o algoritmo de Kruskal
* Parametros: grafo - ponteiro para o grafo
* Retorno: Grafo - árvore geradora mínima
======================================================*/
Grafo AGM_Kruskal(Grafo grafo){

    if (grafo.numero_de_nos<3){
        return grafo;
    }
    //subs é um grafo que representa as subárvores
    Grafo subs;
    inicializar_grafo(&subs);

    if (grafo.direcionado){
        return subs;
    }
    
    subs.arestas_ponderadas = grafo.arestas_ponderadas;
    subs.nos_ponderados = grafo.nos_ponderados;
    //Copia os nós de grafo para subs
    No *no = grafo.primeiro;

    //Cria a lista de arestas ordenadas
    Lista *lista = cria_l(grafo);
    mostra_l(*lista);
    printf("\n");
    while (no!=NULL){
        adicionar_no(&subs,no->id, no->peso);
        subs.numero_de_nos++;
        no = no->proximo_no;
    }

    unsigned int contador = 0;
    No_l *aresta;
    Grafo fecho_o;
    Grafo fecho_d;

    while ((contador<grafo.numero_de_nos - 1) && (lista->tam>0)){
        aresta = remove_l(lista);
        fecho_o = caminho_Dijkstra(&subs, aresta->origem,aresta->destino);
        fecho_d = caminho_Dijkstra(&subs, aresta->destino,aresta->origem);

        if (fecho_o.numero_de_nos==0 && fecho_d.numero_de_nos==0){
            adicionar_aresta(&subs,aresta->origem, aresta->destino,aresta->peso);
            adicionar_aresta(&subs,aresta->destino, aresta->origem,aresta->peso);
            contador++;
        }
    }
    return subs;
}

/*======================================================
*        ÁRVORE GERADORA MÍNIMA - PRIM
---------------------------------------------------------
* Função: Encontra a árvore geradora mínima de um grafo
*         utilizando o algoritmo de Prim
* Parametros: grafo - ponteiro para o grafo
* Retorno: Grafo - árvore geradora mínima
======================================================*/
Grafo AGM_Prim(Grafo grafo){
    if (grafo.numero_de_nos<3){
        return grafo;
    }
    //Lista *lista = cria_l(grafo);
    //Array de nós
    Grafo subs;
    inicializar_grafo(&subs);
    subs.direcionado = grafo.direcionado;
    subs.arestas_ponderadas = grafo.arestas_ponderadas;
    subs.nos_ponderados = grafo.nos_ponderados;

    
    return subs;
}
