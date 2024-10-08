#include "../include/Grafo.h"
#include "../include/Algoritmos_Gulosos.h"
#include "Defines.h" // Include the missing header file

/*====================================================== 
*                    ESCOLHA
* Função: escolher a opção do menu
* Recebe: Grafo *grafo
          char opcao
* Retorno: void
* ======================================================*/
// Atualize a função escolha
void escolha1(Grafo *grafo, char opcao)
{
    switch (opcao) {
        case 'a': {
            printf("      Opcao escolhida: FECHO TRANSITIVO DIRETO \n");
            printf("\nEscolha um vertice: ");
            int vertice;
            scanf("%d", &vertice);
            imprimir_fecho(grafo, vertice, "Direto");

            // Gerar arquivo DOT
            char arquivo_dot[50];
            snprintf(arquivo_dot, sizeof(arquivo_dot), "source/dot/fecho_direto_%d.dot", vertice);
            gerar_arquivo_dot(grafo, arquivo_dot);
            break;
        }
        case 'b': {
            printf("      Opcao escolhida: FECHO TRANSITIVO INDIRETO \n");
            printf("\nEscolha um vertice: ");
            int vertice;
            scanf("%d", &vertice);
            imprimir_fecho(grafo, vertice, "Indireto");

            // Gerar arquivo DOT
            char arquivo_dot[50];
            snprintf(arquivo_dot, sizeof(arquivo_dot), "source/dot/fecho_indireto_%d.dot", vertice);
            gerar_arquivo_dot(grafo, arquivo_dot);
            break;
        }
        case 'c': {
            printf("      Opcao escolhida: CAMINHO MINIMO DE DIJKSTRA \n");
            int o, d;
            printf("\nEscolha um vertice de origem: ");
            scanf("%d", &o);
            printf("\nEscolha um vertice de destino: ");
            scanf("%d", &d);

            Grafo g_dijkstra;
            g_dijkstra = caminho_Dijkstra(grafo, o, d);
            if (grafo_vazio(g_dijkstra)) {
                printf("Nao ha caminho entre os nos pedidos\n");
                break;
            } 
            printf("Menor Caminho: \n");
            imprimir_grafo(&g_dijkstra);

            // Gerar arquivo DOT
            char arquivo_dot[50];
            snprintf(arquivo_dot, sizeof(arquivo_dot), "source/dot/dijkstra_%d_%d.dot", o, d);
            gerar_arquivo_dot(&g_dijkstra, arquivo_dot);
            break;
        }
        case 'd': {
            printf("      Opcao escolhida: CAMINHO MINIMO DE FLOYD \n");
            int o, d;
            printf("\nEscolha um vertice de origem: ");
            scanf("%d", &o);
            printf("\nEscolha um vertice de destino: ");
            scanf("%d", &d);

            Grafo g_floyd_warshall;
            g_floyd_warshall = caminho_Floyd(grafo, o, d);

            if (grafo_vazio(g_floyd_warshall)) {
                printf("Nao ha caminho entre os nos pedidos\n");
            } else {
                printf("Menor Caminho: \n");
                imprimir_grafo(&g_floyd_warshall);

                // Gerar arquivo DOT
                char arquivo_dot[50];
                snprintf(arquivo_dot, sizeof(arquivo_dot), "source/dot/floyd_%d_%d.dot", o, d);
                gerar_arquivo_dot(&g_floyd_warshall, arquivo_dot);
            }
            break;
        }
        case 'e' :{
            printf("      Opcao escolhida: ARVORE GERADORA DE PRIM \n");
            Grafo g_Prim;
            g_Prim = AGM_Prim(*grafo);
            if(g_Prim.numero_de_nos == 0){
                printf("Grafo vazio\n");
                break;
            } 
            imprimir_grafo(&g_Prim);

            // Gerar arquivo DOT
            char arquivo_dot[50];
            snprintf(arquivo_dot, sizeof(arquivo_dot), "source/dot/prim.dot");
            gerar_arquivo_dot(&g_Prim, arquivo_dot);
            
            break;
        }
        case 'f': {
            printf("      Opcao escolhida: ARVORE GERADORA DE KRUSKAL \n");
            Grafo g_Kruskal;
            g_Kruskal = AGM_Kruskal(*grafo);
            if (g_Kruskal.numero_de_nos > 0) {
                imprimir_grafo(&g_Kruskal);

                // Gerar arquivo DOT
                char arquivo_dot[50];
                snprintf(arquivo_dot, sizeof(arquivo_dot), "source/dot/kruskal.dot");
                gerar_arquivo_dot(&g_Kruskal, arquivo_dot);
            }
            break;
        }
        case 'g': {
            printf("      Opcao escolhida: CAMINHAMENTO EM PROFUNDIDADE \n");
            printf("\nEscolha um vertice: ");
            int vertice;
            scanf("%d", &vertice);
            printf("\n");
            Grafo resultado = caminhamento_Profundidade(grafo, vertice);
            imprimir_grafo(&resultado);

            // Gerar arquivo DOT
            char arquivo_dot[50];
            snprintf(arquivo_dot, sizeof(arquivo_dot), "source/dot/profundidade.dot");
            gerar_arquivo_dot(&resultado, arquivo_dot);
            break;
        }
        case 'h' : {
            printf("      Opcao escolhida: PROPRIEDADES DO GRAFO \n");
            calcular_propriedades_grafo(grafo);
            break;
        }
        case 'i' :{
            printf("      Opcao escolhida: CONJUNTO DE VERTICES DE ARTICULACAO \n");
            encontra_nos_articulacao(grafo);
            break;
        }
        //------ -----
        case 'j': {
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
        case 'k': {
            printf("      Opcao escolhida: REMOVER NO \n");
            printf("\nEscolha um vertice: ");
            int vertice;
            scanf("%d", &vertice);
            remover_no(grafo, vertice);
            break;
        }
        case 'l': {
            printf("      Opcao escolhida: VERIFICAR CONECTIVIDADE ENTRE DOIS NOS \n");
            printf("\nEscolha um vertice de origem: ");
            int origem;
            scanf("%d", &origem);
            printf("\nEscolha um vertice de destino: ");
            int destino;
            scanf("%d", &destino);

            if (conectado(grafo, origem, destino))
                printf("\nOs vertices %d e %d sao conectados\n", origem, destino);
            else
                printf("\nOs vertices %d e %d nao sao conectados\n", origem, destino);

            // Gerar arquivo DOT (se aplicável)
            break;
        }
        case 'm': {
            printf("      Opcao escolhida: IMPRIMIR GRAFO \n\n");
            imprimir_grafo(grafo);

            // Gerar arquivo DOT
            char arquivo_dot[50];
            snprintf(arquivo_dot, sizeof(arquivo_dot), "source/dot/grafo_impressao.dot");
            gerar_arquivo_dot(grafo, arquivo_dot);
            break;
        }
        case 'x': {
            printf("      OPERACAO CANCELADA \n");
            break;
        }
        default:
            printf("Opcao invalida.\n");
    }
}

void escolha2(Grafo *grafo, char opcao, int p)
{
    (void)p;  

    switch (opcao) {
        case 'a' : {
            printf("      Opcao escolhida: ALGORITMO GULOSO \n");
            Grafo resposta = MGGPP_guloso(grafo,p);
            //imprimir_grafo(&resposta);
            break;
        }
        case 'b' : {
            printf("      Opcao escolhida: ALGORITMO GULOSO RANDOMIZADO\n");

            break;
        }
        case 'C' : {
            printf("      Opcao escolhida: ALGORITMO GULOSO RANDOMIZADO REATIVO\n");

            break;
        }
        
        case 'z': {
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

void menu1(Grafo *grafo){
    char opcao2;	
    
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
    printf("\n Escolha uma opcao (a-m): ");
    scanf(" %c", &opcao2);
    printf("===================================================== \n");
    escolha1(grafo,opcao2);

    while (opcao2 != 'x' && opcao2 != 'X') {
        printf("===================================================== \n");
        printf("Faca uma nova escolha: ");
        scanf(" %c", &opcao2); 
        printf("\n");
        escolha1(grafo,opcao2);
    } 
}

void menu2(Grafo *grafo,int p){
    char opcao2;	
    
    printf("\n======================= MENU  ======================= \n");
    printf("a) Solucao por Algoritmo Guloso\n");
    printf("b) Solucao por Algoritmo Guloso Randomizado\n");
    printf("c) Solucao por Algoritmo Guloso Randomizado Reativo\n");
    printf("z) Imprimir Grafo\n");
    printf("X) SAIR\n");
    printf("\n Escolha uma opcao (a-c): ");
    scanf(" %c", &opcao2);
    printf("===================================================== \n");
    escolha2(grafo,opcao2,p);

}
    
void processar_instancia1(Grafo *grafo, const char *nome_arquivo, const char *diretorio_saida, int op_direc, int op_peso_aresta, int op_peso_nos) {
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
    char caminho_arquivo[strlen("instances_example/Trab1/") + strlen(nome_arquivo) + 1]; // +1 para o caractere nulo
    strcpy(caminho_arquivo, "instances_example/Trab1/");
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
    menu1(grafo);

    // Fechar os arquivos
    fclose(input_file);
    fclose(output_file); 
}

void processar_instancia2( Grafo *grafo, const char *nome_arquivo) {
    //Parâmetros fixos
    char numero[4];
    for (int i=1;i<4;i++){
        numero[i-1]=nome_arquivo[i];
    }
    numero[3]='\0';
    grafo->numero_de_nos = (size_t)atoi(numero);
    grafo->arestas_ponderadas = 0;
    grafo->nos_ponderados = 1;
    grafo->direcionado = 0;
    int p;
    
    printf("\nINSTANCIA: %s\n", nome_arquivo);
    
    // Concatena o diretório de instâncias com o nome do arquivo
    char caminho_arquivo[strlen("instances_example/Trab2/") + strlen(nome_arquivo) + 1]; // +1 para o caractere nulo
    strcpy(caminho_arquivo, "instances_example/Trab2/");
    strcat(caminho_arquivo, nome_arquivo);
    
    // Abre o arquivo de instância
    FILE *input_file = fopen(caminho_arquivo, "r");
    if (input_file == NULL) {
        printf("Erro ao abrir o arquivo de instancia %s.\n",caminho_arquivo);
        return ;
    }
    p = inicializar_grafo_MGGPP(grafo, input_file);
    
    // Chama MENU do Grafo
    menu2(grafo,p);
    
    // Fechar os arquivos
    fclose(input_file);
}

// argc: número de argumentos passados para o programa
// argv: vetor de strings com os argumentos passados para o programa
int main(int argc,char **argv) 
{
    if (argc == 6)
    {
        Grafo grafo;

        // Lendo argumentos
        char *arquivo_entrada = argv[1];
        char *output_file = argv[2];
        int op_direc = atoi(argv[3]);
        int op_peso_aresta = atoi(argv[4]);
        int op_peso_nos = atoi(argv[5]);

        // Processa a instância
        processar_instancia1(&grafo, arquivo_entrada, output_file, op_direc, op_peso_aresta, op_peso_nos);

    }
    else if(argc == 2)
    {
        Grafo grafo;

        // Lendo argumentos
        char *arquivo_entrada = argv[1];
        
        // Processa a instância
        processar_instancia2(&grafo, arquivo_entrada);
    }
    else
    {
        printf("Numero de argumentos invalido\n");
        printf("Uso para o 1º Trab: %s <arquivo_entrada> <output_file> <op_direc> <op_peso_aresta> <op_peso_nos>\n", argv[0]);
        printf("Uso para o 2º Trab: %s <arquivo_entrada>\n", argv[0]);
    }

    return 0;

}
