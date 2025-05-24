#ifndef commands_h
#define commands_h 

#include <functional> 
#include <iostream>
#include <memory>
#include <spdlog/logger.h>
#include "grid_base.h"
#include "stack.h"
 
namespace commands { 

    enum error : int {

        ok,
        invalid_char
    }; 

    using stack_value_type = long;

    using signature = std::function<error(grid_base&, stack<stack_value_type>&, std::iostream&, std::ostream&, std::shared_ptr<spdlog::logger>&)>;
};

#endif