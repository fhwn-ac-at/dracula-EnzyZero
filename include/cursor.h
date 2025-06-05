#ifndef cursor_h
#define cursor_h  

#include <format>
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
      
    /**  
     * @brief get a clockwise or counter-clockwise rotation of a direction
     */ 
    static constexpr Direction cw(Direction dir)  { return static_cast<Direction>(1 + (dir % 4)); } 
    static constexpr Direction ccw(Direction dir) { return static_cast<Direction>(1 + (dir + 2) % 4); } 

    static constexpr const char* dir_tostr(Direction dir) {

        switch (dir)
        {
            case NONE:  return "none"; 
            case UP:    return "up";
            case RIGHT: return "right";
            case DOWN:  return "down";
            case LEFT:  return "left"; 
            default:    return "???";
        }  

        std::unreachable();
    } 
}; 


// custom printing format for cursor  
template <>
struct std::formatter<Cursor>
{
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }  
 
    auto format(const Cursor& cur, std::format_context& ctx) const { 

        // print with paddings
        return std::format_to(ctx.out(), "dir: {:<5} y: {:<2} x: {:<2}", Cursor::dir_tostr(cur.dir), cur.y, cur.x);
    }
};

#endif