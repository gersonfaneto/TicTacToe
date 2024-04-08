#include <stdio.h>
#include <stdlib.h>

int verifyAlocation(const int* matrix) {
    if(matrix == NULL) {
        printf("Erro: Falha ao alocar memória\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int** initializeMatrix(int lines, int columns) {
    
    int **matrix = (int **) malloc(lines * sizeof(int *));
    verifyAlocation(matrix);
    
    for (int i = 0; i < lines; ++i) {
        matrix[i] = (int *) malloc(columns * sizeof(int));
        verifyAlocation(matrix[i]);
    }

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = '-';
        }
    }
    return matrix;
}