#include "../include/Grafo.h"
#include "Defines.h" // Include the missing header file

// void menu(Grafo *grafo){
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
    printf("Escolha uma opcao (a-i): ");
    scanf(" %c", &opcao);
    printf("===================================================== \n");

    
    switch (opcao)
    {
        case 'a': {
            printf("      Opcao escolhida: FECHO TRANSITIVO DIRETO \n");
            printf("\nEscolha um vertice: ");
            int vertice;
            scanf("%d", &vertice);
            fecho_transitivo_direto(grafo, vertice);
            break;
        }
        case 'b': {
            printf("      Opcao escolhida: FECHO TRANSITIVO INDIRETO \n");
            printf("\nEscolha um vertice: ");
            int vertice;
            scanf("%d", &vertice);
            fecho_transitivo_indireto(grafo, vertice);
            break;
        }
        default:
            printf("Opcao invalida.\n");
    }
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
    imprimir_grafo(grafo);

    // Abertura do arquivo de saída
    FILE *output_file = fopen(nome_arquivo_saida, "w");
    if (output_file == NULL) {
        printf("Erro ao criar o arquivo de saída.\n");
        fclose(input_file);
        return;
    }

    printf("ARQUIVO DE SAIDA CRIADO COM SUCESSO!\n");
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
