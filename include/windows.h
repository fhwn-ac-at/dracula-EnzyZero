#ifndef window_h
#define window_h 

#include <string_view>  
#include <vector>
#include <memory>
#include <ncurses.h>
#include <utility>

#include "global_ncurses.h"
#include "window_base.h"
#include "colors.h"

namespace ui {

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

    subwindow(window_base& win)
    :   window_base( derwin(win.window_, win.height-2, win.width-2, win.starty+1, win.startx+1) )
    {}

    ~subwindow() override { delwin(window_); }; 

private:
    using window_base::window_;
};

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
     * @brief Create a subwindow in the current window
     * 
     * All dimensions should fit into the main window.
     * 
     * @param height 
     * @param width 
     * @param starty 
     * @param startx 
     * 
     * @return int returns the index of where the subwindow is located in the vector
     */
    int create_subwindow(int height, int width, int starty, int startx) {
        subwindows_.emplace_back(std::make_unique<subwindow>(*this, height, width, starty, startx)); 
        return subwindows_.size() - 1;
    }

    /**
     * @brief Create a subwindow 
     * 
     * Subwindow will fit into the borders of the window. 
     * 
     * @return int returns the index of where the subwindow is located in the vector
     */
    int create_subwindow() {
        subwindows_.emplace_back(std::make_unique<subwindow>(*this)); 
        return subwindows_.size() - 1;
    } 

    /**
     * @brief Get a subwindow from the vector
     * 
     * @param pos 
     * @return subwindow& reference to the saved subwindow
     */
    subwindow& get_subwindow(int pos) { return *(subwindows_.at(pos)); }

    /**
     * @brief Delete a subwindow from the vector
     * 
     * @param pos 
     */
    void delete_subwindow(int pos) { subwindows_.erase( subwindows_.begin() + pos); }

    // window owns its window and destroys it
    ~window() override { if (window_) delwin(window_); }

private:
    window(window& other) = delete;
    window& operator=(window& other) = delete; 

    std::vector<std::unique_ptr<subwindow>> subwindows_;

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