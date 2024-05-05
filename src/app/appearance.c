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
    board_t board;

    init_matrix(board, DIMENSION);

    return (board_t) {
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
            if (board.matrix[i][j] == '-') {

                printf_at_xy(array_cols[i] + 2, array_rows[j], "       ");
                printf_at_xy(array_cols[i] + 2, array_rows[j] + 1, "       ");
                printf_at_xy(array_cols[i] + 2, array_rows[j] + 2, "       ");
                printf_at_xy(array_cols[i] + 2, array_rows[j] + 3, "       ");
                printf_at_xy(array_cols[i] + 2, array_rows[j] + 4, "       ");

            } else if (board.matrix[i][j] == 'x') {
                printf_at_xy(array_cols[i] + 2, array_rows[j], "__  __ ");
                printf_at_xy(array_cols[i] + 2, array_rows[j] + 1, "\\ \\/ / ");
                printf_at_xy(array_cols[i] + 2, array_rows[j] + 2, " \\  /  ");
                printf_at_xy(array_cols[i] + 2, array_rows[j] + 3, " /  \\  ");
                printf_at_xy(array_cols[i] + 2, array_rows[j] + 4, "/_/\\_\\ ");
            } else {
                printf_at_xy(array_cols[i] + 2, array_rows[j], "  ___  ");
                printf_at_xy(array_cols[i] + 2, array_rows[j] + 1, " / _ \\ ");
                printf_at_xy(array_cols[i] + 2, array_rows[j] + 2, "| | | |");
                printf_at_xy(array_cols[i] + 2, array_rows[j] + 3, "| |_| |");
                printf_at_xy(array_cols[i] + 2, array_rows[j] + 4, " \\___/ ");
            }
        }
    }
}