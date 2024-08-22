#include "../include/Fila.h"
#include "../include/Defines.h"
#include "../include/No.h"


/*======================================================
*                     CRIA FILA
--------------------------------------------------------
* Função: Cria uma fila
* Parametros: void      
* Retorno: void
======================================================*/
Fila* cria_f(void){
    Fila *nova = (Fila*) malloc(sizeof(Fila));
    nova->head = NULL;
    nova->tail = NULL;
    nova->tam = 0;
    return nova;
}


/*======================================================
*                     INSERE FILA
--------------------------------------------------------
* Função: Insere um elemento na fila
* Parametros: Fila *f  - fila    
              No *no_grafo - nó do grafo    
* Retorno: void
======================================================*/
void insere_f(Fila *f,No *no_grafo){
    No_f *novo = (No_f*)malloc(sizeof(No_f));
    novo->vertice = no_grafo;
    novo->proximo = NULL;  // Corrigir a inicialização do ponteiro

    if (vazia_f(*f)) {
        f->head = novo;
        f->tail = novo;
    } else {
        f->tail->proximo = novo;
        f->tail = novo;
    }

    f->tam++;

}


/*======================================================
*                     REMOVE FILA
--------------------------------------------------------
* Função: Remove um elemento da fila
* Parametros: Fila *f      
* Retorno: No*
======================================================*/
No* remove_f(Fila *f){

    if (vazia_f(*f)){
        return (NULL);
    }
    No_f *target = f->head;
    No *vertice = f->head->vertice;
    f->head = f->head->proximo;
    f->tam--;
    free(target);
    return vertice;
}


/*======================================================
*                     MOSTRA FILA
--------------------------------------------------------
* Função: Mostra a fila
* Parametros: Fila f      
* Retorno: int
======================================================*/
int vazia_f(Fila f){
    return (f.tam==0);
}


/*======================================================
*                     CONTÉM FILA
--------------------------------------------------------
* Função: Verifica se a fila contém um elemento
* Parametros: Fila f - fila
              unsigned int id  - id do elemento  
* Retorno: int
======================================================*/
int contem_f(Fila f,unsigned int id){
    No_f *target = f.head;
    while (target!=NULL){
        if (target->vertice->id == id)
            return 1;
    }
    return 0;
}


/*======================================================
*                     DESTROI FILA
--------------------------------------------------------
* Função: Destroi a fila
* Parametros:   Fila *f - fila      
* Retorno: void
======================================================*/
void destroi_f(Fila *f){
    if (vazia_f(*f)){
        free(f);
        return;
    }
    No_f *target = f->head;
    while (f->head!=f->tail){
        f->head = f->head->proximo;
        free(target);
        target = f->head;
    }
    free(f);
}


/*======================================================
*                     MOSTRA FILA
--------------------------------------------------------
* Função: Mostra a fila
* Parametros: Fila f
* Retorno: void
======================================================*/
void mostra_f(Fila f){
    No_f *target = f.head;
    while (target!=NULL){
        printf("%d - ",target->vertice->id);
        target = target->proximo;
    }
    printf("\n");
}
