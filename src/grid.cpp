#include <fstream>
#include <system_error>
#include <spdlog/logger.h>
#include "grid_base.h"

class grid : public grid_base {
public:

    grid(std::ifstream file, std::shared_ptr<spdlog::logger> logger)
    :   file_( std::move(file) ),
        logger_( std::move(logger) )
    {
        if (!operator bool())
            goto critical;

        // read from the ifstream
        for (auto& line : this->grid_)
        {
            char c { file_.get() };

            for(auto& field : line)
            {
                if (c == '\n' || !file.good() ) // good includes reaching eof
                    break;

                // if no error occured, add character to row
                field = c;

                c = file.get();
            }
            
            if (c != '\n')
            {
                // set failbit in file
                file.setstate(std::ios_base::failbit);
                logger_->error("GRID::INVALID::SIZE: Line is longer than {}.", line.size());
                return;
            }
            else if ( file.eof() )
                break;
            else if (!operator bool()) // file error
                goto critical;
        }

        /*  Now, either eof is reached or
            the next line is an empty line and the last line (eof after newline).
            If not, the file does not adhere to the necessary height.
        */
        if ( !(file.eof() || (file.get() == '\n' && file.get() == EOF)) ) 
        {
            file.setstate(std::ios_base::failbit);
            logger_->error("GRID::INVALID:SIZE: File has more than {} rows", this->grid_.size());
        }

        return;

    critical:
        logger_->critical("GRID::FILE::ERROR: failbit set!"); 
    } 

    operator bool() { return !file_.fail(); } 

    using grid_base::atcur;
    using grid_base::s_atcur;

    auto operator [](size_t i) noexcept -> decltype(grid_[0])& { return this->grid_[i]; }

    ~grid() override = default;
 
private: 
    std::ifstream file_;
    std::shared_ptr<spdlog::logger> logger_;
};