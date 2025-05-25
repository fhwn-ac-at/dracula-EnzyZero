#ifndef interpreter_h
#define interpreter_h 

#include <iostream>
#include <spdlog/logger.h>
#include <memory>
#include "grid_base.h"
#include "perf_hashtable.h"
#include "stack.h"
#include "coroutine.h" 

class Interpreter {
public:

    Interpreter(
        grid_base& grid,  
        const perf_hashtable& hasht,
        std::istream& istream, 
        std::ostream& ostream, 
        std::shared_ptr<spdlog::logger>& logger
    ) 
    :   grid_(grid), hasht_(hasht), istream_(istream), ostream_(ostream), logger_(logger), coro_(interpret())
    {}

    operator bool() { return !!coro_; }
    bool done() { return coro_.done(); }

    void resume() { coro_.resume(); } 
    void operator()() { coro_(); }

    ~Interpreter() = default;


    /// @details these members are public for derivatives of operator_base
    stack<char> stack_;
    grid_base& grid_;

private:
    const perf_hashtable& hasht_;
    std::ostream& ostream_;
    std::istream& istream_;
    std::shared_ptr<spdlog::logger> logger_; 

    Coroutine coro_;
    Coroutine interpret() { co_return; }
};

#endif