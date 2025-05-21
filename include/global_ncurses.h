#ifndef global_ncurses_h
#define global_ncurses_h

#include <ncurses.h>
#include "colors.h"

namespace ui {

inline struct GlobalNcurses {

    explicit GlobalNcurses() {
        initscr();
        curs_set(0); 
        refresh(); // for some reason, not refreshing at start breaks stuff later :(
        // cbreak();
        // noecho()
        // keypad(stdscr, TRUE)
        
        colors::init_colors();
    }
 
    ~GlobalNcurses() { endwin(); }

} global_ncurses;

} // ui namespace

#endif