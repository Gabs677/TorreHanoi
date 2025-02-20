#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Função para imprimir o estado atual das torres
void imprimirTorres(int **torres, int num_torres, int tamanho[], int movimentos) {
    printf("Movimento #%d\n", movimentos);

    for (int i = 0; i < num_torres; i++) {
        printf("Torre %d: ", i + 1);
        for (int j = 1; j <= tamanho[i]; j++) {
            printf("%d ", torres[i][j]);
        }
        printf("\n");
    }

    printf("------------------\n");
}

// Função para mover um disco de uma torre para outra
void moverDisco(int **torres, int origem, int destino, int *movimentos) {
    int disco = torres[origem][torres[origem][0]];
    torres[origem][0]--;
    torres[destino][0]++;
    torres[destino][torres[destino][0]] = disco;
    (*movimentos)++;
}

int main() {
    int numDiscos;
    int movimentos = 0;

    printf("Digite o numero de discos: ");
    scanf("%d", &numDiscos);

    // Calculando o número mínimo de movimentos
    int movimentosMinimos = pow(2, numDiscos) - 1;
    printf("Numero minimo de movimentos: %d\n", movimentosMinimos);

    // Alocando memória para as torres
    int **torres = (int **)malloc(3 * sizeof(int *));
    if (torres == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Inicializando as torres
    for (int i = 0; i < 3; i++) {
        torres[i] = (int *)malloc((numDiscos + 1) * sizeof(int));
        if (torres[i] == NULL) {
            printf("Erro ao alocar memória.\n");
            return 1;
        }
        torres[i][0] = 0; // Número de discos na torre
    }
    for (int i = numDiscos; i > 0; --i) {
        torres[0][0]++;
        torres[0][torres[0][0]] = i;
    }

    // Imprimindo o estado inicial
    int tamanho_torres[3] = {numDiscos, 0, 0};
    imprimirTorres(torres, 3, tamanho_torres, movimentos);

    // Jogando interativamente
    int origem, destino;
    while (1) {
        printf("Digite a torre de origem (1, 2, 3): ");
        scanf("%d", &origem);
        printf("Digite a torre de destino (1, 2, 3): ");
        scanf("%d", &destino);

        // Validando movimento
        if (origem >= 1 && origem <= 3 && destino >= 1 && destino <= 3 && origem != destino &&
            torres[origem - 1][0] > 0 && (torres[destino - 1][0] == 0 || torres[destino - 1][torres[destino - 1][0]] > torres[origem - 1][torres[origem - 1][0]])) {
            moverDisco(torres, origem - 1, destino - 1, &movimentos);
            tamanho_torres[origem - 1]--;
            tamanho_torres[destino - 1]++;
            imprimirTorres(torres, 3, tamanho_torres, movimentos);
        } else {
            printf("Movimento invalido. Tente novamente.\n");
        }

        // Verificando se o jogo foi resolvido
        if (torres[2][0] == numDiscos) {
            printf("Parabens! Voce resolveu a Torre de Hanoi!\n");
            break;
        }
    }

    // Exibindo resultados
    printf("Torre de Hanoi resolvida em %d movimentos!\n", movimentos);

    // Liberando memória das torres
    for (int i = 0; i < 3; i++) {
        free(torres[i]);
    }
    free(torres);

    return 0;
}

