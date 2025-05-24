#include <stdexcept>
#include "perf_hashtable.h"

const unsigned perf_hashtable::hash (const char c)
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

const bool perf_hashtable::in_word_set (const char c)
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
        0, // this will never be used, not sure why gperf does this
        'f',
        'J',
        'm',
        'Q'
    };

    if (hash(c) <= MAX_HASH_VALUE)
        return true;

    return false;
}

auto perf_hashtable::to_array(std::initializer_list<std::pair<char, commands::signature>> list) -> std::array<commands::signature, TOTAL_KEYWORDS> 
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