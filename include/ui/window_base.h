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
 
    /**
     * @brief print a formatted msg to a window
     * 
     * @param format format-string (or string without formats) like in std::format
     * @param args arguments for the format-string if any.
     */
    template <typename... Args>
    void print(const std::string_view format, Args&&... args);
 
    /**
     * @brief Put a single character to the screen.
     * 
     * @param c 
     */
    void putc(const Char c) { ::waddch(window_, c); }
 
    /**
     * @brief Get a single character of the screen
     * 
     * @return int ERR enum on EOF or timeout.
     */
    int getc() { return ::wgetch(window_); }
 
    /**
     * @brief Get Y and X of the cursor.
     * 
     * @return std::pair<int, int> Y then X
     */
    auto get_cursor() const noexcept -> std::pair<int, int>; 
 
    /**
     * @brief Set cursor position
     * 
     * @param y height
     * @param x width
     */
    void set_cursor(int y, int x) noexcept { wmove(window_, y, x); }
     
    /**
     * @brief Set a color pair
     * 
     * @param cl enum from colors.h
     */
    void set_textcolor(colors::color cl) noexcept { wattron(window_, COLOR_PAIR(cl)); }
 
    /**
     * @brief Remove a previously applied color pair
     * 
     * @param cl enum from colors.h
     */
    void rem_textcolor(colors::color cl) noexcept { wattroff(window_, COLOR_PAIR(cl)); } 
 
    /**
     * @brief Make a box around the windows
     * 
     * @param vertical character char to use, 0 makes lines
     * @param horizontal character char to use, 0 makes lines 
     */
    void box(Char vertical = 0, Char horizontal = 0) noexcept { ::box(window_, vertical, horizontal); }
 
    /**
     * @brief Set whether the window is scrollable.
     * 
     * On full windows, this will result in scrolling the contents up.
     * 
     * @param b 
     */
    void set_scrollok(bool b) noexcept { scrollok(window_, b); }
 
    /**
     * @brief true sets io routines to not block for io, false (default) blocks.
     * 
     * @param b 
     */
    void set_nodelay(bool b) noexcept { ::nodelay(window_, b); }
 
    /**
     * @brief refreshes the window and draws memory to screen
     * 
     */
    void refresh() { wrefresh(window_); }
 
    /**
     * @brief removes contents and refreshes window. 
     */
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

#endif