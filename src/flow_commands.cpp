#include "commands.h"

namespace cmds {
namespace flow {



code 
h(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log)
{  
    grid.cursor.dir = grid_base::Cursor::LEFT;
    return ok;
}


code 
j(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    grid.cursor.dir = grid_base::Cursor::DOWN;
    return ok;
}

code 
k(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    grid.cursor.dir = grid_base::Cursor::UP;
    return ok;
}


code 
l(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    grid.cursor.dir = grid_base::Cursor::RIGHT;
    return ok;
}

code 
H(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    if (s.empty()) 
    {
        log->error("STACK::IS::EMPTY no values in the stack");
        return err;
    } 

    grid.cursor.dir = grid_base::Cursor::LEFT; 
    const auto stackval = s.peek();

    do {
        grid.cursor.x--; 
        
    } while (grid.catcur() != stackval && !at_left(grid));

    if (grid.catcur() != stackval)
    {
        log->error("NOT::FOUND::ERROR no field was eq to {}", stackval);
        return err;
    } 

    return ok;
}

code 
J(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    if (s.empty()) 
    {
        log->error("STACK::IS::EMPTY no values in the stack");
        return err;
    } 

    grid.cursor.dir = grid_base::Cursor::DOWN; 
    const auto stackval = s.peek();

    do {
        grid.cursor.y++; 
        
    } while (grid.catcur() != stackval && !at_bot(grid));

    if (grid.catcur() != stackval)
    {
        log->error("NOT::FOUND::ERROR no field was eq to {}", stackval);
        return err;
    } 

    return ok;
} 

code 
K(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    if (s.empty()) 
    {
        log->error("STACK::IS::EMPTY no values in the stack");
        return err;
    } 

    grid.cursor.dir = grid_base::Cursor::UP; 
    const auto stackval = s.peek();

    do {
        grid.cursor.y--; 
        
    } while (grid.catcur() != stackval && !at_top(grid));

    if (grid.catcur() != stackval)
    {
        log->error("NOT::FOUND::ERROR no field was eq to {}", stackval);
        return err;
    } 

    return ok;
} 

code 
x(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    if (s.empty())
    {
        log->error("STACK::IS::EMPTY no values in stack"); 
        return err;
    } 
    else if (grid.cursor.dir == grid_base::Cursor::NONE) 
    {
        log->error("NO::DIRECTION::ERROR cannot turn without an initial direction"); 
        return err;
    } 
  
    // turn clockwise if top is positive
    if(s.peek() > 0)
        grid.cursor.dir = grid_base::Cursor::cw( grid.cursor.dir );

    return ok;
} 

code 
X(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    if (s.empty())
    {
        log->error("STACK::IS::EMPTY no values in stack"); 
        return err;
    } 
    else if (grid.cursor.dir == grid_base::Cursor::NONE) 
    {
        log->error("NO::DIRECTION::ERROR cannot turn without an initial direction"); 
        return err;
    } 
  
    // turn anticlockwise if top is negative
    if(s.peek() < 0)
        grid.cursor.dir = grid_base::Cursor::ccw( grid.cursor.dir );

    return ok;
}

code 
L(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    if (s.empty()) 
    {
        log->error("STACK::IS::EMPTY no values in the stack");
        return err;
    } 

    grid.cursor.dir = grid_base::Cursor::RIGHT; 
    const auto stackval = s.peek();

    do {
        grid.cursor.x++; 
        
    } while (grid.catcur() != stackval && !at_right(grid));

    if (grid.catcur() != stackval)
    {
        log->error("NOT::FOUND::ERROR no field was eq to {}", stackval);
        return err;
    } 

    return ok;
}  

code 
e(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    return end;
}


} // flow namespace
} // cmds namespace