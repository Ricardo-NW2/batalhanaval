#include <stdio.h>
#include <string.h>

#define TAMANHO 10
#define NAVIO 3
#define HABILIDADE 5
#define TAM_HABILIDADE 5  // Tamanho fixo das matrizes de habilidade (5x5)

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("   ");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == 0) printf(" ~ ");
            else if (tabuleiro[i][j] == NAVIO) printf(" N ");
            else if (tabuleiro[i][j] == HABILIDADE) printf(" * ");
        }
        printf("\n");
    }
}

// Cria matriz de habilidade em forma de cone apontando para baixo
void criarMatrizCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= TAM_HABILIDADE / 2 - i && j <= TAM_HABILIDADE / 2 + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria matriz de habilidade em forma de cruz
void criarMatrizCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == TAM_HABILIDADE / 2 || j == TAM_HABILIDADE / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria matriz de habilidade em forma de octaedro (losango)
void criarMatrizOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - TAM_HABILIDADE / 2) + abs(j - TAM_HABILIDADE / 2) <= TAM_HABILIDADE / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Aplica a matriz de habilidade ao tabuleiro na coordenada central dada
void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int origemLinha, int origemColuna, int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int l = origemLinha - TAM_HABILIDADE / 2 + i;
            int c = origemColuna - TAM_HABILIDADE / 2 + j;

            if (l >= 0 && l < TAMANHO && c >= 0 && c < TAMANHO && matriz[i][j] == 1 && tabuleiro[l][c] != NAVIO) {
                tabuleiro[l][c] = HABILIDADE;
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO] = {0};

    // Posicionamento de navios
    int linha1 = 2, coluna1 = 1;     // Horizontal
    int linha2 = 5, coluna2 = 6;     // Vertical
    int linha3 = 0, coluna3 = 0;     // Diagonal principal
    int linha4 = 0, coluna4 = 9;     // Diagonal inversa

    // Funções de posicionamento
    void posicionarNavio(int t[TAMANHO][TAMANHO], int l, int c, char d) {
        for (int i = 0; i < 3; i++) {
            int nl = l, nc = c;
            if (d == 'H') nc += i;
            else if (d == 'V') nl += i;
            else if (d == 'D') { nl += i; nc += i; }
            else if (d == 'I') { nl += i; nc -= i; }
            if (nl < TAMANHO && nc < TAMANHO && nl >= 0 && nc >= 0)
                t[nl][nc] = NAVIO;
        }
    }

    posicionarNavio(tabuleiro, linha1, coluna1, 'H');
    posicionarNavio(tabuleiro, linha2, coluna2, 'V');
    posicionarNavio(tabuleiro, linha3, coluna3, 'D');
    posicionarNavio(tabuleiro, linha4, coluna4, 'I');

    // Matrizes de habilidade
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    criarMatrizCone(cone);
    criarMatrizCruz(cruz);
    criarMatrizOctaedro(octaedro);

    // Aplicação das habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, 6, 2, cone);
    aplicarHabilidade(tabuleiro, 4, 4, cruz);
    aplicarHabilidade(tabuleiro, 7, 7, octaedro);

    // Exibir tabuleiro final
    printf("\nTabuleiro com habilidades:\n");
    imprimirTabuleiro(tabuleiro);

    return 0;
}
