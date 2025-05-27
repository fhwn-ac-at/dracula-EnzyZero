#include <fstream>
#include <spdlog/logger.h>
#include "grid.h"


Grid::Grid(const char path[], std::shared_ptr<spdlog::logger> logger)
:   file_( path ),
    logger_( std::move(logger) )
{
    if (!operator bool())
        goto critical;

    // read from the ifstream
    for (auto& line : this->grid_)
    {
        signed char c{};

        for(auto& field : line)
        {
            file_ >> c;

            if (c == '\n' || !file_.good() ) // good includes reaching eof
                break;

            // add character to row
            field = c;
        }

        if ( file_.eof() )
            break;

        else if (!operator bool()) // file error
            goto critical;

        // if c is not a newline, this will consume the newline (69 characters +1 newline is allowed)
        else if (c != '\n' && file_.get() != '\n' )
        {
            // set failbit in file
            file_.setstate(std::ios_base::failbit);
            logger_->error("GRID::INVALID::SIZE: Line is longer than {}.", line.size());
            return;
        }
    }

    /*  Now, either eof is reached or
        eof comes right after the current file pointer or
        the next line is an empty line and the last line (eof after a newline).
        If not, the file does not adhere to the necessary height.
    */
    if ( !( 
        file_.eof() ||  
        file_.peek() == EOF || 
        (file_.get() == '\n' && file_.get() == EOF)
        ) 
    ) 
    {
        file_.setstate(std::ios_base::failbit);
        logger_->error("GRID::INVALID:SIZE: File has more than {} rows", this->grid_.size());
    }

    // else, clear all failbits (get might set failbit on reaching eof)
    file_.clear(file_.rdstate() & ~std::ios::failbit);
    return;

critical:
    logger_->critical("GRID::FILE::ERROR: The given file might not exist"); 
}