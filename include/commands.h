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
        miss, // hash table miss
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
}

#endif