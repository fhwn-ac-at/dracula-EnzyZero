#ifndef grid_base_h
#define grid_base_h

#include <array>
#include <stdint.h>
#include <spdlog/logger.h>
#include "cursor.h"

class Grid_base
{
public:
    Cursor cursor{};

    Grid_base() = default;

    char &catcur() { return grid_.at(cursor.y).at(cursor.x); }

    char &catpos(const unsigned y, const unsigned x) { return grid_.at(y).at(x); } 

    virtual ~Grid_base() = default;

protected:
    // matrix with height=42 and width=69, very sus 
    std::array<std::array<char, 69>, 42> grid_{};   

public:
    auto matrix() -> decltype(grid_)&  { return grid_; }
};

#endif