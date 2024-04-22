#include "../include/Grafo.h"
#include "../include/defines.h"
#include "../include/No.h"

// ========================================================================================================================
//                                        ESTRUTURA BÁSICA DE UM GRAFO
// ========================================================================================================================

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
            printf("Erro ao LER o nº total de nós!\n");
            return;
        }

        // Enquanto houver linhas no arquivo
        while (fgets(linha, 100, instance) != NULL) {
            // Armazena os valores da linha: ids dos nós e o peso da aresta
            size_t id_no_1, id_no_2;
            float peso;

            // Verifica ponderações
            if(grafo->arestas_ponderadas == 1)
            {
                if (sscanf(linha, "%d %d %f", &id_no_1, &id_no_2, &peso) != 3) {
                    printf("Erro ao LER o arquivo de instância\n");
                    break;
                }

                // Adiciona os nós e as arestas no grafo
                adicionar_no(grafo, id_no_1, 0);
                adicionar_no(grafo, id_no_2, 0);
                adicionar_aresta(grafo, id_no_1, id_no_2, peso);
            } else {
                if (sscanf(linha, "%d %d", &id_no_1, &id_no_2) != 2) {
                    printf("Erro ao LER o arquivo de instância\n");
                    break;
                }

                // Adiciona os nós e as arestas no grafo
                adicionar_no(grafo, id_no_1, 0);
                adicionar_no(grafo, id_no_2, 0);
                adicionar_aresta(grafo, id_no_1, id_no_2, 0);
            }
        }

        // Inicializa os graus de entrada e saída dos nós
        //inicializa_graus(grafo); 
        //printf("Graus de entrada: %d", grafo->adj[0]->grau_entrada);

        

    } else {
        printf("Erro ao ABRIR o arquivo de instância\n");
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
// void remover_no(Grafo *grafo, size_t id_no)
// {
// }

/*====================================================== 
*                    REMOVER ARESTA
* Função: remove uma aresta do grafo
* Recebe: id_no_1 - id do nó 1
*         id_no_2 - id do nó 2
* Retorno: void
* ======================================================*/
// void remover_aresta(Grafo *grafo, size_t id_no_1, size_t id_no_2)
// {
// }


/*======================================================= 
*                      ADICIONAR NÓ  
* Função: adiciona um nó ao grafo
* Recebe: id_no - id do nó a ser adicionado
*         peso - peso do nó
* Retorno: void
* =======================================================*/
void adicionar_no(Grafo *grafo, size_t id_no, float peso)
{
    // Verifica se o nó já existe no grafo
    No *no_atual = grafo->primeiro;
    while(no_atual != NULL) 
    {
        if(no_atual->id == id_no) // Se o nó já existe no grafo
        {
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
void adicionar_aresta(Grafo *grafo, size_t id_no_1, size_t id_no_2, float peso)
{
    Aresta *nova_aresta = (Aresta*)malloc(sizeof(Aresta)); // cria uma nova aresta
    
    if (nova_aresta == NULL) 
    {
        printf("Erro ao alocar memória para a nova aresta\n");
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
    if (nova_aresta == NULL || no_origem == NULL || no_destino == NULL) {
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
                    printf(" -> (%d, %.f)", aresta_atual->id_alvo, aresta_atual->peso);
                    aresta_atual = aresta_atual->prox_aresta;
                }
            } else {
                printf(" -|\n");
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

    if(grafo->direcionado == 1)
    {
        // Enquanto houver nós no grafo
        while (no_atual != NULL) {
            fprintf(output_file, "|%d|\n", no_atual->id);

            if (no_atual->primeira_aresta == NULL) {
                fprintf(output_file, " -|\n");
            } else {
                Aresta *aresta_atual = no_atual->primeira_aresta;

                while (aresta_atual != NULL) {
                    fprintf(output_file, "-> %d , %.2f", aresta_atual->id_alvo, aresta_atual->peso);
                    aresta_atual = aresta_atual->prox_aresta;
                }
            }
            fprintf(output_file, "\n");
            no_atual = no_atual->proximo_no;
        }
    } else {
        // Enquanto houver nós no grafo
        while (no_atual != NULL) {
            fprintf(output_file, "|%d|", no_atual->id);

            if (no_atual->primeira_aresta == NULL) {
                fprintf(output_file, " -|");
            } else {
                Aresta *aresta_atual = no_atual->primeira_aresta;

                while (aresta_atual != NULL) {
                    fprintf(output_file, "- %d", aresta_atual->id_alvo);
                    aresta_atual = aresta_atual->prox_aresta;
                }
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
// int conectado(Grafo *grafo, size_t id_no_1, size_t id_no_2)
// {
// }


// ========================================================================================================================
//                                       ESTRUTURA COMPLEMENTAR DE UM GRAFO
// ========================================================================================================================
No *encontrar_no_por_id(Grafo *grafo, unsigned int id) {
    No *tmp_iterator = grafo->primeiro;
    while (tmp_iterator != NULL) {
        if (tmp_iterator->id == id) {
            return tmp_iterator;
        }
        tmp_iterator = tmp_iterator->proximo_no;
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

    // Agora que os graus foram calculados para todos os nós, vamos imprimir as informações
    // tmp_iterator = grafo->primeiro;
    // while (tmp_iterator != NULL)
    // {
    //     printf("* No %u:\n", tmp_iterator->id);
    //     printf("  - Graus de Entrada: %u\n", tmp_iterator->grau_entrada);
    //     printf("  - Graus de Saida: %u\n", tmp_iterator->grau_saida);
    //     tmp_iterator = tmp_iterator->proximo_no;
    // }
}

/*====================================================== 
*               BUSCA EM PROFUNDIDADE
---------------------------------------------------------
* Função: realiza a busca em profundidade 
* Parametros: grafo - ponteiro para o grafo
*             no - ponteiro para o nó
* Retorno: void
======================================================*/
void busca_prof_visit(Grafo *grafo, No *no) {
    // Marca o vértice como visitado
    no->visitado = 1;
    printf("%u ", no->id); // Você pode modificar esta linha para fazer o que quiser com o vértice

    // Percorre todos os vértices adjacentes ao vértice atual
    Aresta *aresta_atual = no->primeira_aresta;
    while (aresta_atual != NULL) {
        // Se o vértice adjacente não foi visitado, faz uma chamada recursiva para visitá-lo
        No *no_adj = encontrar_no_por_id(grafo, aresta_atual->id_alvo);
        if (no_adj != NULL && no_adj->visitado == 0)
            busca_prof_visit(grafo, no_adj);
        aresta_atual = aresta_atual->prox_aresta;
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
    No *tmp_iterator = grafo->primeiro;
    while (tmp_iterator != NULL) {
        tmp_iterator->visitado = 0; // Inicializa todos os vértices como não visitados
        tmp_iterator = tmp_iterator->proximo_no;
    }

    tmp_iterator = grafo->primeiro;
    while (tmp_iterator != NULL) {
        if (tmp_iterator->visitado == 0)
            busca_prof_visit(grafo, tmp_iterator); // Inicia a busca em profundidade a partir de um vértice não visitado
        tmp_iterator = tmp_iterator->proximo_no;
    }
}


void fecho_transitivo_direto(Grafo *grafo, unsigned int u) {
    // Verifica se o vértice u existe no grafo
    No *no = encontrar_no_por_id(grafo, u);
    if (no == NULL) {
        printf("O vertice %u nao existe no grafo\n", u);
        return;
    }

    // Marca todos os vértices alcançáveis a partir de u
    printf("Fecho Transitivo Direto a partir do V%u: ", u);
    busca_prof_visit(grafo, no);
    printf("\n");
}
