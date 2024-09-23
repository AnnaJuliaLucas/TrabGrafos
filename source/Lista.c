#include "../include/Lista.h"
#include "../include/Defines.h"
#include "../include/No.h"

/*======================================================
*                     INSERE LISTA
--------------------------------------------------------
* Função: Insere um elemento na lista
* Parametros:   Lista *l - lista
                No no - nó do grafo
                Aresta aresta - aresta do grafo
* Retorno: Void
======================================================*/
void insere_l(Lista *l,No no, Aresta aresta){
    No_l* novo = (No_l*)malloc(sizeof(No_l));
    novo->origem = no.id;
    novo->destino = aresta.id_alvo;
    novo->peso = aresta.peso;
    l->tam +=1;
    if (l->tam==1){
        l->head = novo;
        novo->proximo = NULL;
        return;
    }
    if (l->head->peso>aresta.peso){
        novo->proximo= l->head;
        l->head = novo;
        return;
    }
    No_l *atual = l->head;
    while (atual->proximo!=NULL && atual->proximo->peso<aresta.peso){
        atual = atual->proximo;
    }
    //Se a aresta já está em lista, não inclui
    if (atual->proximo!=NULL && atual->proximo->peso==aresta.peso && atual->proximo->origem==no.id && atual->proximo->destino==aresta.id_alvo){
        free(novo);
    }else{
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }
}


/*======================================================
*                     CRIA LISTA
--------------------------------------------------------
* Função: Cria uma lista
* Parametros: Grafo grafo - grafo
* Retorno: Lista*
======================================================*/
Lista* cria_l(Grafo grafo){
    Lista *nova = (Lista *)malloc(sizeof(Lista));
    nova->head = NULL;
    nova->tam = 0;
    No *no = grafo.primeiro;
    Aresta *aresta;
    while (no!=NULL){
        aresta = no->primeira_aresta;
        while (aresta!=NULL){
            insere_l(nova, *no, *aresta);
            aresta = aresta->prox_aresta;
        }
        no = no->proximo_no;
    }
    return nova;
}


/*======================================================
*                     CRIA LISTA VAZIA
--------------------------------------------------------
* Função: Cria uma lista vazia
* Parametros: void
* Retorno: Lista*
======================================================*/
Lista* cria_vazia_l(){
    Lista *nova = (Lista *)malloc(sizeof(Lista));
    nova->head = NULL;
    nova->tam = 0;
    
    return nova;
}


/*======================================================
*                    REMOVE LISTA
--------------------------------------------------------
* Função: Remove uma lista
* Parametros: Lista *l - lista
* Retorno: No_l*
======================================================*/
No_l* remove_l(Lista *l){
    if (l->tam==0){
        return NULL;
    }
    No_l *removido = l->head;
    l->head = l->head->proximo;
    l->tam--;
    return removido;
}

/*======================================================
*                    MOSTRA LISTA
--------------------------------------------------------
* Função: Mostra uma lista
* Parametros: Lista l - lista
* Retorno: void
======================================================*/
void mostra_l(Lista l){
    No_l *no = l.head;
    while (no!=NULL){
        printf("%d - %d - %f \n",no->origem, no->destino, no->peso);
        no = no->proximo;
    }
}

/*======================================================
*                    DESTROI LISTA
--------------------------------------------------------
* Função: Destroi uma lista
* Parametros: Lista *l - lista
* Retorno: void
======================================================*/
void destroi_l(Lista *lista) {
    No_l *atual = lista->head;
    while (atual != NULL) {
        No_l *proximo = atual->proximo; // Salva o próximo nó
        free(atual); // Libera o nó atual
        atual = proximo; // Move para o próximo nó
    }
    free(lista); // Libera a lista em si
}

/*======================================================
*               CRIA MENOR GAP
--------------------------------------------------------
* Função: Cria uma lista de prioridades com os nós que possuem o menor gap
* Parametros: Grafo grafo - grafo a ser analisado
* Retorno: Lista* - ponteiro para a lista de prioridades
======================================================*/
Lista* cria_menor_gap(Grafo grafo){
    Lista *nova = (Lista *)malloc(sizeof(Lista));
    nova->head = NULL;
    nova->tam = 0;
    No *origem = grafo.primeiro;
    No *destino;
    Aresta *aresta;
    while (origem!=NULL){
        if (origem->numero_de_arestas>1){ //o subgrafo não pode ter menos que 2 arestas)
            aresta = origem->primeira_aresta;
            while (aresta!=NULL){
                destino = encontrar_no_por_id(&grafo, aresta->id_alvo);
                if (destino->numero_de_arestas>1){
                    insere_menor_gap(nova,origem->id, destino->id, fabs(origem->peso - destino->peso));
                }
                aresta = aresta->prox_aresta;
            }
        }
        origem = origem->proximo_no;
    }
    return nova;
}

/*======================================================
*               INSERE MENOR GAP
--------------------------------------------------------
* Função: Insere um elemento na lista de prioridades
* Parametros: Lista *l - lista
              unsigned int origem - id do nó de origem
              unsigned int destino - id do nó de destino
              float gap - gap entre os pesos dos nós
* Retorno: void
======================================================*/
void insere_menor_gap(Lista *l, unsigned int origem, unsigned int destino, float gap){
    No_l *novo = (No_l*)malloc(sizeof(No_l));
    novo->origem = origem;
    novo->destino = destino;
    novo->peso = gap;
    l->tam +=1;
    if (l->tam==1){
        l->head = novo;
        novo->proximo = NULL;
        return;
    }
    //Compara com o primeiro
    No_l *atual = l->head;
    if ((atual->origem==origem && atual->destino==destino) || // é a mesma aresta
        (atual->destino==origem && atual->origem==destino)){ //ou a sua recíproca
        free(novo);
    }else if(atual->peso<gap){
        novo->proximo = l->head;
        l->head = novo;
    }else {
        while (atual->proximo!=NULL && atual->proximo->peso>=gap){
            //Se a aresta ou sua recíproca já está em lista, não inclui
            if ((atual->proximo->origem==origem && atual->proximo->destino==destino) || // é a mesma aresta
                (atual->proximo->destino==origem && atual->proximo->origem==destino)){ //ou a sua recíproca
                free(novo);
                break;
            }
            atual = atual->proximo;
        }
        if (atual->proximo==NULL||atual->proximo->peso<gap){
            novo->proximo = atual->proximo;
            atual->proximo = novo;
        }
    }

    
}

/*======================================================
*               REMOVE ARESTA LISTA
--------------------------------------------------------
* Função: Remove uma aresta da lista
* Parametros: Lista *l - lista
              unsigned int origem - id do nó de origem
              unsigned int destino - id do nó de destino
* Retorno: void
======================================================*/
void remover_aresta_l(Lista *l, unsigned int origem, unsigned int destino){
    if (l->tam==0){
        return;
    }
    
    No_l *removido;
    //Se já é o 1o da lista:
    if (l->head->origem==origem && l->head->destino==destino){
        removido = l->head;
        l->head = l->head->proximo;
        free(removido);
        return;
    }
    //Procura no resto da lista
    No_l *atual = l->head;
    while (atual->proximo!=NULL && //até o final da lista
           atual->proximo->peso >= abs((int)origem-(int)destino) ){ //está ordenado por peso
        if (atual->proximo->origem==origem && atual->proximo->destino==destino){
            removido = atual->proximo;
            atual->proximo = atual->proximo->proximo;
            free(removido);
            return;
        }
        atual=atual->proximo;
    }
}

/*======================================================
*               REMOVE NÓ LISTA
--------------------------------------------------------
* Função: Remove um nó da lista
* Parametros: Lista *l - lista
              unsigned int alvo - id do nó a ser removido
* Retorno: void
======================================================*/
void remover_no_l(Lista *l, unsigned int alvo){
    if (l->tam==0){
        return;
    }
    No_l *removido;
    //Se o alvo já é o 1o da lista:
    if (l->head->origem==alvo || l->head->destino==alvo){
        removido = l->head;
        l->head = l->head->proximo;
        free(removido);
        return;
    }
    //Procura no resto da lista
    No_l *atual = l->head;
    while (atual->proximo!=NULL ){
        if (atual->proximo->origem==alvo &&
            atual->proximo->destino==alvo){
            removido = atual->proximo;
            atual->proximo = atual->proximo->proximo;
            free(removido);
        }
        atual=atual->proximo;
    }
}

/*======================================================
*               VERIFICA VAZIA LISTA
--------------------------------------------------------
* Função: Verifica se a lista está vazia
* Parametros: Lista l - lista
* Retorno: int
======================================================*/
int vazia_l(Lista l){
    return l.tam==0;
}
