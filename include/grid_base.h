#include <array>

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

    virtual char& s_atcur() { return grid_.at(cursor.y).at(cursor.x); }
    virtual char& atcur() noexcept { return grid_[cursor.y][cursor.x]; }

    virtual ~grid_base() = default;

protected:

    // matrix with height=42 and width=69, nice
    std::array<std::array<char, 69>, 42> grid_{};

};