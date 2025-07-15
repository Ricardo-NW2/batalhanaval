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

// Verifica se as posições estão livres e dentro dos limites
int podeColocar(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int dx, int dy) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + i * dx;
        int c = coluna + i * dy;
        if (l >= TAMANHO || c >= TAMANHO || l < 0 || c < 0 || tabuleiro[l][c] != AGUA) {
            return 0; // Fora dos limites ou sobreposição
        }
    }
    return 1;
}

// Posiciona um navio se possível
void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int dx, int dy) {
    if (podeColocar(tabuleiro, linha, coluna, dx, dy)) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha + i * dx][coluna + i * dy] = NAVIO;
        }
    } else {
        printf("Erro: não foi possível posicionar o navio em (%d, %d) na direção (%d, %d)\n", linha, coluna, dx, dy);
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];

    // Inicializa o tabuleiro com água
    for (int i = 0; i < TAMANHO; i++)
        for (int j = 0; j < TAMANHO; j++)
            tabuleiro[i][j] = AGUA;

    // Posiciona os navios:
    // Horizontal (linha 2, coluna 4)
    posicionarNavio(tabuleiro, 2, 4, 0, 1);

    // Vertical (linha 5, coluna 1)
    posicionarNavio(tabuleiro, 5, 1, 1, 0);

    // Diagonal principal (linha 0, coluna 0)
    posicionarNavio(tabuleiro, 0, 0, 1, 1);

    // Diagonal secundária (linha 0, coluna 9)
    posicionarNavio(tabuleiro, 0, 9, 1, -1);

    // Exibe o tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}
