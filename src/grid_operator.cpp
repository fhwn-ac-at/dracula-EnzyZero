#include <string>
#include "grid_base.h"

namespace ui {

void grid_operator::setup(window& win) { 
 
    // warn if the grid is not fully visible
    if (grid_.cursor.y >= win.height || grid_.cursor.x > win.width)
        logger_->warn("WINDOW::SIZE::WARNING: window too small to display cursor");

    win.create_subwindow(); 
}


void grid_operator::render(window& win) {

    for (const auto& line : grid_.grid_) 
    {
        std::string row; 

        // add fields in the grid, check if they are printable
        for (const auto& field : line) 
            row += std::isprint(static_cast<unsigned char>(field)) 
                ?  field
                : '#';

        win.sprint(row); 
        win.print("\n");
    } 
         
    // check if cursor can be displayed
    if (grid_.cursor.y >= win.height || grid_.cursor.x > win.width)
    {
        win.refresh();
        return;
    }

    // set terminal cursor to grids cursor
    auto [save_y, save_x] = win.get_cursor(); 
    win.set_cursor(grid_.cursor.y, grid_.cursor.x);
        
    // highlight
    win.set_textcolor(colors::BLUE_WHITE);
    win.print("{}", grid_.grid_.at(grid_.cursor.y).at(grid_.cursor.x));  
    win.rem_textcolor(colors::BLUE_WHITE);

    // reset cursor and display changes
    win.set_cursor(save_y, save_x);
    win.refresh();
}

} // ui namespace