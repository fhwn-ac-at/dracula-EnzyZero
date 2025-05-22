#include "sink.h"

namespace ui {

auto sink_st::level_what_(const spdlog::level::level_enum level) -> std::pair<std::string_view, colors::color> {

    using namespace spdlog::level;
    using namespace colors;

    switch (level)
    {
        case spdlog::level::trace:    return {"[TRACE]", CYAN_BLACK}; 
        case debug:                   return {"[DEBUG]", MAGENTA_BLACK};
        case info:                    return {"[INFO]",  GREEN_BLACK};
        case warn:                    return {"[WARN]",  YELLOW_BLACK};
        case err:                     return {"[ERROR]", RED_BLACK};
        case critical:                return {"[CRIT]",  WHITE_RED};
        case off:                     return {"[OFF]",   BLUE_BLACK};
        default:                      return {"[IDK]",   WHITE_BLACK};
    }

    std::unreachable();
}

void ui::sink_st::sink_it_(const spdlog::details::log_msg& msg) {

    auto [name, color] = level_what_(msg.level);

    // colour the level
    window_.set_textcolor(color); 
    window_.sprint(name);
    window_.rem_textcolor(color);

    // print payload
    if (size_t size = window_.width - name.length(); msg.payload.size() > size)
        window_.sprint( std::string_view(msg.payload.data(), size) );
    else
        window_.sprint(msg.payload.data());

    window_.refresh();
}

} // ui namespace