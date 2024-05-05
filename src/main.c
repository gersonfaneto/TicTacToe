#if 1
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "app/handlers.h"
#include "common/termctl.h"
#include "state.h"
//#include "app/mouse.h"
#include "app/appearance.h"

state_t state;
board_t board;
int main(void) {
  state.is_running = 1;

  state.mouse = init_mouse();
  state.window = init_window();

  //state.mouse.x = state.window.cols / 2;
  //state.mouse.y = state.window.rows / 2;

  set_handlers();

  printf("Starting...\n");

  enter_alt_screen();
  disable_cursor();
  disable_echo();

  i8_t quadrant[2];
  board = init_board();

  while (state.is_running) {
    clear_screen();

    printf_at_xy(0, 1, "Canvas :: [%d, %d]", state.window.cols, state.window.rows);
    printf_at_xy(0, 2, "Mouse  :: [%d, %d]", state.mouse.x, state.mouse.y);
    printf_at_xy(0, 3, "Clicks :: [%d, %d, %d]", state.mouse.left, state.mouse.middle, state.mouse.right);

    quadrant[2] = get_mouse(state.mouse.x, state.mouse.y, board);

    /*for (int i = 0; i < PLAYER_COMPONET_HEIGHT; ++i) {
      if (state.mouse.left) {
        printf_at_xy(((state.window.cols / 2) - (strlen(players[PLAYER_X][i]) / 2) - strlen(players[PLAYER_Y][i])),
                     state.window.rows / 2 + i, "%s", players[PLAYER_X][i]);
        printf_at_xy(((state.window.cols / 2) - (strlen(players[PLAYER_Y][i]) / 2) + strlen(players[PLAYER_X][i])),
                     state.window.rows / 2 + i, "%s", players[PLAYER_Y][i]);
      } else {
        printf_at_xy(((state.window.cols / 2) - (strlen(players[PLAYER_Y][i]) / 2) - strlen(players[PLAYER_X][i])),
                     state.window.rows / 2 + i, "%s", players[PLAYER_Y][i]);
        printf_at_xy(((state.window.cols / 2) - (strlen(players[PLAYER_X][i]) / 2) + strlen(players[PLAYER_Y][i])),
                     state.window.rows / 2 + i, "%s", players[PLAYER_X][i]);
      }
    }*/

    printf_at_xy(state.mouse.x, state.mouse.y, "%c\n", '@');

    state.mouse.read(&state.mouse, state.window.rows, state.window.cols);
  }

  exit_alt_screen();
  enable_cursor();
  enable_echo();

  close(state.mouse.fd);

  printf("Closing...\n");

  return 0;
}
#else

#include "common/algorithm.h"

#include <stdio.h>
#include <stdlib.h>

/*O JOGO COMEÇA JÁ DEFINDO QUE O PRIMEIRO JOGADOR É O X(XIS) E O SEGUNDO É O O(BOLINHA)*/

int main(void) {

    printf("Bem-vindo ao TicTacToe!\n");
    
    char playerOne = 'x';
    char playerTwo = 'o';

    int rows = 3; //Número de linhas da matriz
    int cols = 3; //Número de colunas da matriz

    //Inicializando a matriz do tabuleiro
    char **matrix = init_Matrix(rows, cols);

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


#endif

