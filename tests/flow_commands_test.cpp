#include <gtest/gtest.h> 
#include <array>
#include <string_view>
#include <spdlog/sinks/null_sink.h>
#include <perf_hashtable.h>
#include "commands.h" 

constexpr std::array<std::string_view, 3> grid_input 
{
    "1Hello World",
    "20123456789",
    "3Cruel World"
}; 

using namespace cmds::flow;

class Flow : public testing::Test {
public:  

    using PerfHashtable = PerfHashtable<std::function<cmds::signature>>;

    void SetUp() override { 

        assert(grid_input.size() == grid.matrix().size() && "Grid row count mismatch"); 

        // copy grid_input chars to grid.grid_
        for (size_t row = 0; row < grid_input.size(); row++) 
        { 
            auto& gline     = grid.matrix().at(row);
            auto& inputline = grid_input.at(row); 

            size_t len = std::min(gline.size(), inputline.size()); 

            for (size_t col = 0; col < len; ++col) 
                gline.at(col) = inputline.at(col);
        }
    }
 
    Stack<char> stack;
    GridBase grid;
    std::shared_ptr<spdlog::logger> logger = spdlog::null_logger_st("nolog");
    PerfHashtable hasht
    {
        {'e', e },
        {'l', l },
        {'L', L },
        {'k', k },
        {'K', K },
        {'j', j },
        {'J', J },
        {'h', h },
        {'H', H },

        {'x', no },
        {'I', no },
        {'P', no },
        {'s', no },
        {'d', no },
        {'O', no },
        {'r', no },
        {'a', no },
        {'F', no },
        {'M', no },
        {'q', no },
        {'X', no },
        {'D', no },
        {'i', no },
        {'p', no },
        {'S', no },
        {'A', no },
        {'o', no },
        {'R', no },
        {'f', no },
        {'m', no },
        {'Q', no }
    };  

    static cmds::code no(GridBase& grid, Stack<cmds::stack_value_type>& stack, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& logger) { 
        return cmds::err;
    }
};


TEST_F(Flow, h) { 
    ASSERT_TRUE(hasht.at('h').has_value());

    auto cmd = *hasht.at('h');  
    EXPECT_EQ(cmd(grid, stack, std::cin, std::cout, logger), cmds::ok); 
    EXPECT_EQ(grid.cursor.dir, Cursor::LEFT);
} 

TEST_F(Flow, j) { 
    ASSERT_TRUE(hasht.at('j').has_value());

    auto cmd = *hasht.at('j');  
    EXPECT_EQ(cmd(grid, stack, std::cin, std::cout, logger), cmds::ok); 
    EXPECT_EQ(grid.cursor.dir, Cursor::DOWN);
} 

TEST_F(Flow, k) { 
    ASSERT_TRUE(hasht.at('k').has_value());

    auto cmd = *hasht.at('k');  
    EXPECT_EQ(cmd(grid, stack, std::cin, std::cout, logger), cmds::ok); 
    EXPECT_EQ(grid.cursor.dir, Cursor::UP);
} 

TEST_F(Flow, l) { 
    ASSERT_TRUE(hasht.at('l').has_value());

    auto cmd = *hasht.at('l');  
    EXPECT_EQ(cmd(grid, stack, std::cin, std::cout, logger), cmds::ok); 
    EXPECT_EQ(grid.cursor.dir, Cursor::RIGHT);
} 

TEST_F(Flow, H) {  
    constexpr char C = 'H'; 

    ASSERT_TRUE(hasht.at(C).has_value());
 
    // this should fail "stack empty"
    auto cmd = *hasht.at(C);  
    EXPECT_EQ(cmd(grid, stack, std::cin, std::cout, logger), cmds::err);  
 
    // not found 
    stack.push(' '); 
    auto cmd = *hasht.at(C);  
    EXPECT_EQ(cmd(grid, stack, std::cin, std::cout, logger), cmds::err);  
     
    // ok and found 
    grid.cursor.x = 5;  
    stack.push('1');
    auto cmd = *hasht.at(C);  
    EXPECT_EQ(cmd(grid, stack, std::cin, std::cout, logger), cmds::ok);  
    EXPECT_EQ(Cursor::LEFT, grid.cursor.dir);  
    EXPECT_EQ(0, grid.cursor.x);
    EXPECT_EQ(0, grid.cursor.y); 
}  

TEST_F(Flow, J) { 
    constexpr char C = 'J';  

    ASSERT_TRUE(hasht.at(C).has_value());
 
    // this should fail "stack empty"
    auto cmd = *hasht.at(C);  
    EXPECT_EQ(cmd(grid, stack, std::cin, std::cout, logger), cmds::err);  
 
    // not found 
    stack.push(' '); 
    auto cmd = *hasht.at(C);  
    EXPECT_EQ(cmd(grid, stack, std::cin, std::cout, logger), cmds::err);  
     
    // ok and found 
    grid.cursor.x = 5;  
    stack.push('1');
    auto cmd = *hasht.at(C);  
    EXPECT_EQ(cmd(grid, stack, std::cin, std::cout, logger), cmds::ok);  
    EXPECT_EQ(Cursor::LEFT, grid.cursor.dir);  
    EXPECT_EQ(0, grid.cursor.x);
    EXPECT_EQ(0, grid.cursor.y); 
}
