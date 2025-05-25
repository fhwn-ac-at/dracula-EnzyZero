#include <iostream>
#include <chrono>
#include <memory> 
#include <functional>

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "interpreter.h"
#include "sink.h"
#include "start_ncurses.h"
#include "windows.h" 
#include "perf_hashtable.h"
#include "grid.h"
#include "streambuf.h"

int main(int nargs, char* args[]) { 

    /**
     * 1. Creating a logger for coloured output. 
     * 2. Boilerplate args checking
     * 3. Creating the grid from file.
     */
    std::shared_ptr<spdlog::logger> logger = spdlog::stdout_color_st("console");

    if (nargs != 2)
    {
        logger->error("No filename passed.");
        logger->info("Usage: out <filename>");
        return 1;
    }

    // read data from file and create a grid
    Grid grid(args[1], logger);
    if (!grid)
        return 1;

    /**
     *  Now, ncurses will be started.
     *  The windows will be created as well as some settings tweaked to make them pretty and useful :) 
     *  The ncurses obj only really only exists for calling endwin() in its destructor.
     *  It also holds a window_base "mainwin" which is the standard screen.
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
     * Ncurses captures normal iostreams and provides its own wrapper. 
     * 
     * The last ingredient is the hashtable, which will be initalised with the commands.
     */
    auto log_sink = std::make_shared<ui::sink_st>( logw );
    logger->sinks().clear();
    logger->sinks().emplace_back(log_sink);
 
    // streambuf
    ui::streambuf streamb(iow.subwindows()[0]);
    std::iostream nc(&streamb);   

    using namespace cmds::flow;
    using namespace cmds::stck;
    using namespace cmds::io;

    // you may guess  
    perf_hashtable<std::function<cmds::signature>> 
    hasht
    { 
        {'e', e },
        {'x', x },
        {'X', X },
        {'p', p },
        {'P', P },
        {'d', d },
        {'D', D },
        {'h', h },
        {'H', H },
        {'o', o },
        {'O', O },
        {'R', R },
        {'r', r },
        {'f', f },
        {'F', F },
        {'j', j },
        {'J', J },
        {'i', i },
        {'I', I },
        {'l', l },
        {'L', L },
        {'s', s },
        {'S', S },
        {'a', a },
        {'A', A },
        {'k', k },
        {'K', K },
        {'m', m },
        {'M', M },
        {'q', q },
        {'Q', Q }
    }; 

    /**
     * 1. Make the interpreter and pass resources
     * 2. Run it again and again with a delay
     * 3. If its done, its done  
     */ 

    Interpreter interpreter(grid, hasht, std::cin, std::cout, logger); 

    // TODO operators missing
  
    while (!interpreter.done())   
    {
        std::this_thread::sleep_for( std::chrono::milliseconds(500) ); 
        interpreter.resume();
    }
}