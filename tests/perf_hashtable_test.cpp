#include <gtest/gtest.h>
#include <iostream>
#include <spdlog/sinks/null_sink.h>
#include "perf_hashtable.h"

unsigned call_count = 0;

commands::error func(grid_base& grid, stack<commands::stack_value_type>& stack, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& logger) {
    call_count++;
    return commands::ok;
}

TEST(HashTable, Basic) {

    commands::signature cb = func;
    grid_base grd;
    stack<commands::stack_value_type> s;

    auto null_sink = std::make_shared<spdlog::sinks::null_sink_st>();
    auto logger = std::make_shared<spdlog::logger>("null_logger", null_sink);

    auto test = [&](){

        const perf_hashtable hasht{
            {'x', cb },
            {'e', cb },
            {'I', cb },
            {'l', cb },
            {'P', cb },
            {'s', cb },
            {'d', cb },
            {'H', cb },
            {'k', cb },
            {'O', cb },
            {'r', cb },
            {'a', cb },
            {'F', cb },
            {'j', cb },
            {'M', cb },
            {'q', cb },
            {'X', cb },
            {'D', cb },
            {'i', cb },
            {'L', cb },
            {'p', cb },
            {'S', cb },
            {'A', cb },
            {'h', cb },
            {'K', cb },
            {'o', cb },
            {'R', cb },
            {'f', cb },
            {'J', cb },
            {'m', cb },
            {'Q', cb }
        };

        using namespace commands;

        EXPECT_EQ(hasht('a', grd, s, std::cin, std::cout, logger), ok);
        EXPECT_EQ(hasht('l', grd, s, std::cin, std::cout, logger), ok);
        EXPECT_EQ(hasht('q', grd, s, std::cin, std::cout, logger), ok);
        EXPECT_EQ(hasht('S', grd, s, std::cin, std::cout, logger), ok);
        EXPECT_EQ(hasht('J', grd, s, std::cin, std::cout, logger), ok);
        EXPECT_EQ(hasht('m', grd, s, std::cin, std::cout, logger), ok);
        EXPECT_EQ(hasht('k', grd, s, std::cin, std::cout, logger), ok);

        EXPECT_EQ(hasht('c', grd, s, std::cin, std::cout, logger), invalid_char);

        EXPECT_EQ(call_count, 7);
    };

    ASSERT_NO_THROW(test());
}