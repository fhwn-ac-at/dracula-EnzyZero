#ifndef perfect_hashtable_h
#define perfect_hashtable_h 

#include <array> 
#include <initializer_list>
#include <utility>
#include <memory>
#include <spdlog/logger.h>
#include "commands.h"
#include "grid_base.h"
#include "stack.h"

 
class perf_hashtable {
public: 

    perf_hashtable(std::initializer_list<std::pair<char, commands::signature>> list)
    :   commands_(to_array(list))
    {}

    commands::error operator()(
        const char c, 
        grid_base& grid, 
        stack<commands::stack_value_type>& stack, 
        std::istream& istream, 
        std::ostream& ostream, 
        std::shared_ptr<spdlog::logger>& logger 
    ) 
    const noexcept 
    { 
        const unsigned key = hash(c);
        return key > MAX_HASH_VALUE ? commands::invalid_char : commands_[key](grid, stack, istream, ostream, logger);
    }

private:

    static constexpr int TOTAL_KEYWORDS = 31; 
    static constexpr int MIN_HASH_VALUE = 0;
    static constexpr int MAX_HASH_VALUE = 30; 

    const std::array<commands::signature, TOTAL_KEYWORDS> commands_; 

    static const bool in_word_set(const char c); 
    static const unsigned hash(const char c);
    static auto to_array(std::initializer_list<std::pair<char, commands::signature>> list) -> std::array<commands::signature, TOTAL_KEYWORDS>; 
}; 

#endif