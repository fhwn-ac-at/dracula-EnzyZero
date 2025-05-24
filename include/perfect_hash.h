#ifndef perfect_hash_h
#define perfect_hash_h 

#include <array> 
#include <stdexcept>
#include <initializer_list>
#include <utility>
#include <memory>
#include <spdlog/logger.h>
#include "commands.h"
#include "interpreter.h"
#include "grid_base.h"
#include "stack.h"
 
class PerfHashtable {
public: 

    PerfHashtable(std::initializer_list<std::pair<char, commands::signature>> list)
    :   commands_(to_array(list))
    {}

    commands::error operator()(
        const char c, 
        grid_base& grid, 
        Stack<Interpreter::value_type>& stack, 
        std::iostream& istream, 
        std::ostream& ostream, 
        std::shared_ptr<spdlog::logger> logger 
    ) 
    const 
    { 
        const unsigned key = hash(c);
        return key > MAX_HASH_VALUE ? commands::invalid_char : commands_[key](grid, stack, istream, ostream, logger);
    }

private:
    static constexpr int TOTAL_KEYWORDS = 31;
    static constexpr int MIN_HASH_VALUE = 0;
    static constexpr int MAX_HASH_VALUE = 31;

    static const bool in_word_set(const char c); 
    static const unsigned hash(const char c);

    const std::array<commands::signature, TOTAL_KEYWORDS> commands_;

    static constexpr auto to_array(std::initializer_list<std::pair<char, commands::signature>> list) -> std::array<commands::signature, TOTAL_KEYWORDS> 
    {
        if (list.size() != TOTAL_KEYWORDS)
            throw std::range_error("initalizer list must be equal to TOTAL_KEYWORDS");
 
        // make a temp array and copy list contents into it
        std::array<commands::signature, TOTAL_KEYWORDS> arr{}; 

        for (auto& pair : list) 
        { 
            unsigned key = hash(pair.first);

            if (!in_word_set(key))
                throw std::invalid_argument("invalid key passed for hashtable"); 

            arr.at(key) = pair.second; 
        }

        return arr;
    }
}; 

inline const unsigned PerfHashtable::hash (const char c)
{
    static const unsigned char asso_values[] =
    {
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 22, 32, 32, 17, 32,
        12, 32,  7,  2, 29, 24, 19, 14, 32,  9,
        4, 31, 26, 21, 32, 32, 32, 32, 16, 32,
        32, 32, 32, 32, 32, 32, 32, 11, 32, 32,
        6,  1, 28, 32, 23, 18, 13,  8,  3, 30,
        32, 25, 20, 15, 10,  5, 32, 32, 32, 32,
        0, 32, 32, 32, 32, 32, 32, 32
    };

    return asso_values[static_cast<unsigned char>(c)];
}

inline const bool PerfHashtable::in_word_set (const char c)
{
    static const char wordlist[] =
    {
        'x',
        'e',
        'I',
        'l',
        'P',
        's',
        'd',
        'H',
        'k',
        'O',
        'r',
        'a',
        'F',
        'j',
        'M',
        'q',
        'X',
        'D',
        'i',
        'L',
        'p',
        'S',
        'A',
        'h',
        'K',
        'o',
        'R',
        0,
        'f',
        'J',
        'm',
        'Q'
    };

    unsigned key = hash(c);

    if (key <= MAX_HASH_VALUE)
        return true;

    return false;
}

#endif