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

void show_board(i8_t dimension, board_t board) {
    
    i8_t array_cols[] = {board.col0, board.col1, board.col2, board.col3};
    i8_t array_rows[] = {board.row0, board.row1, board.row2, board.row3};

    for (i8_t i = 0; i < dimension; ++i) {
        for (i8_t j = 0; j < dimension; ++j) {


            if (board.matrix[i][j] == 'O') {

                printf_at_xy(array_cols[j] + 2, array_rows[i], "  ___  ");
                printf_at_xy(array_cols[j] + 2, array_rows[i] + 1, " / _ \\ ");
                printf_at_xy(array_cols[j] + 2, array_rows[i] + 2, "| | | |");
                printf_at_xy(array_cols[j] + 2, array_rows[i] + 3, "| |_| |");
                printf_at_xy(array_cols[j] + 2, array_rows[i] + 4, " \\___/ ");

            } else if (board.matrix[i][j] == 'X') {

                printf_at_xy(array_cols[j] + 2, array_rows[i], "__  __ ");
                printf_at_xy(array_cols[j] + 2, array_rows[i] + 1, "\\ \\/ / ");
                printf_at_xy(array_cols[j] + 2, array_rows[i] + 2, " \\  /  ");
                printf_at_xy(array_cols[j] + 2, array_rows[i] + 3, " /  \\  ");
                printf_at_xy(array_cols[j] + 2, array_rows[i] + 4, "/_/\\_\\ ");

            } else {

                printf_at_xy(array_cols[j] + 2, array_rows[i], "       ");
                printf_at_xy(array_cols[j] + 2, array_rows[i] + 1, "       ");
                printf_at_xy(array_cols[j] + 2, array_rows[i] + 2, "       ");
                printf_at_xy(array_cols[j] + 2, array_rows[i] + 3, "       ");
                printf_at_xy(array_cols[j] + 2, array_rows[i] + 4, "       ");

            }
        }
    }
}

