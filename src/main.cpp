#include <iostream>
#include <spdlog/spdlog.h>
#include <chrono>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "ui.h"
#include "ui_window_handlers.h"
#include "grid.h"


int main() {

    /**
     *  Setting up text-based ui with ncurses
     *  Helper structs will be defined to describe each section in the ui.
     *  With the apply_self method, the structs will create windows in the Ncurses object
     */
    ui::ncurse curse;

    auto [height, width] = curse.get_dimensions();

    ui::window_section grid { 
        .height = static_cast<int>(height * 0.66),
        .width  = static_cast<int>(width  * 0.66)
    };

    ui::window_section log {
        .height = height - code.height / 2,
        .width = width,
        .starty = code.height
    };

    ui::window_section io {
        .height = height - code.height - log.height,
        .width  = width,
        .starty = log.height
    };

    ui::window_section pos {
        .height = code.height / 2,
        .width  = width - code.width,
        .startx = code.width,
    };

    ui::window_section stack {
        .height = height - pos.height - io.height - log.height,
        .width  = pos.width,
        .starty = pos.height,
        .startx = pos.startx
    };

    curse.add_win("grid", grid);
    curse.add_win("log", log);
    curse.add_win("io", io);
    curse.add_win("pos", pos);
    curse.add_win("stack", stack);

    /*
     * Getting a logger which will be passed to whichever window handler needs one.
     * The logger will have a sink which is linked to the "log" window.
     * Therefore, all logs will be displayed there.
     * 
     * Then, all the window handlers will be registered to the curses object.
     */
    std::shared_ptr<ui::sink_st> log_sink = curse.sink_for_window("log");
    spdlog::logger window_logger("window_logger", log_sink);

    curse.register_window_handler<grid_window_handler>("grid", window_logger, grid);

    curse.update();

    std::cin.get();
}