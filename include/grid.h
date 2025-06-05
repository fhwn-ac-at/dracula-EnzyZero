#include <fstream>
#include <spdlog/logger.h>
#include <memory>
#include "grid_base.h"

class Grid : public GridBase {
public:

    /**
     * @brief Construct a new grid object from an ifstream
     * 
     * Checks that the file fits into the grid. Newlines will not be put into the grid. 
     * The logic allows for lines with 69 characters +1 newline.
     * There may be 42 lines in the file +1 empty line
     * 
     * If an error occurs, the failbit will be set int the file_ member.
     * Use the operator bool() method to check for failures like invalid dimensions of the file.
     * 
     * @param path path to file
     * @param logger spdlog::logger used to log
     */
    Grid(const char* path, std::shared_ptr<spdlog::logger> logger);

    /**
     * @brief check for failure bits in the filestream
     * 
     * @return true 
     * @return false 
     */
    operator bool() { return !file_.fail(); } 

    ~Grid() override = default;
 
private: 
    std::ifstream file_;
    std::shared_ptr<spdlog::logger> logger_; 

    Grid(Grid& other) = delete;
    Grid& operator=(Grid& other) = delete;
};

