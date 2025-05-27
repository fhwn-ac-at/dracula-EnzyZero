#include "commands.h"

namespace cmds {
namespace flow {



code 
h(GridBase& grid, [[maybe_unused]] Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{  
    grid.cursor.dir = Cursor::LEFT;
    return ok;
}


code 
j(GridBase& grid, [[maybe_unused]] Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{
    grid.cursor.dir = Cursor::DOWN;
    return ok;
}

code 
k(GridBase& grid, [[maybe_unused]] Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{
    grid.cursor.dir = Cursor::UP;
    return ok;
}


code 
l(GridBase& grid, [[maybe_unused]] Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{
    grid.cursor.dir = Cursor::RIGHT;
    return ok;
}

code 
H(GridBase& grid, [[maybe_unused]] Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
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
J(GridBase& grid, [[maybe_unused]] Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
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
K(GridBase& grid, [[maybe_unused]] Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
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
L(GridBase& grid, [[maybe_unused]] Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
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
x(GridBase& grid, [[maybe_unused]] Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
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
  
    // turn clockwise if top is positive
    if(s.peek() > 0)
        grid.cursor.dir = Cursor::cw( grid.cursor.dir );

    return ok;
} 

code 
X(GridBase& grid, [[maybe_unused]] Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
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
  
    // turn anticlockwise if top is negative
    if(s.peek() < 0)
        grid.cursor.dir = Cursor::ccw( grid.cursor.dir );

    return ok;
}

  

code 
e([[maybe_unused]] GridBase& grid, [[maybe_unused]] Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{
    return end;
}


} // flow namespace
} // cmds namespace