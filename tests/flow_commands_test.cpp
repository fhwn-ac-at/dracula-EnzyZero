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

    void SetUp() override { 

        assert(grid_input.size() == grid.grid_.size() && "Grid row count mismatch"); 

        // copy grid_input chars to grid.grid_
        for (size_t row = 0; row < grid_input.size(); row++) 
        { 
            auto& gline     = grid.grid_.at(row);
            auto& inputline = grid_input.at(row); 

            size_t len = std::min(gline.size(), inputline.size()); 

            for (size_t col = 0; col < len; ++col) 
                gline.at(col) = inputline.at(col);
        }
    }

    grid_base grid;
    std::shared_ptr<spdlog::logger> nosink = spdlog::null_logger_st("nolog");
    perf_hashtable hasht{

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

    static cmds::code no(grid_base& grid, stack<cmds::stack_value_type>& stack, std::istream& is, std::ostream& os, std::shared_ptr<spdlog::logger>& logger) { 
        return cmds::err;
    }

};




TEST_F(Flow, h) { 


}
