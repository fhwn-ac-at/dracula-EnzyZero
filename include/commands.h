#ifndef commands_h
#define commands_h 

#include <iostream>
#include <functional> 
#include <memory>
#include <spdlog/logger.h>
#include "interpreter.h"
#include "grid_base.h"
#include "stack.h"
 
namespace commands {

    enum error : int {

        ok,
        invalid_char
    };

    using signature = std::function<error
    (
        grid_base&, 
        Stack<Interpreter::value_type>&, 
        std::iostream&, 
        std::ostream&, 
        std::shared_ptr<spdlog::logger>&
    )>;
};

#endif