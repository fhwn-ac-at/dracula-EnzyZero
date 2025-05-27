#include <algorithm>
#include "sink.h"

namespace ui {

auto sink_st::level_what_(const spdlog::level::level_enum level) -> std::pair<std::string_view, colors::color> {

    using namespace spdlog::level;
    using namespace colors;

    switch (level)
    {
        case spdlog::level::trace:    return {"[TRACE] ", CYAN_BLACK}; 
        case debug:                   return {"[DEBUG] ", MAGENTA_BLACK};
        case info:                    return {"[INFO] ",  GREEN_BLACK};
        case warn:                    return {"[WARN] ",  YELLOW_BLACK};
        case err:                     return {"[ERROR] ", RED_BLACK};
        case critical:                return {"[CRIT] ",  WHITE_RED};
        case off:                     return {"[OFF] ",   BLUE_BLACK};
        default:                      return {"[IDK] ",   WHITE_BLACK};
    }

    std::unreachable();
}

void ui::sink_st::sink_it_(const spdlog::details::log_msg& msg) {

    auto [name, color] = level_what_(msg.level);
    int used_width = window_.width;

    // colour the level
    window_.set_textcolor(color); 
    window_.print(name);
    used_width -= name.length();
    window_.rem_textcolor(color); 

    // print payload, trunc to window width
    for (char c : std::string_view(msg.payload.data(), std::min(msg.payload.size(), static_cast<size_t>(used_width - 1) )) ) 
        window_.putc(c);

    window_.putc('\n');

    window_.refresh();
}

} // ui namespace