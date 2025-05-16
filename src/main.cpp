#include <iostream>
#include <spdlog/spdlog.h>
#include <chrono>
#include "curses.cpp"

int main() {


    /**
     *  Setting up text-based ui with ncurses
     *  
     */
    Ncurses curse{};

    auto [height, width] = curse.get_dimensions();
    curse.add_win("main", 10, 30, 0, 0);

    
    std::shared_ptr<Ncurses::sink_st> main_sink = curse.sink_for_win("main");
    auto logger = std::make_unique<spdlog::logger>("main_logger", main_sink);

}