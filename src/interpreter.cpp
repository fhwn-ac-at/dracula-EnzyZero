#include <expected>
#include "interpreter.h" 

Coroutine Interpreter::interpret() 
{ 
    using Cmd  = std::function<cmds::signature>;  
    using miss = perf_hashtable<Cmd>::table_miss;   
 
    while(true)
    {
        // get the cmd with the key of the current cursors position in the grid 
        char c = grid_.catcur();
        std::expected<Cmd, miss> exp = hasht_.at( c );
  
        if (!exp)
        {
            logger_->error("HASH::TABLE::MISS encountered character (hex): 0x{:02X}", c); 
            co_return;
        }  

        Cmd cmd = *exp; 

        // call command here, check return code
        if (cmds::code res = cmd(grid_, stack_, istream_, ostream_, logger_); res != cmds::ok)  
            co_return;

        // step to direction (cmds check if step is possible) 
        using enum grid_base::Cursor::direction;
        switch (grid_.cursor.dir)
        {
            case NONE: 
                logger_->error("NO::DIRECTION::ERROR no direction to step to next.");
                co_return; 

            case UP:    grid_.cursor.y--; break;
            case DOWN:  grid_.cursor.y++; break; 
            case LEFT:  grid_.cursor.x--; break;
            case RIGHT: grid_.cursor.x++; break;

            default: std::unreachable();
        } 
  
        // suspend here
        co_await std::suspend_always{}; 
    } 

    std::unreachable();
}