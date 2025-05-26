#ifndef perf_hashtable_impl_h
#define perf_hashtable_impl_h

#include <stdexcept>
#include "perf_hashtable.h" 

template <typename T>
const unsigned PerfHashtable<T>::hash (const char c)
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
        12, 32,  7,  2, 28, 24, 19, 14, 32,  9,
        4, 30, 26, 21, 32, 32, 32, 32, 16, 32,
        32, 32, 32, 32, 32, 32, 32, 11, 32, 32,
        6,  1, 27, 32, 23, 18, 13,  8,  3, 29,
        32, 25, 20, 15, 10,  5, 32, 32, 32, 32,
        0, 32, 32, 32, 32, 32, 32, 32
    };

    return asso_values[static_cast<unsigned char>(c)];
}

template <typename T>
const bool PerfHashtable<T>::in_word_set (const char c)
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
        'f',
        'J',
        'm',
        'Q'
    };

    if (hash(c) <= MAX_HASH_VALUE)
        return true;

    return false;
}

template <typename T>
auto PerfHashtable<T>::to_array(std::initializer_list<std::pair<char, T>> list) -> std::array<T, TOTAL_KEYWORDS> 
{
    if (list.size() != TOTAL_KEYWORDS)
        throw std::range_error("initalizer list must be equal to MAX_HASH_VALUE");
 
    // make a temp array and copy list contents into it
    std::array<std::function<cmds::signature>, TOTAL_KEYWORDS> arr{}; 

    for (auto& pair : list) 
    { 
        if (!in_word_set(pair.first))
            throw std::invalid_argument("invalid key passed for hashtable"); 

        arr.at(hash(pair.first)) = pair.second; 
    }

    return arr;
} 

#endif