#include <iostream>
#include <chrono>
#include <memory>

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "interpreter.h"
#include "sink.h"
#include "start_ncurses.h"
#include "windows.h"
#include "grid_base.h"
#include "grid.h"
#include "streambuf.h"

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
    gridw.box();
    gridw.create_subwindow();
    gridw.refresh();

    ui::window logw ( 
        (height - gridw.height) / 2,
        width,
        gridw.height
    );
    logw.box();
    logw.set_scrollok(true);
    logw.create_subwindow();
    logw.refresh();

    ui::window iow (
        height - gridw.height - logw.height,
        width,
        logw.starty + logw.height
    );
    iow.box();
    iow.create_subwindow();
    iow.set_scrollok(true);
    iow.refresh();

    ui::window posw (
        gridw.height / 2,
        width - gridw.width,
        0,
        gridw.width
    ); 
    posw.box();
    posw.refresh();

    ui::window stackw (
        height - posw.height - iow.height - logw.height,
        posw.width,
        posw.height,
        posw.startx
    ); 
    stackw.box();
    stackw.refresh();

    /*
     * Now that we have ourselves some windows, we cannot print to stdout anymore.
     * A special sink will be used which prints to the "logw" window.
     * Swap the sinks in the mainlogger to now print to the log window.
     * 
     * Also, a special streambuf will be created to print to the io window instead of to stdout/in. 
     * This allows for still using the std::iostream classes.
     */
    auto log_sink = std::make_shared<ui::sink_st>( logw );
    mainlogger->sinks().clear();
    mainlogger->sinks().emplace_back(log_sink);

    ui::streambuf streamb(iow.subwindows()[0]);
    std::iostream nc(&streamb); 

    /**
     * Now the interpreter will be started along with the operators which 
     * print information to the windows.
     */

    
    
 
    nc.get();
}