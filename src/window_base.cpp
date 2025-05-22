#include "window_base.h"

namespace ui {

window_base::window_base(WINDOW* win)
:   window_(win),
    height( getmaxy(win) ),
    width( getmaxx(win) ),
    starty( getbegy(win) ),
    startx( getbegx(win) )
{}

window_base::window_base(
    WINDOW* win,
    int height,
    int width,
    int starty,
    int startx
)
:   window_(win),
    height(height),
    width(width),
    starty(starty),
    startx(startx)
{}
    
window_base::window_base(
    int height,
    int width,
    int starty,
    int startx
)
:   window_( newwin(height, width, starty, startx) ),
    height(height),
    width(width),
    starty(starty),
    startx(startx)
{}

auto ui::window_base::get_cursor() const noexcept -> std::pair<int, int> {
 
    std::pair<int, int> res; 
    getyx(window_, res.first, res.second); 
    return res;
}

void ui::window_base::make_classic_border() noexcept {

    wborder(window_, 
        ACS_VLINE, ACS_VLINE,     // Left, Right: vertical bars
        ACS_HLINE, ACS_HLINE,     // Top, Bottom: horizontal bars
        ACS_ULCORNER, ACS_URCORNER, // Top-left, Top-right
        ACS_LLCORNER, ACS_LRCORNER  // Bottom-left, Bottom-right
    );
}


} // ui namespace