/*!
 *  @file main_sem_menu.c
 *  @author Telmo Silva | a20456
 *  @date 2025-03-25
 *  @project Fase 1 - Estruturas de Dados Avançadas
 *
 *  Versão automática do programa sem menu.
 */


#include "antenas.h"
#include <stdio.h>

int main() {
    int linhas = 0, colunas = 0;

    // 1. Carregar antenas a partir de ficheiro antenas.txt
    Antena* lista = carregarAntenasDeFicheiro("antenas_base.txt", &linhas, &colunas);

    if (lista == NULL) {
        printf("Erro ao carregar as antenas do ficheiro.\n");
        return 1;
    }

    // 2. Inserir e remover antenas diretamente no código
    // Remover antena 'A' da posição (5,6)
    //lista = removerAntena(lista, 5, 6);

    // Inserir nova antena 'O' na posição (5,6)
    //lista = inserirAntena(lista, 'O', 5, 6);

    // Inserir mais uma antena 'O' em (6,6)
    lista = inserirAntena(lista, 'O', 6, 6);

    // 3. Mostrar lista atualizada de antenas
    printf("Lista de Antenas atualizada:\n");
    listarAntenas(lista);

    // 4. Calcular efeitos nefastos
    EfeitoNefasto* efeitos = calcularEfeitoNefasto(lista, 10, 10);

    // 5. Mostrar lista de efeitos nefastos
    printf("\nEfeitos Nefastos calculados:\n");
    listarEfeitos(efeitos);

    // 6. Mostrar matriz de efeito nefasto
    char** matriz = inicializarMatriz(10, 10);
    atualizarMatrizComEfeitos(matriz, efeitos);
    marcarAntenasNaMatriz(matriz, lista);

    printf("\nMapa de Efeito Nefasto (10x10):\n");
    printf("   ");
    for (int j = 1; j <= 10; j++) printf("%d ", j);
    printf("\n");
    for (int i = 0; i < 10; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < 10; j++) {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }

    // 7. Libertar memória
    libertarListaAntenas(lista);
    libertarListaEfeitos(efeitos);
    libertarMatriz(matriz, 10);

    return 0;
}
