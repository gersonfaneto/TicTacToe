#include "appearance.h"
#include "common/algorithm.h"
#include "state.h"
#include "common/termctl.h"

quadrant_t init_quadrant() {

    return (quadrant_t) {
        .width = PLAYER_COMPONENT_WIDTH + SPACE_WIDTH_BORDER,
        .height = PLAYER_COMPONENT_HEIGHT + SPACE_HEIGHT_BORDER,
    };
}

board_t init_board() {

    quadrant_t quadrant = init_quadrant();

    return (board_t) {
        .matrix = {{'-','-','-'}, {'-','-','-'}, {'-','-','-'}},
        .row0 = (state.window.rows * 0.5) - (quadrant.height * 1.5),
        .row1 = (state.window.rows * 0.5) - (quadrant.height * 0.5),
        .row2 = (state.window.rows * 0.5) + (quadrant.height * 0.5),
        .row3 = (state.window.rows * 0.5) + (quadrant.height * 1.5),

        .col0 = (state.window.cols * 0.5) - (quadrant.width * 1.5),
        .col1 = (state.window.cols * 0.5) - (quadrant.width * 0.5),
        .col2 = (state.window.cols * 0.5) + (quadrant.width * 0.5),
        .col3 = (state.window.cols * 0.5) + (quadrant.width * 1.5),
    };
}

void show_contour(i8_t dimension, board_t board) {
    i16_t col_size = 3 * (PLAYER_COMPONENT_HEIGHT + SPACE_HEIGHT_BORDER);

    for(i8_t i = 0; i <= col_size; ++i) {
       printf_at_xy(board.col0, (board.row0 + i), "|"); 
       printf_at_xy(board.col1, (board.row0 + i), "|");
       printf_at_xy(board.col2, (board.row0 + i), "|");
       printf_at_xy(board.col3, (board.row0 + i), "|");
    }

    i16_t row_size = 3 * (PLAYER_COMPONENT_WIDTH + SPACE_WIDTH_BORDER);
    
    for(i8_t j = 0; j <= row_size; ++j) {
       printf_at_xy(board.col0 + j, board.row0, "-"); 
       printf_at_xy(board.col0 + j, board.row1, "-");
       printf_at_xy(board.col0 + j, board.row2, "-");
       printf_at_xy(board.col0 + j, board.row3, "-");
    }
}

void show_board(i8_t dimension, board_t board) {
    
    i8_t array_cols[] = {board.col0, board.col1, board.col2, board.col3};
    i8_t array_rows[] = {board.row0, board.row1, board.row2, board.row3};

    //printf_at_xy(board.col0, board.row0, "1");

    for (i8_t i = 0; i < dimension; ++i) {
        for (i8_t j = 0; j < dimension; ++j) {

            //show_contour(dimension, board, init_quadrant());

            if (board.matrix[i][j] == 'O') {

                printf_at_xy(array_cols[j] + 3, array_rows[i] + 1, "  ___  ");
                printf_at_xy(array_cols[j] + 3, array_rows[i] + 2, " / _ \\ ");
                printf_at_xy(array_cols[j] + 3, array_rows[i] + 3, "| | | |");
                printf_at_xy(array_cols[j] + 3, array_rows[i] + 4, "| |_| |");
                printf_at_xy(array_cols[j] + 3, array_rows[i] + 5, " \\___/ ");

            } else if (board.matrix[i][j] == 'X') {

                printf_at_xy(array_cols[j] + 3, array_rows[i] + 1, "__  __ ");
                printf_at_xy(array_cols[j] + 3, array_rows[i] + 2, "\\ \\/ / ");
                printf_at_xy(array_cols[j] + 3, array_rows[i] + 3, " \\  /  ");
                printf_at_xy(array_cols[j] + 3, array_rows[i] + 4, " /  \\  ");
                printf_at_xy(array_cols[j] + 3, array_rows[i] + 5, "/_/\\_\\ ");

            } else {

                printf_at_xy(array_cols[j] + 3, array_rows[i] + 1, "       ");
                printf_at_xy(array_cols[j] + 3, array_rows[i] + 2, "       ");
                printf_at_xy(array_cols[j] + 3, array_rows[i] + 3, "       ");
                printf_at_xy(array_cols[j] + 3, array_rows[i] + 4, "       ");
                printf_at_xy(array_cols[j] + 3, array_rows[i] + 5, "       ");
            
            }
        }
    }
}

void show_players(board_t board, char currentPlayer) {
    if(currentPlayer == 'O') {
        printf_at_xy((state.window.cols * 0.5) - 48, (state.window.rows * 0.5) - 20, "       ____  _                        __  __        __    ____  _                          ___  ");
        printf_at_xy((state.window.cols * 0.5) - 48, (state.window.rows * 0.5) - 19, "      |  _ \\| | __ _ _   _  ___ _ __  \\ \\/ /        \\ \\  |  _ \\| | __ _ _   _  ___ _ __   / _ \\ ");
        printf_at_xy((state.window.cols * 0.5) - 48, (state.window.rows * 0.5) - 18, "      | |_) | |/ _` | | | |/ _ \\ '__|  \\  /          \\ \\ | |_) | |/ _` | | | |/ _ \\ '__| | | | |");
        printf_at_xy((state.window.cols * 0.5) - 48, (state.window.rows * 0.5) - 17, "      |  __/| | (_| | |_| |  __/ |     /  \\          / / |  __/| | (_| | |_| |  __/ |    | |_| |");
        printf_at_xy((state.window.cols * 0.5) - 48, (state.window.rows * 0.5) - 16, "      |_|   |_|\\__,_|\\__, |\\___|_|    /_/\\_\\        /_/  |_|   |_|\\__,_|\\__, |\\___|_|     \\___/ ");
        printf_at_xy((state.window.cols * 0.5) - 48, (state.window.rows * 0.5) - 15, "                     |___/                                              |___/                   ");
    }
    else {
        printf_at_xy((state.window.cols * 0.5) - 48, (state.window.rows * 0.5) - 20, " __    ____  _                        __  __              ____  _                          ___  ");
        printf_at_xy((state.window.cols * 0.5) - 48, (state.window.rows * 0.5) - 19, " \\ \\  |  _ \\| | __ _ _   _  ___ _ __  \\ \\/ /             |  _ \\| | __ _ _   _  ___ _ __   / _ \\ ");
        printf_at_xy((state.window.cols * 0.5) - 48, (state.window.rows * 0.5) - 18, "  \\ \\ | |_) | |/ _` | | | |/ _ \\ '__|  \\  /              | |_) | |/ _` | | | |/ _ \\ '__| | | | |");
        printf_at_xy((state.window.cols * 0.5) - 48, (state.window.rows * 0.5) - 17, "  / / |  __/| | (_| | |_| |  __/ |     /  \\              |  __/| | (_| | |_| |  __/ |    | |_| |");
        printf_at_xy((state.window.cols * 0.5) - 48, (state.window.rows * 0.5) - 16, " /_/  |_|   |_|\\__,_|\\__, |\\___|_|    /_/\\_\\             |_|   |_|\\__,_|\\__, |\\___|_|     \\___/ ");
        printf_at_xy((state.window.cols * 0.5) - 48, (state.window.rows * 0.5) - 15, "                     |___/                                              |___/                   ");
    }
}

void out_of_board_error(board_t board) {
    printf_at_xy((state.window.cols * 0.5) - 22, (state.window.rows * 0.5) + 15, "<<Choose a position within the game board>>");
}

void invalid_posicion_error(board_t board) {
    printf_at_xy((state.window.cols * 0.5) - 15, (state.window.rows * 0.5) + 15, "<<Select an unoccupied spot>>");
}



