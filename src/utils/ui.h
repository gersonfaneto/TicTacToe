#ifndef UI_H_
#define UI_H_

#define UPPER_RIGHT_CORNER "┐"
#define UPPER_LEFT_CORNER "┌"
#define UPPER_SEGMENT "─"

#define LOWER_RIGHT_CORNER "┘"
#define LOWER_LEFT_CORNER "└"
#define LOWER_SEGMENT "─"

#define SIDE_SEGMENT "│"

#define PLAYER_X 0
#define PLAYER_Y 1

#define PLAYER_COMPONET_WIDTH 7
#define PLAYER_COMPONET_HEIGHT 5

const char* players[][PLAYER_COMPONET_HEIGHT] = {
    {
        "  ___  ",
        " / _ \\ ",
        "| | | |",
        "| |_| |",
        " \\___/ ",
    },
    {
        "__  __ ",
        "\\ \\/ / ",
        " \\  /  ",
        " /  \\  ",
        "/_/\\_\\ ",
    },
};

#endif  // !UI_H_
