#ifndef cursor_h
#define cursor_h  

#include <stdint.h>

struct Cursor {  

    /// @warning ORDER MATTERS!
    enum Direction : uint8_t {
        NONE  = 0,
        UP    = 1,
        RIGHT = 2,
        DOWN  = 3,
        LEFT  = 4
    }; 

    int y{};
    int x{};
    Direction dir{NONE};
     
    static constexpr Direction cw(Direction dir)  { return static_cast<Direction>(1 + (dir % 4)); } 
    static constexpr Direction ccw(Direction dir) { return static_cast<Direction>(1 + (5 + (dir - 2)) % 4); }
};


#endif