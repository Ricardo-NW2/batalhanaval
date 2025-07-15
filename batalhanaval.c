#include <stdio.h>

#define TAMANHO 10     // Tamanho do tabuleiro
#define TAM_NAVIO 3    // Tamanho dos navios
#define AGUA 0         // Representa água
#define NAVIO 3        // Representa parte do navio
#define HABILIDADE 5   // Representa área afetada por habilidade
#define TAM_HAB 5      // Tamanho das matrizes de habilidade (5x5)

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("   ");
    for (int i = 0; i < TAMANHO; i++)
        printf("%2d ", i);
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == AGUA)
                printf(" ~ ");
            else if (tabuleiro[i][j] == NAVIO)
                printf(" N ");
            else if (tabuleiro[i][j] == HABILIDADE)
                printf(" * ");
            else
                printf(" ? "); // fallback
        }
        printf("\n");
    }
}

// Verifica se um navio pode ser colocado
int podeColocar(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int dx, int dy) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + i * dx;
        int c = coluna + i * dy;
        if (l < 0 || l >= TAMANHO || c < 0 || c >= TAMANHO || tabuleiro[l][c] != AGUA)
            return 0;
    }
    return 1;
}

// Coloca o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int dx, int dy) {
    if (podeColocar(tabuleiro, linha, coluna, dx, dy)) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha + i * dx][coluna + i * dy] = NAVIO;
        }
    } else {
        printf("Erro ao posicionar navio em (%d,%d)\n", linha, coluna);
    }
}

// Preenche matriz de habilidade em forma de cone (ponta em cima, base embaixo)
void gerarCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= (TAM_HAB / 2 - i) && j <= (TAM_HAB / 2 + i))
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Preenche matriz de habilidade em forma de cruz (linha e coluna centrais)
void gerarCruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Preenche matriz de habilidade em forma de octaedro (losango)
void gerarOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2) <= TAM_HAB / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Aplica a matriz de habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int matriz[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    int offset = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (matriz[i][j] == 1) {
                int linhaTab = origemLinha + (i - offset);
                int colunaTab = origemColuna + (j - offset);
                if (linhaTab >= 0 && linhaTab < TAMANHO && colunaTab >= 0 && colunaTab < TAMANHO) {
                    if (tabuleiro[linhaTab][colunaTab] == AGUA)
                        tabuleiro[linhaTab][colunaTab] = HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    int cone[TAM_HAB][TAM_HAB], cruz[TAM_HAB][TAM_HAB], octaedro[TAM_HAB][TAM_HAB];

    // Inicializa o tabuleiro
    for (int i = 0; i < TAMANHO; i++)
        for (int j = 0; j < TAMANHO; j++)
            tabuleiro[i][j] = AGUA;

    // Posiciona navios
    posicionarNavio(tabuleiro, 2, 4, 0, 1);  // horizontal
    posicionarNavio(tabuleiro, 5, 1, 1, 0);  // vertical
    posicionarNavio(tabuleiro, 0, 0, 1, 1);  // diagonal principal
    posicionarNavio(tabuleiro, 0, 9, 1, -1); // diagonal secundária

    // Gera matrizes de habilidades
    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    // Aplica habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, cone, 7, 2);
    aplicarHabilidade(tabuleiro, cruz, 4, 5);
    aplicarHabilidade(tabuleiro, octaedro, 2, 2);

    // Exibe tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}
