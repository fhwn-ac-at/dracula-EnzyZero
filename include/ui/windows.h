#ifndef window_h
#define window_h 

#include <string_view>  
#include <vector>
#include <ncurses.h>
#include <utility>

#include "window_base.h"
#include "colors.h"

namespace ui {

/**
 * @brief A subwindow is a derived ncurses window. 
 *
 * Essentially, It operates on some memory of the actual window. 
 * It is an 'inner' window.
 */
class subwindow : public window_base { 
public:
    
    subwindow(
        window_base& win, 
        int height,
        int width,
        int starty,
        int startx
    )
    :   window_base( derwin(win.window_, height, width, starty, startx) )
    {}
 
    // this indents the subwidnow into the window one tile after the borders
    subwindow(window_base& win)
    :   window_base( derwin(win.window_, win.height-2, win.width-2, 1, 1) )
    {}

    ~subwindow() override { delwin(window_); }; 

private:
    using window_base::window_;
};

/**
 * @brief A window that owns its WINDOW* handle and may also have subwindows. 
 */
class window : public window_base { 
public:

    window(
        int height,
        int width,
        int starty = 0,
        int startx = 0
    )
    :   window_base(height, width, starty, startx)
    {}

    window(window&& other) noexcept
    :   window_base( std::exchange(other.window_, nullptr), other.height, other.width, other.starty, other.startx)
    {} 

    window& operator=(window&& other) noexcept;

    /**
     * @brief Create a subwindow with specific dimensions
     * 
     * @param height 
     * @param width 
     * @param starty 
     * @param startx 
     */
    void create_subwindow(int height, int width, int starty, int startx) {
        subwindows_.emplace_back(*this, height, width, starty, startx); 
    }
 
    /**
     * @brief Create an indented subwindow  
     * 
     * Useful for when you do not want to touch the borders and dont want
     * to bother with setting the cursor correctly.
     */
    void create_subwindow() {
        subwindows_.emplace_back(*this); 
    } 

    auto subwindows() -> std::vector<subwindow>& { return subwindows_; }

    
    // window owns its window and destroys it
    ~window() override { if (window_) delwin(window_); }

private:
    window(window& other) = delete;
    window& operator=(window& other) = delete; 

    std::vector<subwindow> subwindows_;

    using window_base::window_;
};

} // ui namespace 


inline ui::window& ui::window::operator=(window&& other) noexcept {
        
    if (window_)
        delwin(window_);

    window_ = std::exchange(other.window_, nullptr);
    height = other.height;
    width = other.width;
    starty = other.starty;
    startx = other.startx;

    return *this;
}

#endif