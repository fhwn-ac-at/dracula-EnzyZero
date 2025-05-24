#ifndef window_base_h
#define window_base_h 

#include <ncurses.h> 
#include <format>
#include "colors.h"

// this is header only

namespace ui {

class window_base {
public:

    window_base(WINDOW* win);

    window_base(
        WINDOW* win,
        int height,
        int width,
        int starty,
        int startx
    );
   
    window_base(
        int height,
        int width,
        int starty = 0,
        int startx = 0
    );

    using Char = chtype;

    template <typename... Args>
    void print(const std::string_view format, Args&&... args);

    template <typename... Args>
    void sprint(const std::string_view format, Args&&... args);

    void putc(const Char c) { ::waddch(window_, c); }

    int getc() { return ::wgetch(window_); }

    auto get_cursor() const noexcept -> std::pair<int, int>; 

    void set_cursor(int y, int x) noexcept { wmove(window_, y, x); }
    
    void set_textcolor(colors::color cl) noexcept { wattron(window_, COLOR_PAIR(cl)); }

    void rem_textcolor(colors::color cl) noexcept { wattroff(window_, COLOR_PAIR(cl)); } 

    void box(Char vertical = 0, Char horizontal = 0) noexcept { ::box(window_, vertical, horizontal); }

    void set_scrollok(bool b) noexcept { scrollok(window_, b); }

    void set_nodelay(bool b) noexcept { ::nodelay(window_, b); }

    void refresh() { wrefresh(window_); }

    void clear() { wclear(window_); } 

    virtual ~window_base() = default; // leaving destruction to derivatives

    WINDOW* window_;
    int height;
    int width;
    int starty;
    int startx;
};

} // ui namespace 


template <typename... Args>
void ui::window_base::print(const std::string_view format, Args&&... args) {
        
    std::string msg = std::vformat(format, std::make_format_args(args...) ); 
    waddstr(window_, msg.c_str());
}

template <typename... Args>
void ui::window_base::sprint(const std::string_view format, Args&&... args) {
        
    std::string msg = std::vformat(format, std::make_format_args(args...) ); 
    waddnstr(window_, msg.c_str(), width); // cut off long outputs
}

#endif