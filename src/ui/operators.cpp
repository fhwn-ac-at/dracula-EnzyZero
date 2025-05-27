#include <string>  
#include "stack.h"
#include "interpreter.h"
#include "operators.h"

namespace ui {

void GridOperator::render(Interpreter& interpreter) {

    GridBase& grid = interpreter.grid(); 
    window_.set_cursor(0, 0); 

    { 
        // reserve string storage
        std::string row;  
        row.reserve(window_.width);

        for (const auto& line : grid.matrix()) 
        {

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
            if (row.length() > window_.width - 1)
                row.resize(window_.width - 1);  

            row += '\n'; // add a newline

            window_.print(row); 
            row.clear(); // capacity not freed here
        }  
    }

    // check if cursor can be displayed
    if (grid.cursor.y > window_.height - 1 || grid.cursor.x > window_.width - 1)
    {
        window_.refresh();
        return;
    }

    // set terminal cursor to grids cursor
    window_.set_cursor(grid.cursor.y, grid.cursor.x); 

    // highlight
    window_.set_textcolor(colors::BLUE_WHITE);
    window_.print("{}", static_cast<char>( (grid.matrix().at(grid.cursor.y).at(grid.cursor.x)) ));  
    window_.rem_textcolor(colors::BLUE_WHITE);

    // display changes
    window_.refresh();
}

void StackOperator::render(Interpreter& interpreter) {   

    auto& stack = interpreter.stack();
    if (stack.empty()) 
        return;
 
    window_.set_cursor(0, 0); // reset cur
    
    auto it = stack.begin();   
    auto end = stack.end(); 

    for (int i = 0; i < window_.height && it != end; i++, it++) 
    {
        // convert stack value to string, fit to window width
        std::string value = std::format("{:>2}.: {}\n", i, static_cast<int>(*it)); 
        if (value.length() > window_.width)
        {
            value.resize(window_.width - 1);   
            value += '\n';
        }
         
        window_.print(value);
    } 

    window_.refresh();
} 

void CursorOperator::render(Interpreter& interpreter) {
  
    auto& cursor = interpreter.grid().cursor; 
 
    // note that std::formatter was specialised to work with Cursor
    std::string msg = std::format("{}\n", cursor);
     
    if (msg.length() > window_.width) // trunc to window width 
    {
        msg.resize(window_.width - 1);  
        msg += '\n';
    }

    window_.print(msg);
    window_.refresh();
}


} // ui namespace   

