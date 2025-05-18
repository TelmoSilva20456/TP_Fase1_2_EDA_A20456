
#include <stdio.h>
#include "grafo.h"

int main() {
    Grafo g;
    inicializarGrafo(&g);

    // Carregar grelha do ficheiro
    if (!carregarGrafoDeFicheiro(&g, "antenas_base.txt")) {
        return 1;
    }

    printf("Grafo carregado com sucesso.\n");
    mostrarGrafo(&g);

    printf("\n--- DFS a partir da antena 0 ---\n");
    dfs(&g, 0);

    printf("\n--- BFS a partir da antena 0 ---\n");
    bfs(&g, 0);

    printf("\n--- Caminhos entre antena 0 e 2 ---\n");
    listarTodosCaminhos(&g, 0, 2);

    printf("\n--- Interseções entre A e O ---\n");
    listarIntersecoes(&g, 'A', 'O');

    return 0;
}
