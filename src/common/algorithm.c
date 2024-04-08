#include <stdio.h>
#include <stdlib.h>

char** initializeMatrix(int rows, int columns) {

    char **matrix = (char **)malloc(rows * sizeof(char *));
    if (matrix == NULL) {
        printf("Erro: Falha ao alocar memória\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; ++i) {
        matrix[i] = (char *)malloc(columns * sizeof(char));
        if (matrix[i] == NULL) {
            printf("Erro: Falha ao alocar memória\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = '-';
        }
    }

    return matrix;
}






