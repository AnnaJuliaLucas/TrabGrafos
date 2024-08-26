#include "../include/Defines.h"
#include "../include/No.h"
#include "../include/Pilha.h"


/* =======================================================
*                    CRIA PILHA
*---------------------------------------------------------
* Função: Cria uma pilha
* Recebe: Void
* Retorno: Pilha criada
* ======================================================*/
Pilha* cria_p(void){
    Pilha *nova = (Pilha*) malloc(sizeof(Pilha));
    nova->head = NULL;
    nova->tam = 0;
    return nova;
}


/* =======================================================
*                    INSERE PILHA
*---------------------------------------------------------
* Função: Insere um elemento na pilha
* Recebe: p - Pilha
*         origem - Origem da aresta
*         destino - Destino da aresta
*         peso - Peso da aresta
* Retorno: Void
* ======================================================*/
void insere_p(Pilha *p,unsigned int origem, unsigned int destino, float peso){
    No_p *novo = (No_p*)malloc(sizeof(No_p));
    novo->origem = origem;
    novo->destino = destino;
    novo->peso = peso;
    novo->proximo = p->head;
    p->head = novo;
    p->tam++;

}


/* =======================================================
*                    REMOVE PILHA
*---------------------------------------------------------
* Função: Remove um elemento da pilha
* Recebe: p - Pilha
* Retorno: No_p - Elemento removido
* ======================================================*/
No_p* remove_p(Pilha *p){

    if (vazia_p(*p)){
        return (NULL);
    }
    No_p *target = p->head;
    p->head = p->head->proximo;
    p->tam--;
    return target;
    
}


/* =======================================================
*                    VAZIA PILHA
*---------------------------------------------------------
* Função: Verifica se a pilha está vazia
* Recebe: f - Pilha
* Retorno: 1 se vazia, 0 se não vazia
* ======================================================*/
int vazia_p(Pilha f){
    return (f.tam==0);
}


/* =======================================================
*                    DESTROI PILHA
*---------------------------------------------------------
* Função: Destroi a pilha
* Recebe: p - Pilha
* Retorno: Void
* ======================================================*/
void destroi_p(Pilha *p){
    if (vazia_p(*p)){
        free(p);
        return;
    }
    No_p *target = p->head;
    while (p->head!=NULL){
        p->head = p->head->proximo;
        free(target);
        target = p->head;
    }
    free(p);
}


/* =======================================================
*                    MOSTRA PILHA
*---------------------------------------------------------
* Função: Mostra a pilha
* Recebe: f - Pilha
* Retorno: Void
* ======================================================*/
void mostra_p(Pilha f){
    No_p *target = f.head;
    while (target!=NULL){
        printf("(%d - %d - %f)",target->origem, target->destino, target->peso);
        target = target->proximo;
    }
    printf("\n");
}
