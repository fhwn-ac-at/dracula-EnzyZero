#include <iostream>
#include <spdlog/spdlog.h>
#include <chrono>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "windows.h"
#include "window_manager.h"
#include "grid.h"

int main() { 

    /*
     * Getting a logger which will be passed to whichever window handler needs one.
     * The logger will have a sink which is linked to the "log" window.
     * Therefore, all logs will be displayed there.
     */
    //std::shared_ptr<ui::sink_st> log_sink = curse.sink_for_window("log");
    //spdlog::logger window_logger("window_logger", log_sink);

    //grid grd("");

    /**
     *  Setting up text-based ui with ncurses
     *  First, the dimensions of the window will be defined.
     *  Then, the windows will be moved into the window_manger and registered to it.
     *  The window manager saves them internally and maps an id to each of them, which will be returned.
     */ 

    int height = ui::mainwin.height; 
    int width  = ui::mainwin.width;

    ui::window grid { 
        static_cast<int>(height * 0.66), // height
        static_cast<int>(width  * 0.66)  // width
    };

    ui::window log {
        height - grid.height / 2,
        width,
        grid.height
    };

    ui::window io {
        height - grid.height - log.height,
        width,
        log.height
    };

    ui::window pos {
        grid.height / 2,
        width - grid.width,
        grid.width,
    };

    ui::window stack {
        height - pos.height - io.height - log.height,
        pos.width,
        pos.height,
        pos.startx
    }; 

    int 
        gridwin_id,
        logwin_id,
        iowin_id,
        poswin_id,
        stackwin_id;

    // creating a window manager 
    ui::window_manager winmanager;

    // register windows to manager
    {
        auto grid_res  = winmanager.create_window( std::move(grid) );
        auto log_res   = winmanager.create_window( std::move(log) );
        auto io_res    = winmanager.create_window( std::move(io) );
        auto pos_res   = winmanager.create_window( std::move(pos) );
        auto stack_res = winmanager.create_window( std::move(stack) );

        if (!grid_res || !log_res || !io_res || !pos_res || !stack_res)
            // logger here
            return 1;

        gridwin_id = *grid_res;
        logwin_id = *log_res;
        iowin_id = *io_res;
        poswin_id = *pos_res;
        stackwin_id = *stack_res;
    } 

    // register operators to the windows 
    // couple windows and operators 

    ui::mainwin.refresh();

    std::cin.get();
}