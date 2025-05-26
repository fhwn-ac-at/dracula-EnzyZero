#include <gtest/gtest.h>
#include <iostream>
#include <spdlog/sinks/null_sink.h>
#include "perf_hashtable.h"

unsigned call_count = 0;

cmds::code func(GridBase& grid, Stack<cmds::stack_value_type>& stack, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& logger) {
    call_count++;
    return cmds::ok;
}

TEST(HashTable, Basic) {

    std::function<cmds::signature> cb = func;
    GridBase grd;
    Stack<cmds::stack_value_type> s;
    auto logger = spdlog::null_logger_st("nolog");

    auto test = [&](){ 

        using PerfHashtable = PerfHashtable<std::function<cmds::signature>>;

        const PerfHashtable 
        hasht
        { 
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

        using namespace cmds;

        EXPECT_EQ(hasht.at('a').value()(grd, s, std::cin, std::cout, logger), ok);
        EXPECT_EQ(hasht.at('l').value()(grd, s, std::cin, std::cout, logger), ok);
        EXPECT_EQ(hasht.at('q').value()(grd, s, std::cin, std::cout, logger), ok);
        EXPECT_EQ(hasht.at('S').value()(grd, s, std::cin, std::cout, logger), ok);
        EXPECT_EQ(hasht.at('J').value()(grd, s, std::cin, std::cout, logger), ok);
        EXPECT_EQ(hasht.at('m').value()(grd, s, std::cin, std::cout, logger), ok);
        EXPECT_EQ(hasht.at('k').value()(grd, s, std::cin, std::cout, logger), ok);

        EXPECT_EQ(hasht.at('c').error(), PerfHashtable::table_miss{});

        EXPECT_EQ(call_count, 7);
    };

    ASSERT_NO_THROW(test());
}