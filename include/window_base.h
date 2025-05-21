#ifndef window_base_h
#define window_base_h 

#include <ncurses.h> 
#include <fmt/format.h>
#include "global_ncurses.h"
#include "colors.h"

// this is header only

namespace ui {

class window_base {
public:

    window_base(WINDOW* win)
    :   window_(win),
        height_( getmaxy(win) ),
        width_( getmaxy(win) ),
        starty_( getbegy(win) ),
        startx_( getbegx(win) )
    {}

    window_base(
        WINDOW* win,
        int height,
        int width,
        int starty,
        int startx
    )
    :   window_(win),
        height_(height),
        width_(width),
        starty_(starty),
        startx_(startx)
    {}
    
    window_base(
        int height,
        int width,
        int starty = 0,
        int startx = 0
    )
    :   window_( newwin(height, width, starty, startx) ),
        height_(height),
        width_(width),
        starty_(starty),
        startx_(startx)
    {}

    /**
     * @brief  print to the window 
     * 
     * @tparam Args 
     * @param format mft format like in fmt::print
     * @param args any args the format takes
     */
    template <typename... Args>
    void print(const std::string_view format, Args&&... args);

    /**
     * @brief print to a window without wrapping
     * 
     * The s stands for safe.
     * This printing function will print to the window and cut off strings that are longe than width_.
     * 
     * @tparam Args 
     * @param format fmt format like in fmt::print
     * @param args any args the format takes
     */
    template <typename... Args>
    void sprint(const std::string_view format, Args&&... args);

    /**
     * @brief get the position of the cursor in the terminal
     * 
     * @return std::pair<int, int> height, then width
     */
    auto get_cursor() const noexcept -> std::pair<int, int>; 

    /**
     * @brief set the position of the cursor in the window
     * 
     * @param y height
     * @param x width
     */
    void set_cursor(int y, int x) noexcept { wmove(window_, y, x); }

    /**
     * @brief Set a color pair for this window.
     * 
     * @param cl an enum value from the color enum
     */
    void set_textcolor(colors::color cl) noexcept { wattron(window_, COLOR_PAIR(cl)); }

    /**
     * @brief Remove a currently active color. Must match the previously set color.
     * 
     * Errors are not checked.
     * 
     * @param cl en enum value from the color enum
     */
    void rem_textcolor(colors::color cl) noexcept { wattroff(window_, COLOR_PAIR(cl)); }

    /**
     * @brief refresh and load any changes in memory
     */
    void refresh() { wrefresh(window_); }

    /**
     * @brief clear a window from all contents
     */
    void clear() { wclear(window_); }

    virtual ~window_base() = default; // leaving destruction to derivatives


    WINDOW* window_;
    int height_;
    int width_;
    int starty_;
    int startx_;
};

} // ui namespace 


auto ui::window_base::get_cursor() const noexcept -> std::pair<int, int> {
 
    std::pair<int, int> res; 
    getyx(window_, res.first, res.second); 
    return res;
}

template <typename... Args>
void ui::window_base::print(const std::string_view format, Args&&... args) {
        
    std::string msg = fmt::format(format, std::forward<Args>(args)... ); 
    waddstr(window_, msg.c_str());
}

template <typename... Args>
void ui::window_base::sprint(const std::string_view format, Args&&... args) {
        
    std::string msg = fmt::format(format, std::forward<Args>(args)... ); 
    waddnstr(window_, msg.c_str(), width_); // cut off long outputs
}

#endif