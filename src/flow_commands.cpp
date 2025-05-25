#include "commands.h"

namespace cmds {
namespace flow {

bool at_left(grid_base& grid)   { return grid.cursor.x <= 0; }
bool at_right(grid_base& grid)  { return grid.cursor.x >= grid.grid_.at(grid.cursor.x).size() -1; } 
bool at_top(grid_base& grid)    { return grid.cursor.y <= 0; }
bool at_bot(grid_base& grid)    { return grid.cursor.y >= grid.grid_.at(grid.cursor.y).size() -1; } 
 
code 
h(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log)
{  
    if (at_left(grid))
    {
        log->error("BAD::MOVE::ERROR cannot move left");
        return err;
    }

    grid.cursor.dir = grid_base::Cursor::LEFT;
    return ok;
}


code 
j(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    if (at_bot(grid))
    {
        log->error("BAD::MOVE::ERROR cannot move down");
        return err;
    }
    
    grid.cursor.dir = grid_base::Cursor::DOWN;
    return ok;
}

code 
k(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    if (at_top(grid))
    {
        log->error("BAD::MOVE::ERROR cannot move up");
        return err;
    }

    grid.cursor.dir = grid_base::Cursor::UP;
    return ok;
}


code 
l(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    if (at_right(grid))
    {
        log->error("BAD::MOVE::ERROR cannot move right");
        return err;
    }

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
    else if (at_left(grid))
    {
        log->error("BAD::MOVE::ERROR cannot move left");
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
    else if (at_bot(grid))
    {
        log->error("BAD::MOVE::ERROR cannot move down");
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
    else if (at_top(grid))
    {
        log->error("BAD::MOVE::ERROR cannot move up");
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
L(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{
    if (s.empty()) 
    {
        log->error("STACK::IS::EMPTY no values in the stack");
        return err;
    } 
    else if (at_right(grid))
    {
        log->error("BAD::MOVE::ERROR cannot move right");
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