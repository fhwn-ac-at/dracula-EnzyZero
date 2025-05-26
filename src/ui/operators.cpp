#include <string>  
#include "stack.h"
#include "interpreter.h"
#include "operators.h"

namespace ui {

void GridOperator::render(Interpreter& interpreter) {

    GridBase& grid = interpreter.grid(); 
    window_.set_cursor(0, 0);

    for (const auto& line : grid.matrix()) 
    {
        std::string row; 

        // add fields in the grid, check if they are printable
        for (const auto& field : line) 
        { 
            row += std::isprint(static_cast<unsigned char>(field)) 
                ?  field            // field is printable
                :  field == 0       // field is empty
                ?  ' '              // then print whitespace
                :  '#';             // else, print a hash
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
    window_.print("{}", grid.matrix().at(grid.cursor.y).at(grid.cursor.x));  
    window_.rem_textcolor(colors::BLUE_WHITE);

    // reset cursor and display changes
    window_.set_cursor(save_y, save_x);
    window_.refresh();
}

void StackOperator::render(Interpreter& interpreter) { 

    window_.set_cursor(0, 0);
    
    auto it = interpreter.stack().begin();   
    auto end = interpreter.stack().end(); 

    for (int i = 0; i < window_.height && it != end; i++) 
    {  
        // convert stack value to string, fit to window width
        std::string value = std::format("{}{}", i, *it++); 
        if (value.length() > window_.width)
            value.resize(window_.width); 
         
        window_.print(value);
    } 

    window_.refresh();
} 

void CursorOperator::render(Interpreter& interpreter) {
 
    
    

}


} // ui namespace   

