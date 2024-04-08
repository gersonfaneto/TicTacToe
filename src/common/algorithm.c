#include <stdio.h>
#include <stdlib.h>

int verifyAlocation(const int* matrix) {
    if(matrix == NULL) {
        printf("Erro: Falha ao alocar memória\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

char** initializeMatrix(int rows, int columns) {

    char **matrix = (char **)malloc(rows * sizeof(char *));
    if (matrix == NULL) {
        printf("Error allocating memory for matrix rows\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; ++i) {
        matrix[i] = (char *)malloc(columns * sizeof(char));
        if (matrix[i] == NULL) {
            printf("Error allocating memory for matrix columns\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = '-';
        }
    }

    return matrix;
}



