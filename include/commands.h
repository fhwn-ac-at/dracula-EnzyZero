#ifndef commands_h
#define commands_h 

#include <functional> 
#include <iostream>
#include <memory>
#include <spdlog/logger.h>
#include "grid_base.h"
#include "stack.h"
 
namespace cmds { 

    enum code : int {
        ok,
        err,
        end
    };

    using stack_value_type = char;
    using signature = code(grid_base&, stack<stack_value_type>&, std::istream&, std::ostream&, std::shared_ptr<spdlog::logger>&);   


    namespace flow 
    {
        code h(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code j(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code k(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code l(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code H(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code J(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code K(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code L(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code e(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
    }

    namespace stck
    {
        code s(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code S(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code d(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code D(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code a(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code A(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code r(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code R(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code p(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code P(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code q(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code Q(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code m(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code M(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code f(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code F(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
    } 

    namespace io 
    {
        code o(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code O(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code i(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code I(grid_base& grid, stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
    }

    inline bool at_left(grid_base& grid)     { return grid.cursor.x <= 0; }
    inline bool at_right(grid_base& grid)    { return grid.cursor.x >= grid.grid_.at(grid.cursor.x).size() -1; } 
    inline bool at_top(grid_base& grid)      { return grid.cursor.y <= 0; }
    inline bool at_bot(grid_base& grid)      { return grid.cursor.y >= grid.grid_.at(grid.cursor.y).size() -1; } 
    inline bool above_avail(grid_base& grid) { return grid.cursor.y > 0; }
    inline bool below_avail(grid_base& grid) { return grid.cursor.y < grid.grid_.size() -1; } 
}

#endif