#include <stdio.h>
#include <stdlib.h>
#include "common/defines.h"
#include "utils/format.h"

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


int main(void) {
  println(D_MSG);
  char matrix[3][3] = {{'-', '-', '-'}, {'-', 'X', '-'}, {'-', '-', 'X'}};
  printf("%d\n", verifyMainDiagonal(3, matrix, 'X'));
  return 0;
}
