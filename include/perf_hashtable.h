#ifndef perfect_hashtable_h
#define perfect_hashtable_h 

#include <expected>
#include <functional>
#include <array> 
#include <initializer_list>
#include <utility>
#include <memory>
#include <spdlog/logger.h>
#include "commands.h"
#include "grid_base.h"
#include "stack.h"

template <typename T> 
class PerfHashtable {
public: 
 
    /**
     * @brief Construct a new Perf Hashtable object from a list of key-value pairs
     * 
     * @param list key-value pairs where decltype(value) == T
     */
    PerfHashtable(std::initializer_list<std::pair<char, T>> list)
    :   values_(to_array(list))
    {}  

    struct table_miss{}; // error flag 
 
    /**
     * @brief returns the value of the key c
     * 
     * @param c key in the hashtable
     * @return std::expected<T, table_miss> either the value or an unexpected table_miss (empty struct)
     */
    auto at(const char c) const -> std::expected<T, table_miss>;

private:

    static constexpr int TOTAL_KEYWORDS = 31; 
    static constexpr int MIN_HASH_VALUE = 0;
    static constexpr int MAX_HASH_VALUE = 30; 

    const std::array<T, TOTAL_KEYWORDS> values_; 
 
    static bool in_word_set(const char c); 
    static unsigned hash(const char c);
    static auto to_array(std::initializer_list<std::pair<char, T>> list) -> std::array<T, TOTAL_KEYWORDS>; 
};   


template <typename T>
auto PerfHashtable<T>::at(const char c) const -> std::expected<T, table_miss>
{  
    unsigned key = hash(c);
    if (key > MAX_HASH_VALUE)
        return std::unexpected(table_miss{});

    return values_[key];
} 


#include "perf_hashtable_impl.h"

#endif