#ifndef sink_h
#define sink_h

#include <spdlog/sinks/base_sink.h> 
#include <spdlog/details/null_mutex.h>

#include "windows.h"
#include "colors.h"

namespace ui {

/**
 * This is a custom sink for spdlog to log to a window.
 */
class sink_st : public spdlog::sinks::base_sink<spdlog::details::null_mutex>  {
public:

    sink_st(window_base& window) 
    :   window_( window )
    {}

protected:
 
    /**
     * @brief prints a msg to a window
     * 
     * Note that any formats are ignored, and the level is printed directly with the message behind it.
     * This is due to ncurses not providing ansi-escapes and I was... lazy.
     * 
     */
    void sink_it_(const spdlog::details::log_msg& msg) override;
 
    // just calls wreferes on the window
    void flush_() override { window_.refresh(); }

private: 

    window_base& window_;
 
    // gets the string and color enum for a level (look into colors.h for the enums)
    static auto level_what_(const spdlog::level::level_enum level) -> std::pair<std::string_view, colors::color>;
}; 

} // ui namespace

#endif