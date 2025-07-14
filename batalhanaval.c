#include <stdio.h>

#define TAMANHO 10     // Tamanho do tabuleiro 10x10
#define NAVIO 3        // Valor que representa parte do navio
#define TAM_NAVIO 3    // Tamanho fixo dos navios

// Função para imprimir o tabuleiro no console
void imprimirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("   ");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Verifica se é possível posicionar o navio sem ultrapassar os limites nem sobrepor
int podePosicionar(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha;
        int c = coluna;

        if (direcao == 'H') c += i;               // Horizontal
        else if (direcao == 'V') l += i;          // Vertical
        else if (direcao == 'D') { l += i; c += i; } // Diagonal principal \
        else if (direcao == 'I') { l += i; c -= i; } // Diagonal inversa /

        // Verifica limites
        if (l < 0 || l >= TAMANHO || c < 0 || c >= TAMANHO) return 0;

        // Verifica sobreposição
        if (tabuleiro[l][c] == NAVIO) return 0;
    }
    return 1;
}

// Posiciona o navio na direção especificada
void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha;
        int c = coluna;

        if (direcao == 'H') c += i;
        else if (direcao == 'V') l += i;
        else if (direcao == 'D') { l += i; c += i; }
        else if (direcao == 'I') { l += i; c -= i; }

        tabuleiro[l][c] = NAVIO;
    }
}

int main() {
    // Inicializa o tabuleiro com zeros (água)
    int tabuleiro[TAMANHO][TAMANHO] = {0};

    // Coordenadas e direções dos navios
    int linha1 = 2, coluna1 = 1;     // Horizontal
    int linha2 = 5, coluna2 = 6;     // Vertical
    int linha3 = 0, coluna3 = 0;     // Diagonal principal (\)
    int linha4 = 0, coluna4 = 9;     // Diagonal inversa (/)

    // Posicionamento horizontal
    if (podePosicionar(tabuleiro, linha1, coluna1, 'H')) {
        posicionarNavio(tabuleiro, linha1, coluna1, 'H');
    } else {
        printf("Erro: navio horizontal não pode ser posicionado.\n");
    }

    // Posicionamento vertical
    if (podePosicionar(tabuleiro, linha2, coluna2, 'V')) {
        posicionarNavio(tabuleiro, linha2, coluna2, 'V');
    } else {
        printf("Erro: navio vertical não pode ser posicionado.\n");
    }

    // Posicionamento diagonal principal (\)
    if (podePosicionar(tabuleiro, linha3, coluna3, 'D')) {
        posicionarNavio(tabuleiro, linha3, coluna3, 'D');
    } else {
        printf("Erro: navio diagonal principal não pode ser posicionado.\n");
    }

    // Posicionamento diagonal inversa (/)
    if (podePosicionar(tabuleiro, linha4, coluna4, 'I')) {
        posicionarNavio(tabuleiro, linha4, coluna4, 'I');
    } else {
        printf("Erro: navio diagonal inversa não pode ser posicionado.\n");
    }

    // Exibe o tabuleiro final
    printf("\nTabuleiro final:\n");
    imprimirTabuleiro(tabuleiro);

    return 0;
}
