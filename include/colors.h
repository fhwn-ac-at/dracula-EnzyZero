#ifndef colors_h
#define colors_h

#include <ncurses.h>
#include <assert.h>

namespace ui {
namespace colors {

enum colors : int {

    CYAN_BLACK,
    MAGENTA_BLACK,
    GREEN_BLACK,
    YELLOW_BLACK,
    RED_BLACK,
    WHITE_RED,
    BLUE_BLACK,
    WHITE_BLACK,
    BLUE_WHITE
};

void init_colors() { 

    assert(!isendwin() && "ncurses must be initialised!");

    start_color();
    init_pair(CYAN_BLACK,    COLOR_CYAN, COLOR_BLACK);    // trace
    init_pair(MAGENTA_BLACK, COLOR_MAGENTA, COLOR_BLACK); // debug
    init_pair(GREEN_BLACK,   COLOR_GREEN, COLOR_BLACK);   // info
    init_pair(YELLOW_BLACK,  COLOR_YELLOW, COLOR_BLACK);  // warn
    init_pair(RED_BLACK,     COLOR_RED, COLOR_BLACK);     // error
    init_pair(WHITE_RED,     COLOR_WHITE, COLOR_RED);     // critical
    init_pair(BLUE_BLACK,    COLOR_BLUE, COLOR_BLACK);    // off
    init_pair(WHITE_BLACK,   COLOR_WHITE, COLOR_BLACK);   // n_levels (idk)
    init_pair(BLUE_WHITE,    COLOR_BLUE, COLOR_WHITE);   // for hightlighting the cursor
}

}
}

#endif