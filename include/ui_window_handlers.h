
#include "grid.h"
#include "ui.h"

namespace ui {

class grid_window_handler : public ui::window_handler_base {

    grid_window_handler(
        WINDOW* win, 
        std::shared_ptr<spdlog::logger> logger,
        const grid& grid 
    );

    void update() override;

    ~grid_window_handler() = default;

private:
    const grid& grid_;
    std::shared_ptr<spdlog::logger> logger_;
    static constexpr int cursor_color_pair_num_ = 10; // TODO find a better solution
};


} // ui namespace