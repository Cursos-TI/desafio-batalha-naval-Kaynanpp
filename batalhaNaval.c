/*
  batalha_completa.c
  Implementação consolidada dos três níveis do desafio "Batalha Naval":
    - Nível Novato: 2 navios (1 vertical, 1 horizontal) — imprime coordenadas
    - Nível Aventureiro: tabuleiro 10x10, 4 navios (inclui diagonais), imprime matriz (0/3)
    - Nível Mestre: demonstra três padrões de habilidade (cone, cruz, octaedro) em matrizes 5x5 (0/1)

  Como usar:
    gcc batalha_completa.c -o batalha_completa
    ./batalha_completa

  Observações:
    - Valores base (âncoras e tamanhos) estão definidos por variáveis no código.
    - O menu permite executar qualquer nível independentemente.
    - Proteções básicas de limite foram adicionadas para evitar escrita fora da matriz.
*/

#include <stdio.h>
#include <string.h>

#define N_AVENT 10
#define H_MESTRE 5
#define W_MESTRE 5

/* ---------- Utilitários ---------- */

/* Verifica se coordenadas (x,y) estão dentro de um tabuleiro width x height */
int dentro(int x, int y, int width, int height) {
    return (x >= 0 && x < width && y >= 0 && y < height);
}

/* Limpa matriz inteira (int) de tamanho height x width */
void limpar_matriz_int(int mat[][N_AVENT], int height, int width) {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            mat[i][j] = 0;
}

/* Imprime matriz genérica (height x width) com etiqueta e formato inteiro */
void imprimir_matriz_generica_int(int *mat, int height, int width, const char *titulo) {
    printf("%s\n\n", titulo);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            /* matriz linearizada: mat[i*width + j] */
            printf("%d ", *((int *)mat + i * width + j));
        }
        printf("\n");
    }
    printf("\n");
}

/* ---------- NÍVEL NOVATO ---------- */
/* Posiciona e imprime coordenadas de 2 navios (manual via variáveis) */
void nivel_novato(void) {
    printf("=== NÍVEL NOVATO ===\n\n");

    /* Variáveis de entrada (manuais) */
    int navA_x = 2, navA_y = 1, navA_len = 3; /* Navio A: vertical */
    int navB_x = 5, navB_y = 4, navB_len = 4; /* Navio B: horizontal */

    /* Exibição clara e organizada */
    printf("Navio A (vertical) - âncora: (%d,%d) - tamanho: %d\n", navA_x, navA_y, navA_len);
    printf("Partes (x,y):\n");
    for (int i = 0; i < navA_len; ++i) {
        printf("  Parte %d: (%d, %d)\n", i+1, navA_x, navA_y + i);
    }

    printf("\nNavio B (horizontal) - âncora: (%d,%d) - tamanho: %d\n", navB_x, navB_y, navB_len);
    printf("Partes (x,y):\n");
    for (int i = 0; i < navB_len; ++i) {
        printf("  Parte %d: (%d, %d)\n", i+1, navB_x + i, navB_y);
    }

    printf("\n");
}

/* ---------- NÍVEL AVENTUREIRO ---------- */
/* Tabuleiro 10x10, 4 navios (2 diagonais), exibe 0 para livre e 3 para ocupado */
void nivel_aventureiro(void) {
    printf("=== NÍVEL AVENTUREIRO ===\n\n");

    int board[N_AVENT][N_AVENT];
    /* inicializa com zeros */
    for (int i = 0; i < N_AVENT; ++i)
        for (int j = 0; j < N_AVENT; ++j)
            board[i][j] = 0;

    /* Definições manuais (variáveis) - podem ser alteradas no código */
    /* Navio 1: vertical tamanho 3, ancorado em (1,1) */
    int n1_x = 1, n1_y = 1, n1_len = 3;
    /* Navio 2: horizontal tamanho 4, ancorado em (4,2) */
    int n2_x = 4, n2_y = 2, n2_len = 4;
    /* Navio 3: diagonal descendente "\" tamanho 3, ancorado em (6,5) */
    int n3_x = 6, n3_y = 5, n3_len = 3;
    /* Navio 4: diagonal ascendente "/" tamanho 3, ancorado em (2,7) */
    int n4_x = 2, n4_y = 7, n4_len = 3;

    /* Inserção com verificação de limites: marca 3 em posições válidas */
    for (int i = 0; i < n1_len; ++i) {
        int x = n1_x;
        int y = n1_y + i;
        if (dentro(x, y, N_AVENT, N_AVENT)) board[y][x] = 3;
    }
    for (int i = 0; i < n2_len; ++i) {
        int x = n2_x + i;
        int y = n2_y;
        if (dentro(x, y, N_AVENT, N_AVENT)) board[y][x] = 3;
    }
    for (int i = 0; i < n3_len; ++i) {
        int x = n3_x + i;
        int y = n3_y + i;
        if (dentro(x, y, N_AVENT, N_AVENT)) board[y][x] = 3;
    }
    for (int i = 0; i < n4_len; ++i) {
        int x = n4_x + i;
        int y = n4_y - i;
        if (dentro(x, y, N_AVENT, N_AVENT)) board[y][x] = 3;
    }

    /* Exibição do tabuleiro 10x10 (0 = livre, 3 = ocupado) */
    printf("Tabuleiro 10x10 (0=livre, 3=ocupado):\n\n   ");
    for (int j = 0; j < N_AVENT; ++j) printf("%2d ", j);
    printf("\n");
    for (int y = 0; y < N_AVENT; ++y) {
        printf("%2d ", y);
        for (int x = 0; x < N_AVENT; ++x) {
            printf("%2d ", board[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}

/* ---------- NÍVEL MESTRE ---------- */
/* Cria e exibe três padrões (cone, cruz, octaedro) em matrizes 5x5 (0/1) */
void nivel_mestre(void) {
    printf("=== NÍVEL MESTRE ===\n\n");

    int cone[H_MESTRE][W_MESTRE] = {0};
    int cruz[H_MESTRE][W_MESTRE] = {0};
    int octaedro[H_MESTRE][W_MESTRE] = {0};

    /* Preenchimento do padrão CONE (conforme exemplo do enunciado) */
    /* Exemplo visual desejado:
       0 0 1 0 0
       0 1 1 1 0
       1 1 1 1 1
    */
    cone[0][2] = 1;
    cone[1][1] = 1; cone[1][2] = 1; cone[1][3] = 1;
    for (int j = 0; j < W_MESTRE; ++j) cone[2][j] = 1;

    /* Preenchimento do padrão OCTAEDRO (conforme exemplo) */
    /* Exemplo visual:
       0 0 1 0 0
       0 1 1 1 0
       0 0 1 0 0
    */
    octaedro[0][2] = 1;
    octaedro[1][1] = 1; octaedro[1][2] = 1; octaedro[1][3] = 1;
    octaedro[2][2] = 1;

    /* Preenchimento do padrão CRUZ (conforme exemplo) */
    /* Exemplo visual:
       0 0 1 0 0
       1 1 1 1 1
       0 0 1 0 0
    */
    cruz[0][2] = 1;
    for (int j = 0; j < W_MESTRE; ++j) cruz[1][j] = 1;
    cruz[2][2] = 1;

    /* Impressão das matrizes — usando função utilitária genérica */
    imprimir_matriz_generica_int((int *)cone, H_MESTRE, W_MESTRE, "Habilidade: CONE (0=nao afetado, 1=afetado)");
    imprimir_matriz_generica_int((int *)octaedro, H_MESTRE, W_MESTRE, "Habilidade: OCTAEDRO (0=nao afetado, 1=afetado)");
    imprimir_matriz_generica_int((int *)cruz, H_MESTRE, W_MESTRE, "Habilidade: CRUZ (0=nao afetado, 1=afetado)");
}

/* ---------- Programa principal com menu ---------- */
int main(void) {
    int opcao = 0;

    while (1) {
        printf("BATALHA NAVAL - Implementacao Completa\n");
        printf("Selecione o nível para executar:\n");
        printf("  1 - Nível Novato (posicionamento simples)\n");
        printf("  2 - Nível Aventureiro (tabuleiro 10x10, 4 navios)\n");
        printf("  3 - Nível Mestre (padroes de habilidade)\n");
        printf("  0 - Sair\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            /* Leitura inválida: limpa stdin e continua */
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Entrada invalida. Tente novamente.\n\n");
            continue;
        }

        printf("\n");
        switch (opcao) {
            case 1:
                nivel_novato();
                break;
            case 2:
                nivel_aventureiro();
                break;
            case 3:
                nivel_mestre();
                break;
            case 0:
                printf("Encerrando. Obrigado.\n");
                return 0;
            default:
                printf("Opcao invalida. Escolha 0-3.\n\n");
                break;
        }

        /* Separador e pausa leve entre execuções */
        printf("---------\n\n");
    }

    return 0;
}
