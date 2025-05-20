#ifndef window_h
#define window_h 

#include <string_view>
#include <array>
#include <ncurses.h>

#include "colors.h"

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
    void set_color(colors::color cl) noexcept;

    /**
     * @brief Remove a currently active color. Must match the previously set color.
     * 
     * Errors are not checked.
     * 
     * @param cl en enum value from the color enum
     */
    void rem_color(colors::color cl) noexcept;

    /**
     * @brief refresh and load any changes in memory
     */
    void refresh() { wrefresh(window_); }

    virtual ~window_base() = default; // leaving destruction to derivatives

    WINDOW* window_;
    int height_;
    int width_;
    int starty_;
    int startx_;
};

class subwindow : public window_base {
    
    subwindow(
        window win, 
        int height,
        int width,
        int starty,
        int startx
    )
    :   window_base( derwin(win.window_, height, width, starty, startx) )
    {}

    ~subwindow() override { delwin(window_); };
};

template <size_t S>
class window : public window_base { 

    window(
        int height,
        int width,
        int starty = 0,
        int startx = 0
    )
    :   window_base(height, width, starty, startx)
    {}

    /**
     * @brief Create a subwindow in the current window
     * 
     * All dimensions should fit into the main window.
     * 
     * @param height 
     * @param width 
     * @param starty 
     * @param startx 
     */
    create_subwindow(int height, int width, int starty, int startx); 

    /**
     * @brief Delete a subwindow from the array
     * 
     * @param pos 
     */
    delete_subwindow(int pos);

    window(window& other) = delete;
    window& operator=(window& other) = delete;

    // window owns its window and destroys it
    ~window() override { delwin(window_); }

    std::vector<subwindow> subwindows;
};



} // ui namespace

#endif