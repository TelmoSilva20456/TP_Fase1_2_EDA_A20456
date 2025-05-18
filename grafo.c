
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

void inicializarGrafo(Grafo *g) {
    g->numVertices = 0;
}

int adicionarAntena(Grafo *g, int linha, int coluna, char frequencia) {
    if (g->numVertices >= MAX_VERTICES) return -1;

    int id = g->numVertices;
    g->vertices[id].antena.id = id;
    g->vertices[id].antena.linha = linha;
    g->vertices[id].antena.coluna = coluna;
    g->vertices[id].antena.frequencia = frequencia;
    g->vertices[id].adjacentes = NULL;
    g->vertices[id].visitado = 0;

    g->numVertices++;
    return id;
}

void adicionarAresta(Grafo *g, int origem, int destino) {
    NoAdjacente *novo = malloc(sizeof(NoAdjacente));
    novo->id = destino;
    novo->prox = g->vertices[origem].adjacentes;
    g->vertices[origem].adjacentes = novo;
}

void ligarAntenas(Grafo *g) {
    for (int i = 0; i < g->numVertices; i++) {
        for (int j = i + 1; j < g->numVertices; j++) {
            if (g->vertices[i].antena.frequencia == g->vertices[j].antena.frequencia) {
                adicionarAresta(g, i, j);
                adicionarAresta(g, j, i);
            }
        }
    }
}

void mostrarGrafo(Grafo *g) {
    for (int i = 0; i < g->numVertices; i++) {
        Antena a = g->vertices[i].antena;
        printf("Antena %d (%d,%d) [%c] -> ", a.id, a.linha, a.coluna, a.frequencia);

        NoAdjacente *adj = g->vertices[i].adjacentes;
        while (adj) {
            printf("%d ", adj->id);
            adj = adj->prox;
        }
        printf("\n");
    }
}


// Reset de visitados
void resetVisitados(Grafo *g) {
    for (int i = 0; i < g->numVertices; i++)
        g->vertices[i].visitado = 0;
}

// DFS
void dfsVisit(Grafo *g, int v) {
    g->vertices[v].visitado = 1;
    Antena a = g->vertices[v].antena;
    printf("(%d,%d) [%c]\n", a.linha, a.coluna, a.frequencia);

    NoAdjacente *adj = g->vertices[v].adjacentes;
    while (adj) {
        if (!g->vertices[adj->id].visitado) {
            dfsVisit(g, adj->id);
        }
        adj = adj->prox;
    }
}

void dfs(Grafo *g, int origem) {
    resetVisitados(g);
    printf("DFS a partir da antena %d:\n", origem);
    dfsVisit(g, origem);
}

// BFS
#include <stdbool.h>

void bfs(Grafo *g, int origem) {
    resetVisitados(g);
    int fila[MAX_VERTICES];
    int inicio = 0, fim = 0;

    fila[fim++] = origem;
    g->vertices[origem].visitado = 1;

    printf("BFS a partir da antena %d:\n", origem);

    while (inicio < fim) {
        int v = fila[inicio++];
        Antena a = g->vertices[v].antena;
        printf("(%d,%d) [%c]\n", a.linha, a.coluna, a.frequencia);

        NoAdjacente *adj = g->vertices[v].adjacentes;
        while (adj) {
            if (!g->vertices[adj->id].visitado) {
                fila[fim++] = adj->id;
                g->vertices[adj->id].visitado = 1;
            }
            adj = adj->prox;
        }
    }
}

// Caminhos
void caminhosAux(Grafo *g, int atual, int destino, int caminho[], int pos) {
    g->vertices[atual].visitado = 1;
    caminho[pos++] = atual;

    if (atual == destino) {
        printf("Caminho: ");
        for (int i = 0; i < pos; i++) {
            Antena a = g->vertices[caminho[i]].antena;
            printf("(%d,%d) ", a.linha, a.coluna);
        }
        printf("\n");
    } else {
        NoAdjacente *adj = g->vertices[atual].adjacentes;
        while (adj) {
            if (!g->vertices[adj->id].visitado)
                caminhosAux(g, adj->id, destino, caminho, pos);
            adj = adj->prox;
        }
    }

    g->vertices[atual].visitado = 0;
}

void listarTodosCaminhos(Grafo *g, int origem, int destino) {
    int caminho[MAX_VERTICES];
    resetVisitados(g);
    printf("Todos os caminhos de %d para %d:\n", origem, destino);
    caminhosAux(g, origem, destino, caminho, 0);
}

// Interseções entre antenas com frequência A e B
void listarIntersecoes(Grafo *g, char freqA, char freqB) {
    printf("Interseções entre frequências %c e %c:\n", freqA, freqB);
    for (int i = 0; i < g->numVertices; i++) {
        for (int j = i + 1; j < g->numVertices; j++) {
            if ((g->vertices[i].antena.frequencia == freqA &&
                 g->vertices[j].antena.frequencia == freqB) ||
                (g->vertices[i].antena.frequencia == freqB &&
                 g->vertices[j].antena.frequencia == freqA)) {
                printf("(%d,%d) [%c] <-> (%d,%d) [%c]\n",
                    g->vertices[i].antena.linha, g->vertices[i].antena.coluna, g->vertices[i].antena.frequencia,
                    g->vertices[j].antena.linha, g->vertices[j].antena.coluna, g->vertices[j].antena.frequencia);
            }
        }
    }
}

int carregarGrafoDeFicheiro(Grafo *g, const char *nomeFicheiro) {
    FILE *f = fopen(nomeFicheiro, "r");
    if (!f) {
        printf("Erro ao abrir o ficheiro %s\n", nomeFicheiro);
        return 0;
    }

    char linha[1024];
    int l = 0;
    while (fgets(linha, sizeof(linha), f)) {
        for (int c = 0; linha[c] != '\0' && linha[c] != '\n'; c++) {
            char ch = linha[c];
            if (ch != '.' && ch != ' ' && ch != '0') {
                adicionarAntena(g, l, c, ch);
            }
        }
        l++;
    }

    fclose(f);
    ligarAntenas(g);
    return 1;
}
