#include <iostream>
#include <chrono>
#include <memory>

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "sink.h"
#include "start_ncurses.h"
#include "windows.h"
#include "grid_base.h"
#include "grid.h"

int main(int nargs, char* args[]) { 

    // Creating loggers and a coloured sink for logging to terminal. 
    auto terminal_sink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
    auto mainlogger = std::make_shared<spdlog::logger>("mainlogger", terminal_sink);

    if (nargs != 2)
    {
        mainlogger->error("No filename passed.");
        mainlogger->info("Usage: out <filename>");
        return 1;
    }

    // read data from file and create a grid
    Grid grid(args[1], mainlogger);
    if (!grid)
        return 1;

    /**
     *  Now, ncurses will be started.
     *  The windows will be created as well as some settings tweaked to make them pretty and useful :)
     */  
    ui::ncurses start{};

    int height = start.mainwin.height;
    int width  = start.mainwin.width;


    ui::window gridw (
        static_cast<int>(height * 0.66), // height
        static_cast<int>(width  * 0.66)  // width
    );
    gridw.make_classic_border();
    gridw.create_subwindow();
    gridw.refresh();

    ui::window logw ( 
        (height - gridw.height) / 2,
        width,
        gridw.height
    );
    logw.make_classic_border();
    logw.set_scrollok(true);
    logw.create_subwindow();
    logw.refresh();

    ui::window iow (
        height - gridw.height - logw.height,
        width,
        logw.starty + logw.height
    );
    iow.make_classic_border();
    iow.set_scrollok(true);
    iow.refresh();

    ui::window posw (
        gridw.height / 2,
        width - gridw.width,
        0,
        gridw.width
    ); 
    posw.make_classic_border();
    posw.refresh();

    ui::window stackw (
        height - posw.height - iow.height - logw.height,
        posw.width,
        posw.height,
        posw.startx
    ); 
    stackw.make_classic_border();
    stackw.refresh();

    /*
     * Now that we have ourselves some windows, we cannot print to stdout anymore.
     * A special sink will be used which prints to the "logw" window.
     * Swap the sinks in the mainlogger to now print to the log window.
     */
    auto log_sink = std::make_shared<ui::sink_st>( logw );
    mainlogger->sinks().clear();
    mainlogger->sinks().emplace_back(log_sink);

    // make grid operator

    std::cin.get();
}