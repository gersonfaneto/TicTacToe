//#include "common/algorithm.h"

#include <stdio.h>
#include <stdlib.h>

/*Esta função aloca dinamicamente uma matriz de caracteres (char) com o 
  número de linhas especificado em rows e o número de colunas especificado em cols.*/

char **initializeMatrix(int rows, int cols) {
  char **matrix = (char **)malloc(rows * sizeof(char *));

  if (matrix == NULL) {
    printf("Erro: Falha ao alocar memória\n");
    exit(EXIT_FAILURE);
  }

  int i, j;
  for (i = 0; i < rows; ++i) {
    matrix[i] = (char *)malloc(cols * sizeof(char));
    if (matrix[i] == NULL) {
      printf("Erro: Falha ao alocar memória\n");
      exit(EXIT_FAILURE);
    }
    for (j = 0; j < cols; ++j) {
      matrix[i][j] = '-';
      printf("%d,%d\n", i, j);
    }
  }

  return matrix;
}

/**/
int isEmpty(int row, int column, char **matrix) {
  if (matrix[row][column] == '-') {
    return 1;
  }
  return 0;
}

/*Esta função verifica se o jogador representado pelo caractere playerCharacther ganhou em alguma linha da matriz.*/
int verifyRows(int dimension, char **matrix, char playerCharacther) {
  int win;

  for (int i = 0; i < dimension; ++i) {
    win = 1;
    for (int j = 0; j < dimension; ++j) {
      if (matrix[i][j] != playerCharacther) {
        win = 0;
        break;
      }
    }
    if (win) {
      return 1;
    }
  }
  return 0;
}

/*Esta função verifica se o jogador ganhou em alguma coluna da matriz.*/
int verifyColumns(int dimension, char **matrix, char playerCharacther) {
  int win;

  for (int i = 0; i < dimension; ++i) {
    win = 1;
    for (int j = 0; j < dimension; ++j) {
      if (matrix[j][i] != playerCharacther) {
        win = 0;
        break;
      }
    }
    if (win) {
      return 1;
    }
  }
  return 0;
}

/*Esta função verifica se o jogador ganhou na diagonal principal da matriz.*/
int verifyMainDiagonal(int dimension, char **matrix, char playerCharacther) {
  int win;

  for (int i = 0; i < dimension; ++i) {
    win = 1;
    if (matrix[i][i] != playerCharacther) {
      win = 0;
      break;
    }
  }
  if (win) {
    return 1;
  }
  return 0;
}

/*Esta função verifica se o jogador ganhou na diagonal secundária da matriz.*/
int verifySecundaryDiagonal(int dimension, char **matrix, char playerCharacther) {
  int win = 1;

  for (int i = 0; i < dimension; ++i) {
    if (matrix[i][dimension - 1 - i] != playerCharacther) {
      win = 0;
      break;
    }
  }
  if (win) {
    return 1;
  }
  return 0;
}

/*Função para imprimir a matriz no terminal (somente para a fase de testes iniciais)*/
int showMatrix(int dimension, char **matrix) {
    int i, j;
    printf("\n");
    for (i = 0; i<dimension; i++) {
        for (j = 0; j<dimension; j++) {
            printf("| %c |", matrix[i][j]);
        }
        printf("\n");
    }
}



/*O JOGO COMEÇA JÁ DEFINDO QUE O PRIMEIRO JOGADOR É O X(XIS) E O SEGUNDO É O O(BOLINHA)*/

int main(void) {

    printf("Bem-vindo ao TicTacToe!\n");
    
    char playerOne = 'x';
    char playerTwo = 'o';

    int rows = 3; //Número de linhas da matriz
    int cols = 3; //Número de colunas da matriz

    //Inicializando a matriz do tabuleiro
    char **matrix = initializeMatrix(rows, cols);

    showMatrix(rows, matrix);

    //variável que indica de qual jogador pertece a jogada atual (números pares - jogador x; números ímpares - jogador o)
    int verifyPlayerTurn = 0;

    //Variável que verifica se alguém ganho o jogo (1 - ganhou; 0 - não ganhou)
    int win = 0;

    //Variáveis que indicam a linha e coluna da casa no tabuleiro, selecionada pelo jogador através do mouse
    int rowSelectedCell;
    int colSelectedCell;
    int selectionError = 1; //Para o loop de verificação se a casa selecionada está vazia

    //verifica se a matriz do tabuleiro está vazia para começar o jogo
    int i;
    for (i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] != '-') {
                printf("Erro: Tabuleiro não está vazio!");
            }
        }
    }

    //Loop principal do jogo, acaba somente quando há uma vitória ou acaba em um empate
    while (win == 0 && verifyPlayerTurn != 8) {

        //Verifica de qual jogador é a vez
        if (verifyPlayerTurn%2 == 0) {

            //Loop para verificar se a casa selecionada está vazia
            selectionError = 1;
            while (selectionError == 1) {

                //Jogador seleciona a casa do tabuleiro que deseja jogar
                scanf("%d,%d", &rowSelectedCell, &colSelectedCell);

                if (isEmpty(rowSelectedCell, colSelectedCell, matrix) == 1) {
                    matrix[rowSelectedCell][colSelectedCell] = playerOne;
                    selectionError = 0;
                } else {
                    printf("Essa casa já está ocupada! Selecione novamente.");
                    selectionError = 1;
                }
                getchar();
            }

            //Exibindo no tabuleiro o x na casa escolhida
            showMatrix(rows, matrix);

            //Funções que verificam se o jogador 1 ganhou a partida
            win = verifyRows(rows, matrix, playerOne);
            if (win == 1){break;}
            win = verifyColumns(rows, matrix, playerOne);
            if (win == 1){break;}
            win = verifyMainDiagonal(rows, matrix, playerOne);
            if (win == 1){break;}
            win = verifySecundaryDiagonal(rows, matrix, playerOne);
            if (win == 1){break;}
         
        } else {

            //Loop para verificar se a casa selecionada está vazia
            selectionError = 1;
            while (selectionError == 1) {

                //Jogador seleciona a casa do tabuleiro que deseja jogar
                scanf("%d,%d", &rowSelectedCell, &colSelectedCell);

                if (isEmpty(rowSelectedCell, colSelectedCell, matrix) == 1) {
                    matrix[rowSelectedCell][colSelectedCell] = playerTwo;
                    selectionError = 0;
                } else {
                    printf("Essa casa já está ocupada! Selecione novamente.");
                    selectionError = 1;
                }
                getchar();
            }
            
            //Exibindo no tabuleiro o x na casa escolhida
            showMatrix(rows, matrix);

            //Funções que verificam se o jogador 2 ganhou a partida
            win = verifyRows(rows, matrix, playerTwo);
            if (win == 1){break;}
            win = verifyColumns(rows, matrix, playerTwo);
            if (win == 1){break;}
            win = verifyMainDiagonal(rows, matrix, playerTwo);
            if (win == 1){break;}
            win = verifySecundaryDiagonal(rows, matrix, playerTwo);
            if (win == 1){break;}
        }

        verifyPlayerTurn += 1; //Acrescenta mais um para indicar que a jogada é do próximo jogador
    }

    //Após o término da partida, verifica quem ganhou ou se houve empate e exibi o resultado
    if (verifyPlayerTurn == 8 && win == 0) {
        printf("EMPATE!\n");
    } else if (win == 1 && verifyPlayerTurn%2 == 0) {
        printf("JOGADOR 1 GANHOU!\n");
    } else if (win == 1 && verifyPlayerTurn%2 != 0) {
        printf("JOGADOR 2 GANHOU!\n");
    }
}
