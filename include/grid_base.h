#ifndef grid_base_h
#define grid_base_h

#include <array>
#include <spdlog/logger.h>

class grid_base {
public:

    grid_base() = default;

    struct Cursor {
        int y{};
        int x{};

        enum direction : int {
            NONE,
            UP,
            DOWN,
            RIGHT,
            LEFT
        };

        direction dir{NONE};
    };

    Cursor cursor{}; 

    char& catcur() { return grid_.at(cursor.y).at(cursor.x); }

    char& catpos(const unsigned y, const unsigned x) { return grid_.at(y).at(x); } 

    virtual ~grid_base() = default;

    // matrix with height=42 and width=69, very sus
    std::array<std::array<char, 69>, 42> grid_{};
};

#endif