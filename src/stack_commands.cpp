#include "commands.h"


namespace cmds { 
namespace stck {

code 
s(GridBase& grid, Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{ 
    if(!below_avail(grid)) 
    {
        log->error("BAD::CELL::ACCESS cannot access value below");
        return err;
    }
    
    s.push( grid.catpos(grid.cursor.y+1, grid.cursor.x) );
    return ok;
} 

code 
S(GridBase& grid, Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{ 
    if(!above_avail(grid)) 
    {
        log->error("BAD::CELL::ACCESS cannot access value above");
        return err;
    }
    
    s.push( grid.catpos(grid.cursor.y-1, grid.cursor.x) );
    return ok;
} 

code 
d([[maybe_unused]] GridBase& grid, Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{
    if(s.empty())
    {
        log->error("STACK::IS::EMPTY cannot duplicate");
        return err;
    } 

    s.push( s.peek() );
    return ok;
}

code 
D([[maybe_unused]] GridBase& grid, Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{
    if(s.empty())
    {
        log->error("STACK::IS::EMPTY cannot delete");
        return err;
    } 

    s.pop();
    return ok;
}

code 
a(GridBase& grid, Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{ 
    if(!below_avail(grid)) 
    {
        log->error("BAD::CELL::ACCESS cannot access value below");
        return err;
    }
    else if(s.empty())
    {
        log->error("STACK::IS::EMPTY cannot add");
        return err;
    } 

    s.peek() += grid.catpos( grid.cursor.y+1, grid.cursor.x ); 
    return ok;
} 

code 
A(GridBase& grid, Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{ 
    if(!above_avail(grid)) 
    {
        log->error("BAD::CELL::ACCESS cannot access value above");
        return err;
    }
    else if(s.empty())
    {
        log->error("STACK::IS::EMPTY cannot add");
        return err;
    } 

    s.peek() += grid.catpos( grid.cursor.y-1, grid.cursor.x ); 
    return ok;
}

code 
r(GridBase& grid, Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{ 
    if(!below_avail(grid)) 
    {
        log->error("BAD::CELL::ACCESS cannot access value below");
        return err;
    }
    else if(s.empty())
    {
        log->error("STACK::IS::EMPTY cannot reduce");
        return err;
    } 

    s.peek() -= grid.catpos( grid.cursor.y+1, grid.cursor.x ); 
    return ok;
} 

code 
R(GridBase& grid, Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{ 
    if(!above_avail(grid)) 
    {
        log->error("BAD::CELL::ACCESS cannot access value above");
        return err;
    }
    else if(s.empty())
    {
        log->error("STACK::IS::EMPTY cannot reduce");
        return err;
    } 

    s.peek() -= grid.catpos( grid.cursor.y-1, grid.cursor.x ); 
    return ok;
} 

code 
p(GridBase& grid, Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{ 
    if(!below_avail(grid)) 
    {
        log->error("BAD::CELL::ACCESS cannot access value below");
        return err;
    }
    else if(s.empty())
    {
        log->error("STACK::IS::EMPTY cannot multiply");
        return err;
    } 

    s.peek() *= grid.catpos( grid.cursor.y+1, grid.cursor.x ); 
    return ok;
}

code 
P(GridBase& grid, Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{ 
    if(!above_avail(grid)) 
    {
        log->error("BAD::CELL::ACCESS cannot access value above");
        return err;
    }
    else if(s.empty())
    {
        log->error("STACK::IS::EMPTY cannot multiply");
        return err;
    } 

    s.peek() *= grid.catpos( grid.cursor.y-1, grid.cursor.x ); 
    return ok;
}

code 
q(GridBase& grid, Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{ 
    if(!below_avail(grid)) 
    {
        log->error("BAD::CELL::ACCESS cannot access value below");
        return err;
    }
    else if(s.empty())
    {
        log->error("STACK::IS::EMPTY cannot divide");
        return err; 
    } 

    s.peek() /= grid.catpos( grid.cursor.y+1, grid.cursor.x ); 
    return ok;
}

code 
Q(GridBase& grid, Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{ 
    if(!above_avail(grid)) 
    {
        log->error("BAD::CELL::ACCESS cannot access value above");
        return err;
    }
    else if(s.empty())
    {
        log->error("STACK::IS::EMPTY cannot divide");
        return err;
    } 

    s.peek() /= grid.catpos( grid.cursor.y-1, grid.cursor.x ); 
    return ok;
}

code 
m(GridBase& grid, Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{ 
    if(!below_avail(grid)) 
    {
        log->error("BAD::CELL::ACCESS cannot access value below");
        return err;
    }
    else if(s.empty())
    {
        log->error("STACK::IS::EMPTY cannot take the modulus");
        return err; 
    } 

    s.peek() %= grid.catpos( grid.cursor.y+1, grid.cursor.x ); 
    return ok;
}

code 
M(GridBase& grid, Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{ 
    if(!above_avail(grid)) 
    {
        log->error("BAD::CELL::ACCESS cannot access value above");
        return err;
    }
    else if(s.empty())
    {
        log->error("STACK::IS::EMPTY cannot take the modulus");
        return err;
    } 

    s.peek() %= grid.catpos( grid.cursor.y-1, grid.cursor.x ); 
    return ok;
}

code 
f(GridBase& grid, Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{ 
    if (!below_avail(grid))
    {
        log->error("BAD::CELL::ACCESS cannot access value below");
        return err;
    }
    else if (s.empty())
    {
        log->error("STACK::IS::EMPTY cannot pop");
        return err;
    }

    grid.catpos( grid.cursor.y+1, grid.cursor.x ) = s.pop();
    return ok;
} 

code 
F(GridBase& grid, Stack<stack_value_type>& s, [[maybe_unused]] std::istream& is, [[maybe_unused]] std::ostream& os, [[maybe_unused]] std::shared_ptr<spdlog::logger>& log)
{ 
    if (!above_avail(grid))
    {
        log->error("BAD::CELL::ACCESS cannot access value above");
        return err;
    }
    else if (s.empty())
    {
        log->error("STACK::IS::EMPTY cannot pop");
        return err;
    }

    grid.catpos( grid.cursor.y-1, grid.cursor.x ) = s.pop();
    return ok;
}

} // stack namespace
} // cmds namespace