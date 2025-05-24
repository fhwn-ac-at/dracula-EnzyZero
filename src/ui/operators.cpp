#include <string> 
#include "interpreter.h"
#include "operators.h"

namespace ui {

void grid_operator::render(Interpreter& interpreter) {

    grid_base& grid = interpreter.grid_;

    for (const auto& line : grid.grid_) 
    {
        std::string row; 

        // add fields in the grid, check if they are printable
        for (const auto& field : line) 
        {
            row += std::isprint(static_cast<unsigned char>(field)) 
                ?  field            // field is printable
                :  field == ' '     // field is non-printable but is it a whitespace?
                ? ' '               // then print a whitespace
                : '#';              // else, print a hash
        }

        // truncate if too long to be displayed
        if (row.length() > window_.width)
            row.resize(window_.width); 

        window_.print(row);
    } 
         
    // check if cursor can be displayed
    if (grid.cursor.y >= window_.height || grid.cursor.x > window_.width)
    {
        window_.refresh();
        return;
    }

    // set terminal cursor to grids cursor
    auto [save_y, save_x] = window_.get_cursor(); 
    window_.set_cursor(grid.cursor.y, grid.cursor.x);
        
    // highlight
    window_.set_textcolor(colors::BLUE_WHITE);
    window_.print("{}", grid.grid_.at(grid.cursor.y).at(grid.cursor.x));  
    window_.rem_textcolor(colors::BLUE_WHITE);

    // reset cursor and display changes
    window_.set_cursor(save_y, save_x);
    window_.refresh();
}

} // ui namespace