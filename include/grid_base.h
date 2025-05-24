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

    /**
     * @brief safe get char at current cursor value in the grid
     * 
     * @return char& char at cur
     */
    virtual char& catcurs() { return grid_.at(cursor.y).at(cursor.x); }

    /**
     * @brief unsafe get char at current cursor value in the grid
     * 
     * @return char& cahr at cur
     */
    virtual char& catcur() noexcept { return grid_[cursor.y][cursor.x]; }

    virtual ~grid_base() = default;

    // matrix with height=42 and width=69, very sus
    std::array<std::array<char, 69>, 42> grid_{};
};

#endif