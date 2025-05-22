#ifndef sink_h
#define sink_h

#include <spdlog/sinks/base_sink.h> 
#include <spdlog/details/null_mutex.h>

#include "windows.h"
#include "colors.h"

namespace ui {

class sink_st : public spdlog::sinks::base_sink<spdlog::details::null_mutex>  {
public:

    sink_st(window_base& window) 
    :   window_( window )
    {}

protected:

    void sink_it_(const spdlog::details::log_msg& msg) override;

    void flush_() override { window_.refresh(); }

private: 

    window_base& window_;

    static auto level_what_(const spdlog::level::level_enum level) -> std::pair<std::string_view, colors::color>;
}; 

} // ui namespace

#endif