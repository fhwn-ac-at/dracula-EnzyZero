#ifndef grid_base_h
#define grid_base_h

#include <array>
#include <stdint.h>
#include <spdlog/logger.h>
#include "cursor.h"

/**
 * @brief Base for any grid, uses 7-Bit chars (signed)
 * 
 * Another derived will implement getting the grid from a file.
 */
class GridBase
{
public:
    Cursor cursor{}; // a grid uses a cursor

    GridBase() = default;
 
    /**
     * @brief return the character at the cursors current position
     * 
     * @return signed char& 
     */
    signed char &catcur() { return grid_.at(cursor.y).at(cursor.x); }
 
    /**
     * @brief return the character at the specified position in the grid
     * 
     * @param y height  
     * @param x  width
     * @return signed char& 
     */
    signed char &catpos(const unsigned y, const unsigned x) { return grid_.at(y).at(x); } 

    virtual ~GridBase() = default;

protected:
    // matrix with height=42 and width=69, very sus 
    std::array<std::array<signed char, 69>, 42> grid_{};   

public:
    auto matrix() -> decltype(grid_)&  { return grid_; }
};

#endif