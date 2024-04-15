#include "common/algorithm.h"

#include <stdio.h>
#include <stdlib.h>

/*O JOGO COMEÇA JÁ DEFINDO QUE O PRIMEIRO JOGADOR É O X(XIS) E O SEGUNDO É O O(BOLINHA)*/

int main(void) {
    char playerOne = 'x';
    char playerTwo = 'o';

    int rows = 3; //Número de linhas da matriz
    int cols = 3; //Número de colunas da matriz

    //Inicializando a matriz do tabuleiro
    char **matrix = initializeMatrix(rows, cols);

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
                //int rowSelectedCell = ;******
                //int colSelectedCell = ;******

                if (isEmpty(rowSelectedCell, colSelectedCell, matrix)) {
                    matrix[rowSelectedCell][colSelectedCell] = playerOne;
                    selectionError = 0;
                } else {
                    printf("Essa casa já está ocupada! Selecione novamente.");  
                }
            }

            //Exibindo no tabuleiro o x na casa escolhida


            //Funções que verificam se o jogador 1 ganhou a partida
            win = verifyRows(rows, matrix, playerOne);
            win = verifyColumns(rows, matrix, playerOne);
            win = verifyMainDiagonal(rows, matrix, playerOne);
            win = verifySecundaryDiagonal(rows, matrix, playerOne);
         
        } else {

            //Loop para verificar se a casa selecionada está vazia
            selectionError = 1;
            while (selectionError == 1) {

                //Jogador seleciona a casa do tabuleiro que deseja jogar
                //int rowSelectedCell = ;******
                //int colSelectedCell = ;******

                if (isEmpty(rowSelectedCell, colSelectedCell, matrix)) {
                    matrix[rowSelectedCell][colSelectedCell] = playerTwo;
                    selectionError = 0;
                } else {
                    printf("Essa casa já está ocupada! Selecione novamente.");  
                }
            }
            
            //Exibindo no tabuleiro o x na casa escolhida

            //Funções que verificam se o jogador 2 ganhou a partida
            win = verifyRows(rows, matrix, playerTwo);
            win = verifyColumns(rows, matrix, playerTwo);
            win = verifyMainDiagonal(rows, matrix, playerTwo);
            win = verifySecundaryDiagonal(rows, matrix, playerTwo);
        }

        verifyPlayerTurn += 1; //Acrescenta mais um para indicar que a jogada é do próximo jogador
    }

    //Após o término da partida, verifica quem ganhou ou se houve empate e exibi o resultado
    if (verifyPlayerTurn == 8 && win == 0) {
        printf("EMPATE!");
    } else if (win == 1 && verifyPlayerTurn%2 == 0) {
        printf("JOGADOR 1 GANHOU!");
    } else if (win == 1 && verifyPlayerTurn%2 != 0) {
        printf("JOGADOR 2 GANHOU!");
    }
}