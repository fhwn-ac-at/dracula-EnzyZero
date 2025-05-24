#ifndef interpreter_h
#define interpreter_h 

#include <iostream>
#include <spdlog/logger.h>
#include <memory>
#include "grid_base.h"
#include "stack.h"
#include "coroutine.h" 

class Interpreter {
public:

    using value_type = long;

    Interpreter(
        grid_base& grid, 
        std::istream& istream, 
        std::ostream& ostream, 
        std::shared_ptr<spdlog::logger>& logger
    ) 
    :   grid_(grid), istream_(istream), ostream_(ostream), logger_(logger), coro_(interpret())
    {}

    operator bool() { return !!coro_; }
    bool done() { return coro_.done(); }

    void resume() { coro_.resume(); } 
    void operator()() { coro_(); }

    ~Interpreter() = default;

private:
    Stack<value_type> stack_;
    grid_base& grid_;
    std::istream& istream_;
    std::ostream& ostream_;
    std::shared_ptr<spdlog::logger> logger_;
    Coroutine coro_;

    Coroutine interpret() { co_return; }

    
    friend class ui::grid_operator;
};


#endif