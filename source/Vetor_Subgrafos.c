#include "../include/Vetor_Subgrafos.h"
#include "../include/Defines.h"
#include "../include/Fila.h"
#include "../include/Grafo.h"

/*======================================================
*                 CRIAÇÃO DE VETOR
--------------------------------------------------------
* Função: Cria um vetor de subgrafos
* Parametros: int n - número de nós
* Retorno: Vetor* - ponteiro para o vetor
======================================================*/
Vetor* cria_v(int n){
    Vetor* novo = (Vetor*)malloc(sizeof(Vetor));
    //Para sincronizar o vetor com os nós, vamos começar no 1
    novo->sub =(int*)malloc((n+1)*sizeof(int));
    for( int i=0;i<=n;i++){
        novo->sub[i]=1;
    }
    novo->n_subs = 1;
    return novo;
}

/*======================================================
*               REDIVIDIR SUBGRAFOS
--------------------------------------------------------
* Função: Refaz a divisão dos subgrafos
* Parametros: Vetor *vetor - vetor de subgrafos
              Grafo subs - grafo a ser analisado
              No no1 - nó de origem
              No no2 - nó de destino
* Retorno: void
======================================================*/
void redividir_subs(Vetor *vetor,Grafo subs,No no1, No no2){
    Fila *percorre = cria_f();
    Fila *caminho = cria_f();
    insere_f(percorre,&no1);
    insere_f(caminho,&no1);

    int id_sub =vetor->sub[no1.id];//guarda qual era o valor do subgrafo do no1
    No *no;
    Aresta *aresta;
    No *filho;
    while (!vazia_f(*percorre)){
        no = remove_f(percorre);
        vetor->sub[no->id] = -1; //marcar todo mundo ligado ao no1 como -1
        aresta = no->primeira_aresta;
        for (unsigned int i=0;i<no->numero_de_arestas;i++){
            if (vetor->sub[aresta->id_alvo]!=-1){ //se ainda não marcou o nó
                filho = encontrar_no_por_id(&subs, aresta->id_alvo);
                insere_f(percorre,filho);
                insere_f(caminho,filho);
            }
            aresta = aresta->prox_aresta;

        }
    }
    //se o no2 não está no mesmo subgrafo que o no1, cria um novo id de subgrafoa
    if (vetor->sub[no2.id]!=-1){
        //Cria um novo identificador de subgrafo
        vetor->n_subs++;
        id_sub=vetor->n_subs;
    }
    //Volta todos que foram marcados com -1 para o valor anterior
    while (!vazia_f(*caminho)){
        no = remove_f(caminho);
        vetor->sub[no->id] = id_sub;
    }

    destroi_f(caminho);
    destroi_f(percorre);
   
}
