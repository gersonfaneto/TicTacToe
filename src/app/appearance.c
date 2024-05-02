#include "appearance.h"

#include "state.h"

quadrant init_quadrant() {

    return (quadrant) {
        .width = PLAYER_COMPONENT_WIDTH + SPACE_WIDTH_BORDER,
        .height = PLAYER_COMPONENT_HEIGHT + SPACE_HEIGHT_BORDER,
    };
}

board init_board() {

    quadrant quadrant = init_quadrant();

    return (board) {
        .middle_x = state.window.rows * 0.5,
        .middle_y = state.window.cols * 0.5,
        .width = quadrant.width * 3,
        .height = quadrant.height * 3,
    };
}