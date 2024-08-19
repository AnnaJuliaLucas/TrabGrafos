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
    No_l *novo = (No_l*)malloc(sizeof(No_l));
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
    novo->proximo = atual->proximo;
    atual->proximo = novo;
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
*                     REMOVE LISTA
--------------------------------------------------------
* Função: Remove um elemento da lista
* Parametros: Lista *l
* Retorno: No lista*
======================================================*/
No_l* remove_l(Lista *l){
    if (l->tam==0){
        return NULL;
    }
    No_l *removido = l->head;
    l->head = l->head->proximo;
    return removido;
}


/*======================================================
*                     VAZIA LISTA
--------------------------------------------------------
* Função: Verifica se a lista está vazia
* Parametros: Lista l
* Retorno: int
======================================================*/
void mostra_l(Lista l){
    No_l *no = l.head;
    while (no!=NULL){
        printf("%d - %d - %f \n",no->origem, no->destino, no->peso);
        no = no->proximo;
    }
}
