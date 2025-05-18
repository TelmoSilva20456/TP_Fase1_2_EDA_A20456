
#ifndef GRAFO_H
#define GRAFO_H

#define MAX_VIZINHOS 8
#define MAX_VERTICES 100

typedef struct Antena {
    int id;
    int linha;
    int coluna;
    char frequencia;
} Antena;

typedef struct NoAdjacente {
    int id;
    struct NoAdjacente *prox;
} NoAdjacente;

typedef struct Vertice {
    Antena antena;
    NoAdjacente *adjacentes;
    int visitado;
} Vertice;

typedef struct Grafo {
    Vertice vertices[MAX_VERTICES];
    int numVertices;
} Grafo;

// Funções principais
void inicializarGrafo(Grafo *g);
int adicionarAntena(Grafo *g, int linha, int coluna, char frequencia);
void ligarAntenas(Grafo *g); // criar arestas entre antenas com mesma frequência
void mostrarGrafo(Grafo *g);

// DFS, BFS, Caminhos e Interseções
void dfs(Grafo *g, int origem);
void bfs(Grafo *g, int origem);
void listarTodosCaminhos(Grafo *g, int origem, int destino);
void listarIntersecoes(Grafo *g, char freqA, char freqB);

#endif

int carregarGrafoDeFicheiro(Grafo *g, const char *nomeFicheiro);
