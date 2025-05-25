#include "commands.h"


namespace cmds { 
namespace stck {


code 
s(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
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
s(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
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
d(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
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
D(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
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
a(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
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
A(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
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
r(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
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
R(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
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
p(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
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

    s.push( s.peek() * grid.catpos( grid.cursor.y-1, grid.cursor.x ) ); 
    return ok;
}

code 
P(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{ 
    if(!below_avail(grid)) 
    {
        log->error("BAD::CELL::ACCESS cannot access value above");
        return err;
    }
    else if(s.empty())
    {
        log->error("STACK::IS::EMPTY cannot multiply");
        return err;
    } 

    s.push( s.peek() * grid.catpos( grid.cursor.y+1, grid.cursor.x ) ); 
    return ok;
}

code 
q(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
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

    s.push( s.peek() / grid.catpos( grid.cursor.y-1, grid.cursor.x ) ); 
    return ok;
}

code 
Q(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{ 
    if(!below_avail(grid)) 
    {
        log->error("BAD::CELL::ACCESS cannot access value above");
        return err;
    }
    else if(s.empty())
    {
        log->error("STACK::IS::EMPTY cannot divide");
        return err;
    } 

    s.push( s.peek() / grid.catpos( grid.cursor.y+1, grid.cursor.x ) ); 
    return ok;
}

code 
m(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
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

    s.push( s.peek() % grid.catpos( grid.cursor.y-1, grid.cursor.x ) ); 
    return ok;
}

code 
M(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log) 
{ 
    if(!below_avail(grid)) 
    {
        log->error("BAD::CELL::ACCESS cannot access value above");
        return err;
    }
    else if(s.empty())
    {
        log->error("STACK::IS::EMPTY cannot take the modulus");
        return err;
    } 

    s.push( s.peek() % grid.catpos( grid.cursor.y+1, grid.cursor.x ) ); 
    return ok;
}

code 
f(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log)  
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
F(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log)  
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