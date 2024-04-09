#include <stdio.h>
#include <stdlib.h>

char** initializeMatrix(int dimension) {

    char **matrix = (char **)malloc(dimension * sizeof(char *));
    if (matrix == NULL) {
        printf("Erro: Falha ao alocar memória\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < dimension; ++i) {
        matrix[i] = (char *)malloc(dimension * sizeof(char));
        if (matrix[i] == NULL) {
            printf("Erro: Falha ao alocar memória\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < dimension; ++j) {
            matrix[i][j] = '-';
        }
    }

    return matrix;
}

int isEmpty(int dimension, int row, int column, char *matrix[dimension]) {
    if(matrix[row][column] == '-') {
        return EXIT_FAILURE; 
    } 
    return EXIT_SUCCESS;
}

int verifyRows(int dimension, char matrix[dimension][dimension], char playerCharacther) {

    int win;

    for(int i = 0; i < dimension; ++i) {
        win = 1;
        for(int j = 0; j < dimension; ++j) {
            if(matrix[i][j] != playerCharacther) {
                win = 0;
                break;
            }
        }
        if(win) {
          return 1;
        }
    }
    return 0;
}

int verifyColumns(int dimension, char matrix[dimension][dimension], char playerCharacther) {
    
    int win;

    for(int i = 0; i < dimension; ++i) {
        win = 1;
        for(int j = 0; j < dimension; ++j) {
            if(matrix[j][i] != playerCharacther) {
                win = 0;
                break;
            }
        }
        if(win) {
          return 1;
        }
    }
    return 0;
}

int verifyMainDiagonal(int dimension, char matrix[dimension][dimension], char playerCharacther) {
    
    int win;

    for(int i = 0; i < dimension; ++i) {
        win = 1;
        if(matrix[i][i] != playerCharacther) {
            win = 0;
            break;
        }
    }
    if(win) {
        return 1;
    }
    return 0;
}

int verigySecundaryDiagonal(int dimension, char matrix[dimension][dimension], char playerCharacther) {

}







