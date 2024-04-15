#include "common/algorithm.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    char playerOne = 'x';
    char playerTwo = 'o';

    int rows = 3; //Número de linhas da matriz
    int cols = 3; //Número de colunas da matriz

    char **matrix = initializeMatrix(rows, cols); //Inicializando a matriz do tabuleiro

    //variável que indica de qual jogador pertece a jogada atual (números pares - jogador x; números ímpares - jogador o)
    int verifyPlayerTurn = 0;

    //Variável que verifica se alguém ganho o jogo (1 - ganhou; 0 - não ganhou)
    int win = 0;

    //Variáveis que indicam a linha e coluna da casa no tabuleiro, selecionada pelo jogador através do mouse
    int rowSelectedCell;
    int colSelectedCell; //*****FAZER VERIFICAÇÃO SE FOI SELECIONADO UMA CASA JÁ SELECIONADA ANTES

    //verifica se a matriz do tabuleiro está vazia para começar o jogo
    if (isEmpty(rows, cols, matrix)) {

    }

    //Loop principal do jogo, acaba somente quando há uma vitória ou acaba em um empate
    while (win == 0 && verifyPlayerTurn != 8) {

        //Verifica de qual jogador é a vez
        if (verifyPlayerTurn)
        //Jogador seleciona a casa do tabuleiro que deseja jogar
        matrix[rowSelectedCell][colSelectedCell] = 
        
        verifyPlayerTurn += 1;

    }
}