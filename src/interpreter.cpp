#include <expected> 

#include "interpreter.h" 

Coroutine Interpreter::interpret() 
{ 
    using Cmd  = std::function<cmds::signature>;  
    using miss = PerfHashtable<Cmd>::table_miss;   
 
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

        std::function<cmds::signature>& cmd = *exp; 

        // call command here, check return code
        if (cmds::code res = cmd(grid_, stack_, istream_, ostream_, logger_); res != cmds::ok)  
            co_return;

        // step to direction and check if possible
        using enum Cursor::Direction;
        switch (grid_.cursor.dir)
        {
            case NONE: 
                logger_->error("NO::DIRECTION::ERROR no direction to step to next.");
                co_return; 

            case UP:     
                if (cmds::at_top(grid_))  
                {
                    logger_->error("BAD::MOVE::ERROR cannot move up");
                    co_return;
                }
                grid_.cursor.y--; 
                break; 

            case DOWN:   
                if (cmds::at_bot(grid_))  
                {
                    logger_->error("BAD::MOVE::ERROR cannot move down");
                    co_return;
                }
                grid_.cursor.y++; 
                break;  

            case LEFT:     
                if (cmds::at_left(grid_))  
                {
                    logger_->error("BAD::MOVE::ERROR cannot move left");
                    co_return;
                }
                grid_.cursor.x--; 
                break; 

            case RIGHT:   
                if (cmds::at_right(grid_))  
                {
                    logger_->error("BAD::MOVE::ERROR cannot move right");
                    co_return;
                } 
                grid_.cursor.x++; 
                break;

            default: 
                std::unreachable();
        } 
  
        // suspend here
        co_await std::suspend_always{}; 
    } 

    std::unreachable();
}