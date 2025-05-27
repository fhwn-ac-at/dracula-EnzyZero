#include "commands.h" 

namespace cmds {
namespace io {

code 
o(GridBase& grid, [[maybe_unused]] Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{
    if(!below_avail(grid))
    {
        log->error("BAD::CELL::ACCESS cannot send value below"); 
        return err;
    }

    os << grid.catpos( grid.cursor.y+1, grid.cursor.x ) << std::flush; // flush calls wrefresh for ncurses
    return ok;
} 

code 
O(GridBase& grid, [[maybe_unused]] Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{
    if(!above_avail(grid))
    {
        log->error("BAD::CELL::ACCESS cannot send value above"); 
        return err;
    }

    os << grid.catpos( grid.cursor.y-1, grid.cursor.x ) << std::flush; // flush calls wrefresh for ncurses
    return ok;
} 

code 
i(GridBase& grid, [[maybe_unused]] Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{
    if(!below_avail(grid))
    {
        log->error("BAD::CELL::ACCESS no cell below to store to"); 
        return err;
    }
 
    // get input
    log->info("Need input...");  
    char c;
    is >> c;
 
    log->info("Got input (hex): 0x{:02X}", c); 
    grid.catpos( grid.cursor.y+1, grid.cursor.x ) = c;   

    return ok;
} 

code 
I(GridBase& grid, [[maybe_unused]] Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{
    if(!above_avail(grid))
    {
        log->error("BAD::CELL::ACCESS no cell above to store to"); 
        return err;
    }
 
    // get input
    log->info("Need input...");  
    char c;
    is >> c;
 
    log->info("Got input (hex): 0x{:02X}", c); 
    grid.catpos( grid.cursor.y-1, grid.cursor.x ) = c;   

    return ok;
}

} // io namespace
} // cmds namespace