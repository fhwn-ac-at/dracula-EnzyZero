#ifndef commands_h
#define commands_h 

#include <stdint.h>
#include <iostream>
#include <memory>
#include <spdlog/logger.h>
#include "grid_base.h"
#include "stack.h"
 
namespace cmds { 

    enum code : uint8_t {
        ok,
        err,
        end
    };

    using stack_value_type = signed char;
    using signature = code(GridBase&, Stack<stack_value_type>&, std::istream&, std::ostream&, std::shared_ptr<spdlog::logger>&);   


    namespace flow 
    {
        code h(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code j(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code k(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code l(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code H(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code J(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code K(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code L(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code x(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code X(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code e(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
    }

    namespace stck
    {
        code s(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code S(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code d(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code D(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code a(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code A(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code r(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code R(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code p(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code P(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code q(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code Q(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code m(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code M(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code f(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code F(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
    } 

    namespace io 
    {
        code o(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code O(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code i(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
        code I(GridBase& grid, Stack<stack_value_type>& s, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& log);
    }

    inline bool at_left(GridBase& grid)     { return static_cast<size_t>(grid.cursor.x) <= 0; }
    inline bool at_right(GridBase& grid)    { return static_cast<size_t>(grid.cursor.x) >= grid.matrix().at(grid.cursor.x).size() -1; } 
    inline bool at_top(GridBase& grid)      { return static_cast<size_t>(grid.cursor.y) <= 0; }
    inline bool at_bot(GridBase& grid)      { return static_cast<size_t>(grid.cursor.y) >= grid.matrix().at(grid.cursor.y).size() -1; } 
    inline bool above_avail(GridBase& grid) { return static_cast<size_t>(grid.cursor.y) > 0; }
    inline bool below_avail(GridBase& grid) { return static_cast<size_t>(grid.cursor.y) < grid.matrix().size() -1; } 
}

#endif
