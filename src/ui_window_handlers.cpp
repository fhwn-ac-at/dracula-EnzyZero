#include <cctype> 
#include <string>
#include <memory>

#include <spdlog/logger.h>

#include "ui_window_handlers.h"

namespace ui {


grid_window_handler::grid_window_handler(
    WINDOW* win, 
    std::shared_ptr<spdlog::logger> logger,
    const grid& grid 
)
:   ui::window_handler_base(win),
    grid_(grid),
    logger_( std::move(logger) )
{}

void grid_window_handler::update() {

    for (const auto& line : grid_.grid_) 
    {
        std::string row; 

        // add fields in the grid, check if they are printable
        for (const auto& field : line) 
            row += std::isprint(static_cast<unsigned char>(field)) 
                ?  field
                : '#';

        sprint(row); 
        print("\n");
    } 
         
    // check if cursor can be displayed
    if (grid_.cursor.y >= height_ || grid_.cursor.x > width_)
    {
        logger_->warn("WINDOW::SIZE::WARNING: window too small to display cursor");
        refresh();
        return;
    }

    // set terminal cursor to grids cursor
    auto [save_y, save_x] = get_cursor(); 
    set_cursor(grid_.cursor.y, grid_.cursor.x);
        
    // highlight
    wattron(window_, COLOR_PAIR( cursor_color_pair_num_ ));
    print("{}", grid_.grid_.at(grid_.cursor.y).at(grid_.cursor.x)); 
    wattroff(window_, COLOR_PAIR( cursor_color_pair_num_ )); 

    // reset cursor and display changes
    set_cursor(save_y, save_x);
    refresh();
}
    

} // ui namespace