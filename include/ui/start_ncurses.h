#ifndef global_ncurses_h
#define global_ncurses_h

#include <ncurses.h>
#include "colors.h" 
#include "window_base.h" 

namespace ui {

/**
 * Ncurses setup in a constructor and teardown in deconstructor. 
 * Also has a window_base member with the stdscr.
 */
struct ncurses {

    ncurses() 
    :   mainwin(0, 0, 0, 0)
    { 

        initscr();
        curs_set(0); 
        refresh(); // for some reason, not refreshing at start breaks stuff later :(   
        cbreak();
        noecho();
        // keypad(stdscr, TRUE)
        
        colors::init_colors(); 

        mainwin = {stdscr};
    }
 
    ~ncurses() { endwin(); }  

    window_base mainwin;
};

} // ui namespace

#endif