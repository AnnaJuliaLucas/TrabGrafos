#include "../include/Grafo.h"
#include "Defines.h" // Include the missing header file

/*====================================================== 
*                    ESCOLHA
* Função: escolher a opção do menu
* Recebe: Grafo *grafo
          char opcao
* Retorno: void
* ======================================================*/
void escolha(Grafo *grafo, char opcao)
{
    switch (opcao) {
        case 'a' : {
            printf("      Opcao escolhida: FECHO TRANSITIVO DIRETO \n");
            printf("\nEscolha um vertice: ");
            int vertice;
            scanf("%d", &vertice);
            imprimir_fecho(grafo, vertice, "Direto");
            break;
        }
        case 'b' : {
            printf("      Opcao escolhida: FECHO TRANSITIVO INDIRETO \n");
            printf("\nEscolha um vertice: ");
            int vertice;
            scanf("%d", &vertice);
            imprimir_fecho(grafo, vertice, "Indireto");
            break;
        }
        case 'c':{
            printf("      Opcao escolhida: CAMINHO MINIMO ENTRE DOIS VERTICES USANDO DIJKSTRA \n");
            int origem, destino;
            printf("\nEscolha um vertice de origem: ");
            scanf("%d", &origem);
            printf("Escolha um vertice de destino: ");
            scanf("%d", &destino);

            Grafo g_dijkstra = caminho_Dijkstra(grafo, origem, destino);
            if(grafo_vazio(g_dijkstra))
            {
                printf("Nao existe caminho entre os vertices %d e %d\n", origem, destino);
            }
            else
            {
                printf("Caminho minimo entre %d e %d usando Dijkstra: \n", origem, destino);
                imprimir_grafo(&g_dijkstra);
            }
            break;
        }
        case 'd' :{
            printf("      Opcao escolhida: CAMINHO MINIMO ENTRE DOIS VERTICES USANDO FLOYD \n");
            int origem, destino;
            printf("\nEscolha um vertice de origem: ");
            scanf("%d", &origem);
            printf("Escolha um vertice de destino: ");
            scanf("%d", &destino);

            Grafo g_floyd = caminho_Floyd_Warshall(grafo, origem, destino);
            if(grafo_vazio(g_floyd))
            {
                printf("Nao existe caminho entre os vertices %d e %d\n", origem, destino);
            }
            else
            {
                printf("Caminho minimo entre %d e %d usando Floyd: \n", origem, destino);
                imprimir_grafo(&g_floyd);
            }
            break;
        }
        case 'e' :{
            printf("      Opcao escolhida: ARVORE GERADORA MINIMA USANDO PRIM \n");
            Grafo g_prim = AGM_Prim(*grafo);
            printf("Arvore geradora minima usando Prim: \n");
            imprimir_grafo(&g_prim);
            break;
        }
        case 'f' :{
            printf("      Opcao escolhida: ARVORE GERADORA MINIMA USANDO KRUSKAL \n");
            Grafo g_kruskal = AGM_Kruskal(*grafo);
            printf("Arvore geradora minima usando Kruskal: \n");
            imprimir_grafo(&g_kruskal);
            break;
        }
        case 'g' :{
            printf("      Opcao escolhida: CAMINHAMENTO EM PROFUNDIDADE A PARTIR DE UM VERTICE \n");
            printf("\nEscolha um vertice: ");
            int vertice;
            scanf("%d", &vertice);
            busca_prof(grafo);
            break;
        }
        //------ continuar daqui -----
        case 'j' :{
            printf("      Opcao escolhida: REMOVER ARESTA \n");
            printf("\nEscolha um vertice de origem: ");
            int origem;
            scanf("%d", &origem);
            printf("\nEscolha um vertice de destino: ");
            int destino;
            scanf("%d", &destino);
            remover_aresta(grafo, origem, destino);
            break;
        }
        case 'k' :{
            printf("      Opcao escolhida: REMOVER NO \n");
            printf("\nEscolha um vertice: ");
            int vertice;
            scanf("%d", &vertice);
            remover_no(grafo, vertice);
            break;
        }
        case 'l':{
            printf("      Opcao escolhida: VERIFICAR CONECTIVIDADE ENTRE DOIS NOS \n");
            printf("\nEscolha um vertice de origem: ");
            int origem;
            scanf("%d", &origem);
            printf("\nEscolha um vertice de destino: ");
            int destino;
            scanf("%d", &destino);

            if(conectado(grafo, origem, destino))
                printf("\nOs vertices %d e %d sao conectados.\n", origem, destino);
            else
                printf("\nOs vertices %d e %d nao sao conectados.\n", origem, destino);
            
            break;
        }
        case 'm': {
            printf("      Opcao escolhida: IMPRIMIR GRAFO \n\n");
            imprimir_grafo(grafo); 
            break;
        }
        case 'x':{
            printf("      OPERACAO CANCELADA \n");
            break;
        }
        default:
            printf("Opcao invalida.\n");
        
    }
}

// void menu(Grafo *grafo)
void menu(Grafo *grafo){
    char opcao;	
    
    printf("\n======================= MENU  ======================= \n");
    printf("a) Fecho Transitivo Direto\n");
    printf("b) Fecho Transitivo Indireto\n");
    printf("c) Caminho Minimo entre dois vertices usando Dijkstra\n");
    printf("d) Caminho Minimo entre dois vertices usando Floyd\n");
    printf("e) Arvore Geradora Minima usando Prim\n");
    printf("f) Arvore Geradora Minima usando Kruskal\n");
    printf("g) Caminhamento em Profundidade a partir de um vertice\n");
    printf("h) Propriedades do grafo (raio, diametro, centro, periferia)\n");
    printf("i) Conjunto de Vertices de Articulacao\n");
    printf("j) Remover aresta\n");
    printf("k) Remover no\n");
    printf("l) Verificar conectividade entre dois nos\n");
    printf("m) Imprimir grafo\n");
    printf("X) SAIR\n");
    printf("\n Escolha uma opcao (a-i): ");
    scanf(" %c", &opcao);
    printf("===================================================== \n");
    escolha(grafo,opcao);

    do{
        printf("===================================================== \n");
        printf("Faca uma nova escolha: ");
        scanf(" %c", &opcao); 
        printf("\n");
        escolha(grafo,opcao);
    } while(opcao != 'x' && opcao != 'X');
}


void processar_instancia(Grafo *grafo, const char *nome_arquivo, const char *diretorio_saida, int op_direc, int op_peso_aresta, int op_peso_nos) {
    printf("\nINSTANCIA: %s\n", nome_arquivo);
  
    // Extrair apenas o nome do arquivo de entrada (sem o caminho)
    char *nome_arquivo_sem_caminho = basename((char *) nome_arquivo);

    // Concatenar o diretório de saída com o nome do arquivo de entrada (removendo a extensão .dat) e a extensão .txt
    char nome_arquivo_saida[strlen(diretorio_saida) + strlen(nome_arquivo_sem_caminho) + 5]; // +5 para ".txt" e o caractere nulo
    strcpy(nome_arquivo_saida, diretorio_saida);
    strncat(nome_arquivo_saida, nome_arquivo_sem_caminho, strlen(nome_arquivo_sem_caminho) - 4); // Remove a extensão .dat
    strcat(nome_arquivo_saida, ".txt");

    printf("ARQUIVO DE SAIDA: %s\n", nome_arquivo_saida);

    // Concatena o diretório de instâncias com o nome do arquivo
    char caminho_arquivo[strlen("instances_example/") + strlen(nome_arquivo) + 1]; // +1 para o caractere nulo
    strcpy(caminho_arquivo, "instances_example/");
    strcat(caminho_arquivo, nome_arquivo);

    // Abre o arquivo de instância
    FILE *input_file = fopen(caminho_arquivo, "r");
    if (input_file == NULL) {
        printf("Erro ao abrir o arquivo de instancia.\n");
        return;
    }

    // Lê o cabeçalho do arquivo de instância
    printf("GRAFO: ");
    if(op_direc == 1)
    {
        grafo->direcionado = 1;
        printf("Direcionado\n");
    } else {
        grafo->direcionado = 0;
        printf("Nao direcionado\n");
    }
    
    printf("ARESTAS: ");
    if(op_peso_aresta == 1)
    {
        grafo->arestas_ponderadas = 1;
        printf("Ponderadas\n");
    } else {
        grafo->arestas_ponderadas = 0;
        printf("Nao Ponderadas\n");
    }

    printf("NOS: ");
    if(op_peso_nos == 1)
    {
        grafo->nos_ponderados = 1;
        printf("Ponderados\n\n");
    } else {
        grafo->nos_ponderados = 0;
        printf("Nao Ponderados\n\n");
    }

    // Inicializa o grafo com o arquivo de instância
    char confirmacao;
    printf("Confirma? S/N ");
    scanf("%c", &confirmacao);
    if(confirmacao == 'N' || confirmacao == 'n')
    {
        printf("Operacao cancelada\n");
        return;
    }

    inicializar_grafo_com_arquivo(grafo, input_file); 

    // Ler e processar o arquivo de instância

    // Abertura do arquivo de saída
    FILE *output_file = fopen(nome_arquivo_saida, "w");
    if (output_file == NULL) {
        printf("Erro ao criar o arquivo de saída.\n");
        fclose(input_file);
        return;
    }

    printf("\n ARQUIVO DE SAIDA CRIADO COM SUCESSO!\n");
    inicializa_graus(grafo);
    // Escrever o resultado no arquivo de saída
    imprimir_grafo_em_arquivo(grafo, output_file);

    // Chama MENU do Grafo
    menu(grafo);

    // Fechar os arquivos
    fclose(input_file);
    fclose(output_file); 
}

// argc: número de argumentos passados para o programa
// argv: vetor de strings com os argumentos passados para o programa
int main(int argc,char **argv) 
{
    // Verifica os argumentos passados
    if (argc < 6) {
        printf(" PADRAO: %s <arquivo_entrada> <output_file> <Op_Direc> <Op_PesoAresta> <Op_PesoNos>\n", argv[0]);
        return 1;
    }

    Grafo grafo;

    // Lendo argumentos
    char *arquivo_entrada = argv[1];
    char *output_file = argv[2];
    int op_direc = atoi(argv[3]);
    int op_peso_aresta = atoi(argv[4]);
    int op_peso_nos = atoi(argv[5]);
   
    // Processa a instância
    processar_instancia(&grafo, arquivo_entrada, output_file, op_direc, op_peso_aresta, op_peso_nos);

    return 0;

}
