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
 
    /**
     * @brief check if the underlying coro exists/is done
     * 
     * @return true 
     * @return false 
     */
    operator bool() { return !!coro_; }
    bool done() { return coro_.done(); }
 
    /**
     * @brief resume the underlying coro
     * 
     */
    void resume() { coro_.resume(); } 
    void operator()() { coro_(); }

    ~Interpreter() = default; 

private:  
    Stack<signed char> stack_; // an interpreter owns a stack 

    // but it uses a grid, hashtable, streams and a logger
    GridBase& grid_;
    const PerfHashtable<std::function<cmds::signature>>& hasht_;
    std::istream& istream_;
    std::ostream& ostream_;
    std::shared_ptr<spdlog::logger> logger_; 

    Coroutine coro_; // return obj of interpret(), used to resume
    Coroutine interpret(); // coroutine function

public: // access points for ui::operators
    auto stack() -> decltype(stack_)& { return stack_; } 
    auto grid() -> decltype(grid_)& { return grid_; }
};

#endif