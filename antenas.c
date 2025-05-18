/*!
 *  @file antenas.c
 *  @author Telmo Silva | a20456
 *  @date 2025-03-25
 *  @project Fase 1 - Estruturas de Dados Avançadas
 *
 *  Implementação das funções relacionadas com antenas e efeitos nefastos.
 */

#include "antenas.h"
#include <string.h>
#include <math.h>

// Funções de inicialização
Antena* inicializar_lista() {
    return NULL;
}

char** inicializarMatriz(int linhas, int colunas) {
    char** matriz = (char**)malloc(linhas * sizeof(char*));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (char*)malloc(colunas * sizeof(char));
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = '.';
        }
    }
    return matriz;
}

char** inicializar_matriz_efeito_nefasto(int linhas, int colunas) {
    return inicializarMatriz(linhas, colunas);
}

// Inserção automática das antenas iniciais
void inserir_antenas_iniciais(Antena** lista) {
    *lista = inserirAntena(*lista, 'O', 2, 9);
    *lista = inserirAntena(*lista, 'O', 3, 6);
    *lista = inserirAntena(*lista, 'O', 4, 8);
    *lista = inserirAntena(*lista, 'O', 5, 5);
    *lista = inserirAntena(*lista, 'A', 6, 7);
    *lista = inserirAntena(*lista, 'A', 9, 9);
    *lista = inserirAntena(*lista, 'A', 10, 10);
}

// Funções de manipulação de antenas
Antena* inserirAntena(Antena* lista, char frequencia, int linha, int coluna) {
    if (jaExisteAntena(lista, linha, coluna)) {
        printf("Ja existe uma antena nessa posicao.\n");
        return lista;
    }
    Antena* nova = (Antena*)malloc(sizeof(Antena));
    nova->frequencia = frequencia;
    nova->posicao.linha = linha;
    nova->posicao.coluna = coluna;
    nova->next = lista;
    return nova;
}

Antena* removerAntena(Antena* lista, int linha, int coluna) {
    if (lista == NULL) return NULL;

    if (lista->posicao.linha == linha && lista->posicao.coluna == coluna) {
        Antena* temp = lista->next;
        free(lista);
        return temp;
    }

    Antena* atual = lista;
    while (atual->next != NULL) {
        if (atual->next->posicao.linha == linha && atual->next->posicao.coluna == coluna) {
            Antena* temp = atual->next;
            atual->next = temp->next;
            free(temp);
            break;
        }
        atual = atual->next;
    }
    return lista;
}

// Funções de visualização
void listarAntenas(Antena* lista) {
    printf("\nLista de Antenas:\n");
    printf("Frequencia\tPosicao (linha,coluna)\n");
    printf("----------------------------------------\n");

    while (lista != NULL) {
        printf("%c\t\t(%d,%d)\n", lista->frequencia, lista->posicao.linha, lista->posicao.coluna);
        lista = lista->next;
    }
    printf("----------------------------------------\n");
}

void exibir_matriz_posicionamento(char** matriz, int linhas, int colunas) {
    printf("\nMapa de Posicionamento:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
}

void exibir_matriz_efeito_nefasto(char** matriz, int linhas, int colunas) {
    printf("\nMatriz com Efeitos Nefastos:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
}

// Funções auxiliares para cálculo de efeito nefasto
double calcular_distancia(Coordenada p1, Coordenada p2) {
    int dx = p2.coluna - p1.coluna;
    int dy = p2.linha - p1.linha;
    return sqrt(dx*dx + dy*dy);
}

bool esta_alinhado(Coordenada p1, Coordenada p2, Coordenada p3) {
    int v1x = p2.coluna - p1.coluna;
    int v1y = p2.linha - p1.linha;
    int v2x = p3.coluna - p1.coluna;
    int v2y = p3.linha - p1.linha;

    return (v1x * v2y - v1y * v2x) == 0;
}

bool verificar_interferencia(Antena* antena1, Antena* antena2, Coordenada* ponto) {
    if (antena1->frequencia != antena2->frequencia) return false;

    if (antena1->frequencia == 'a' || antena1->frequencia == 'A') {
        if (esta_alinhado(antena1->posicao, antena2->posicao, *ponto)) {
            double d1 = calcular_distancia(antena1->posicao, *ponto);
            double d2 = calcular_distancia(antena2->posicao, *ponto);

            const double epsilon = 0.0001;
            if (fabs(d1 - 2*d2) < epsilon || fabs(d2 - 2*d1) < epsilon) {
                return true;
            }
        }
    }

    return false;
}

EfeitoNefasto* calcularEfeitoNefasto(Antena* lista, int linhas, int colunas) {
    EfeitoNefasto* resultado = NULL;

    for (Antena* a1 = lista; a1 != NULL; a1 = a1->next) {
        for (Antena* a2 = a1->next; a2 != NULL; a2 = a2->next) {
            if (a1->frequencia != a2->frequencia) continue;

            for (int i = 0; i < linhas; i++) {
                for (int j = 0; j < colunas; j++) {
                    Coordenada ponto = {i + 1, j + 1};
                    if (verificar_interferencia(a1, a2, &ponto) && ponto.linha <= 10 && ponto.coluna <= 10) {
                        bool ja_existe = false;
                        for (EfeitoNefasto* atual = resultado; atual != NULL; atual = atual->next) {
                            if (atual->posicao.linha == ponto.linha && atual->posicao.coluna == ponto.coluna) {
                                ja_existe = true;
                                break;
                            }
                        }

                        if (!ja_existe) {
                            EfeitoNefasto* novo = (EfeitoNefasto*)malloc(sizeof(EfeitoNefasto));
                            novo->posicao = ponto;
                            novo->next = resultado;
                            resultado = novo;
                        }
                    }
                }
            }
        }
    }

    return resultado;
}

// Funções de arquivo
Antena* carregarAntenasDeFicheiro(const char* nome_arquivo, int* linhas, int* colunas) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) return NULL;

    char linha[1000];
    Antena* lista = NULL;
    *linhas = 0;
    *colunas = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        int len = strlen(linha);
        if (linha[len - 1] == '\n') linha[--len] = '\0';
        if (len > *colunas) *colunas = len;
        (*linhas)++;
    }

    rewind(arquivo);

    for (int i = 0; i < *linhas; i++) {
        if (fgets(linha, sizeof(linha), arquivo)) {
            for (int j = 0; linha[j] != '\0' && linha[j] != '\n'; j++) {
                if (linha[j] == 'a' || linha[j] == 'A' || linha[j] == 'O') {
                    lista = inserirAntena(lista, linha[j], i + 1, j + 1);
                }
            }
        }
    }

    fclose(arquivo);
    return lista;
}

void salvar_antenas_arquivo(const char* nome_arquivo, Antena* lista) {
    int max_linha = 0, max_coluna = 0;
    for (Antena* atual = lista; atual != NULL; atual = atual->next) {
        if (atual->posicao.linha > max_linha) max_linha = atual->posicao.linha;
        if (atual->posicao.coluna > max_coluna) max_coluna = atual->posicao.coluna;
    }

    char** matriz = inicializarMatriz(max_linha, max_coluna);

    for (Antena* atual = lista; atual != NULL; atual = atual->next) {
        matriz[atual->posicao.linha - 1][atual->posicao.coluna - 1] = atual->frequencia;
    }

    FILE* arquivo = fopen(nome_arquivo, "w");
    if (arquivo) {
        for (int i = 0; i < max_linha; i++) {
            for (int j = 0; j < max_coluna; j++) {
                fprintf(arquivo, "%c", matriz[i][j]);
            }
            fprintf(arquivo, "\n");
        }
        fclose(arquivo);
    }

    libertarMatriz(matriz, max_linha);
}

// Funções de limpeza
void libertarListaAntenas(Antena* lista) {
    while (lista != NULL) {
        Antena* temp = lista;
        lista = lista->next;
        free(temp);
    }
}

void libertarListaEfeitos(EfeitoNefasto* lista) {
    while (lista != NULL) {
        EfeitoNefasto* temp = lista;
        lista = lista->next;
        free(temp);
    }
}

void libertarMatriz(char** matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}


/**
 * @brief Lista os efeitos nefastos registrados.
 * @param lista Lista ligada de efeitos nefastos.
 */
void listarEfeitos(EfeitoNefasto* lista) {
    printf("\nLocalizacoes com Efeito Nefasto:\n");
    printf("Linha\tColuna\n");
    printf("-------------------\n");

    while (lista != NULL) {
        printf("%d\t%d\n", lista->posicao.linha, lista->posicao.coluna);
        lista = lista->next;
    }
    printf("-------------------\n");
}


/**
 * @brief Verifica se já existe uma antena na posição especificada.
 * @param lista Lista ligada de antenas.
 * @param linha Linha a verificar.
 * @param coluna Coluna a verificar.
 * @return 1 se já existir, 0 caso contrário.
 */
int jaExisteAntena(Antena* lista, int linha, int coluna) {
    while (lista != NULL) {
        if (lista->posicao.linha == linha && lista->posicao.coluna == coluna) {
            return 1;
        }
        lista = lista->next;
    }
    return 0;
}


void atualizarMatrizComEfeitos(char** matriz, EfeitoNefasto* efeitos) {
    while (efeitos != NULL) {
        if (efeitos->posicao.linha <= 10 && efeitos->posicao.coluna <= 10)
            matriz[efeitos->posicao.linha - 1][efeitos->posicao.coluna - 1] = '#';
        efeitos = efeitos->next;
    }
}

void marcarAntenasNaMatriz(char** matriz, Antena* lista) {
    while (lista != NULL) {
        if (lista->posicao.linha <= 10 && lista->posicao.coluna <= 10)
            matriz[lista->posicao.linha - 1][lista->posicao.coluna - 1] = 'a';
        lista = lista->next;
    }
}
