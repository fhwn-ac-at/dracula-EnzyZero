#ifndef grid_base_h
#define grid_base_h

#include <array> 
#include <stdint.h>
#include <spdlog/logger.h>

class grid_base {
public:

    grid_base() = default;

    struct Cursor {
        int y{};
        int x{};
 
        /// @warning ORDER MATTERS!
        enum direction : uint8_t {
            NONE  = 0,
            UP    = 1,
            RIGHT = 2,
            DOWN  = 3,
            LEFT  = 4
        }; 

        static constexpr direction cw(direction dir)  {
            return static_cast<direction>(1 + (dir % 4));
        } 

        static constexpr direction ccw(direction dir) {
            return static_cast<direction>(1 + (5 + (dir - 2)) % 4);
        }

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