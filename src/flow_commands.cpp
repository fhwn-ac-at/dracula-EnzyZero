#include "commands.h"

namespace cmds {
namespace flow {



code 
h(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log)
{  
    grid.cursor.dir = Cursor::LEFT;
    return ok;
}


code 
j(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    grid.cursor.dir = Cursor::DOWN;
    return ok;
}

code 
k(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    grid.cursor.dir = Cursor::UP;
    return ok;
}


code 
l(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    grid.cursor.dir = Cursor::RIGHT;
    return ok;
}

code 
H(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    if (s.empty()) 
    {
        log->error("STACK::IS::EMPTY no values in the stack");
        return err;
    } 

    grid.cursor.dir = Cursor::LEFT; 
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
J(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    if (s.empty()) 
    {
        log->error("STACK::IS::EMPTY no values in the stack");
        return err;
    } 

    grid.cursor.dir = Cursor::DOWN; 
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
K(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    if (s.empty()) 
    {
        log->error("STACK::IS::EMPTY no values in the stack");
        return err;
    } 

    grid.cursor.dir = Cursor::UP; 
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
x(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    if (s.empty())
    {
        log->error("STACK::IS::EMPTY no values in stack"); 
        return err;
    } 
    else if (grid.cursor.dir == Cursor::NONE) 
    {
        log->error("NO::DIRECTION::ERROR cannot turn without an initial direction"); 
        return err;
    } 
    else if (s.peek() == 0) 
        log->warn("ZERO::WARN top val of stack is 0");
  
    // turn clockwise if top is positive
    if(s.peek() > 0)
        grid.cursor.dir = Cursor::cw( grid.cursor.dir );

    return ok;
} 

code 
X(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    if (s.empty())
    {
        log->error("STACK::IS::EMPTY no values in stack"); 
        return err;
    } 
    else if (grid.cursor.dir == Cursor::NONE) 
    {
        log->error("NO::DIRECTION::ERROR cannot turn without an initial direction"); 
        return err; 
    }   
    else if (s.peek() == 0) 
        log->warn("ZERO::WARN top val of stack is 0");

  
    // turn anticlockwise if top is negative
    if(s.peek() < 0)
        grid.cursor.dir = Cursor::ccw( grid.cursor.dir );

    return ok;
}

code 
L(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    if (s.empty()) 
    {
        log->error("STACK::IS::EMPTY no values in the stack");
        return err;
    } 

    grid.cursor.dir = Cursor::RIGHT; 
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
e(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    return end;
}


} // flow namespace
} // cmds namespace