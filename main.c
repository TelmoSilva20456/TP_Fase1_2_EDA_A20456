
#include <stdio.h>
#include "grafo.h"

// (incluir os headers necessários da Fase 1 aqui)
extern void menuFase1();

int main() {
    int opcao;
    Grafo g;
    inicializarGrafo(&g);

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("--- FASE 1 ---\n");
        printf("1. Inserir antena\n");
        printf("2. Remover antena\n");
        printf("3. Listar antenas\n");
        printf("4. Calcular efeitos nefastos\n");
        printf("5. Ver mapa com efeitos\n");
        printf("6. Carregar configuração\n");
        printf("--- FASE 2 ---\n");
        printf("7. Carregar grafo de antenas\n");
        printf("8. DFS\n");
        printf("9. BFS\n");
        printf("10. Caminhos entre antenas\n");
        printf("11. Interseções entre frequências\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        int origem, destino;
        char freqA, freqB;
        switch(opcao) {
            case 1: case 2: case 3: case 4: case 5: case 6:
                menuFase1(opcao);
                break;
            case 7:
                if (carregarGrafoDeFicheiro(&g, "antenas_base.txt"))
                    printf("Grafo carregado com sucesso.\n");
                else
                    printf("Erro ao carregar o grafo.\n");
                break;
            case 8:
                printf("ID da antena inicial (DFS): ");
                scanf("%d", &origem);
                dfs(&g, origem);
                break;
            case 9:
                printf("ID da antena inicial (BFS): ");
                scanf("%d", &origem);
                bfs(&g, origem);
                break;
            case 10:
                printf("Origem: ");
                scanf("%d", &origem);
                printf("Destino: ");
                scanf("%d", &destino);
                listarTodosCaminhos(&g, origem, destino);
                break;
            case 11:
                printf("Frequência A: ");
                scanf(" %c", &freqA);
                printf("Frequência B: ");
                scanf(" %c", &freqB);
                listarIntersecoes(&g, freqA, freqB);
                break;
            case 0:
                printf("A sair...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
