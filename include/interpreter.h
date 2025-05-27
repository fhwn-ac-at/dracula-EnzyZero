#ifndef interpreter_h
#define interpreter_h 

#include <iostream>
#include <functional>
#include <spdlog/logger.h>
#include <memory>
#include "grid_base.h"
#include "perf_hashtable.h"
#include "stack.h"
#include "coroutine.h" 

class Interpreter {
public:

    Interpreter(
        GridBase& grid,  
        const PerfHashtable<std::function<cmds::signature>>& hasht,
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


private:  
    Stack<signed char> stack_;
    GridBase& grid_;
    const PerfHashtable<std::function<cmds::signature>>& hasht_;
    std::ostream& ostream_;
    std::istream& istream_;
    std::shared_ptr<spdlog::logger> logger_; 

    Coroutine coro_;
    Coroutine interpret();

public: // access points for ui::operators
    auto stack() -> decltype(stack_)& { return stack_; } 
    auto grid() -> decltype(grid_)& { return grid_; }
};

#endif