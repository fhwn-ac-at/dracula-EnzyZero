#include <iostream>
#include <spdlog/spdlog.h>
#include <chrono>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "ui.h"
#include "grid.h"

struct ui_section {
    int height;
    int width;
    int starty;
    int startx;

    void make_window(ui::ncurse& obj, const std::string name) {
        obj.add_win(name, height, width, starty, startx);
    }
};

int main() {

    #if 0
    /**
     *  Setting up text-based ui with ncurses
     *  Helper structs will be defined to describe each section in the ui.
     *  With the apply_self method, the structs will create windows in the Ncurses object
     */
    ui::ncurse curse;

    auto [height, width] = curse.get_dimensions();

    ui_section code { 
        .height = static_cast<int>(height * 0.75),
        .width  = static_cast<int>(width  * 0.66)
    };

    ui_section io {
        .height = height - code.height,
        .width  = width,
        .starty = code.height,
    };

    ui_section pos {
        .height = height - code.height,
        .width  = width  - code.width,
        .startx = code.width,
    };

    ui_section stack {
        .height = height - pos.height - io.height,
        .width  = pos.width,
        .starty = pos.height,
        .startx = pos.startx
    };

    code.make_window(curse,  "code");
    io.make_window(curse,    "io");
    pos.make_window(curse,   "pos");
    stack.make_window(curse, "stack");

    std::cin.get();

    #endif
    
    auto logger = spdlog::stdout_color_mt("testlogger");

    std::ifstream file("trash/test.txt");

    grid grd(std::move(file), logger);

    logger->info("First char {}", grd.catcur());

}