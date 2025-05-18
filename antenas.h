#ifndef ANTENAS_H
#define ANTENAS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Representa uma coordenada na matriz.
 */
typedef struct {
    int linha;
    int coluna;
} Coordenada;

/**
 * @brief Representa uma antena com frequência e posição.
 */
typedef struct Antena {
    char frequencia;
    Coordenada posicao;
    struct Antena* next;
} Antena;

/**
 * @brief Representa um ponto com efeito nefasto.
 */
typedef struct EfeitoNefasto {
    Coordenada posicao;
    struct EfeitoNefasto* next;
} EfeitoNefasto;

Antena* inicializar_lista();
char** inicializarMatriz(int linhas, int colunas);
char** inicializar_matriz_efeito_nefasto(int linhas, int colunas);

Antena* inserirAntena(Antena* lista, char frequencia, int linha, int coluna);
Antena* removerAntena(Antena* lista, int linha, int coluna);

void listarAntenas(Antena* lista);
void exibir_matriz_posicionamento(char** matriz, int linhas, int colunas);
void exibir_matriz_efeito_nefasto(char** matriz, int linhas, int colunas);

EfeitoNefasto* calcularEfeitoNefasto(Antena* lista, int linhas, int colunas);
bool verificar_interferencia(Antena* antena1, Antena* antena2, Coordenada* ponto);

Antena* carregarAntenasDeFicheiro(const char* nome_arquivo, int* linhas, int* colunas);
void salvar_antenas_arquivo(const char* nome_arquivo, Antena* lista);

void libertarListaAntenas(Antena* lista);
void libertarListaEfeitos(EfeitoNefasto* lista);
void libertarMatriz(char** matriz, int linhas);

void inserir_antenas_iniciais(Antena** lista);
void listarEfeitos(EfeitoNefasto* lista);

int jaExisteAntena(Antena* lista, int linha, int coluna);


void atualizarMatrizComEfeitos(char** matriz, EfeitoNefasto* efeitos);
void marcarAntenasNaMatriz(char** matriz, Antena* lista);

#endif // ANTENAS_H
