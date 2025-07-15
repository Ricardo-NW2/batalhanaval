#include <stdio.h>

#define TAMANHO 10     // Tamanho do tabuleiro (10x10)
#define TAM_NAVIO 3    // Tamanho fixo dos navios
#define NAVIO 3        // Valor que representa parte do navio
#define AGUA 0         // Valor que representa água

// Função para imprimir o tabuleiro no console
void imprimirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("   ");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i);  // Cabeçalho de colunas
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i);  // Cabeçalho de linhas
        for (int j = 0; j < TAMANHO; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];

    // Inicializa todas as posições do tabuleiro com água (0)
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Vetores para representar os navios (usado só para exemplo)
    int navioHorizontal[TAM_NAVIO] = {NAVIO, NAVIO, NAVIO};
    int navioVertical[TAM_NAVIO] = {NAVIO, NAVIO, NAVIO};

    // Coordenadas iniciais dos navios (definidas diretamente no código)
    int linhaH = 2, colunaH = 4;  // Navio horizontal começa na linha 2, coluna 4
    int linhaV = 5, colunaV = 1;  // Navio vertical começa na linha 5, coluna 1

    // Valida se o navio horizontal cabe no tabuleiro
    if (colunaH + TAM_NAVIO <= TAMANHO) {
        int sobreposicao = 0;

        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaH][colunaH + i] != AGUA) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaH][colunaH + i] = navioHorizontal[i];
            }
        } else {
            printf("Erro: sobreposição detectada no navio horizontal.\n");
        }
    } else {
        printf("Erro: navio horizontal fora dos limites.\n");
    }

    // Valida se o navio vertical cabe no tabuleiro
    if (linhaV + TAM_NAVIO <= TAMANHO) {
        int sobreposicao = 0;

        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaV + i][colunaV] != AGUA) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaV + i][colunaV] = navioVertical[i];
            }
        } else {
            printf("Erro: sobreposição detectada no navio vertical.\n");
        }
    } else {
        printf("Erro: navio vertical fora dos limites.\n");
    }

    // Exibe o tabuleiro com os navios posicionados
    imprimirTabuleiro(tabuleiro);

    return 0;
}
