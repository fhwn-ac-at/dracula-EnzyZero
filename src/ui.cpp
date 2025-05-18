#include <map>
#include <string>
#include <string_view>
#include <utility>
#include <memory>
#include <array>
#include <type_traits>

#include <spdlog/sinks/base_sink.h>
#include <spdlog/details/null_mutex.h>
#include <spdlog/pattern_formatter.h>
#include <spdlog/formatter.h>

#include "ui.h" 

namespace ui {

window_base::window_base(WINDOW* win)
:   width_( getmaxx(win)-2 ),
    window_( derwin(win, getmaxy(win) - 2, width_, 1, 1) )
{
    // make window scrollable
    scrollok(window_, true);
} 

sink_st::sink_st(WINDOW* win)
:   width_( getmaxx(win)-2 ),
    window_( derwin(win, getmaxy(win) -2, width_ , 1, 1) )
{
    // make window scrollable
    scrollok(window_, true);
}

void sink_st::sink_it_(const spdlog::details::log_msg& msg) {

    auto [lvl_name, lvl_id] = level_what_(msg.level);

    // colour the level
    wattron(window_, COLOR_PAIR( lvl_id ) );
    waddstr(window_, lvl_name.data() );
    wattroff(window_, COLOR_PAIR( lvl_id ));

    // print payload
    // waddnstr truncates strings that are too long
    waddnstr(window_, msg.payload.data(), width_ - lvl_name.length() - 1 );
    wprintw(window_, "\n");
    wrefresh(window_);
}

void ncurse::add_win(const std::string name, int height, int width, int start_y, int start_x) { 

    WINDOW* win = newwin(height, width, start_y, start_x);
    wborder(win, 
        ACS_VLINE, ACS_VLINE,     // Left, Right: vertical bars
        ACS_HLINE, ACS_HLINE,     // Top, Bottom: horizontal bars
        ACS_ULCORNER, ACS_URCORNER, // Top-left, Top-right
        ACS_LLCORNER, ACS_LRCORNER  // Bottom-left, Bottom-right
    );

    wrefresh(win);

    windows_.insert({
        name, 
        win
    });
}

auto ncurse::sink_for_win(const std::string name) -> std::shared_ptr<sink_st> {
    return std::make_shared<sink_st>( windows_.at(name) );
}

void ncurse::del_win(const std::string name)
{
    delwin(windows_.at(std::string(name)));
    windows_.erase(name);
}

ncurse::~ncurse() { 

    for (auto window : windows_)
        delwin(window.second);
}

ncurse::global_state_::global_state_() {

    initscr();
    curs_set(0); 
    refresh(); // for some reason, not refreshing at start breaks stuff later :(
    // cbreak();
    // noecho()
    // keypad(stdscr, TRUE)

    // define colors for spdlog::levels enum
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);    // trace
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK); // debug
    init_pair(3, COLOR_GREEN, COLOR_BLACK);   // info
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);  // warn
    init_pair(5, COLOR_RED, COLOR_BLACK);     // error
    init_pair(6, COLOR_WHITE, COLOR_RED);     // critical
    init_pair(7, COLOR_BLUE, COLOR_BLACK);    // off
    init_pair(8, COLOR_WHITE, COLOR_BLACK);   // n_levels (idk)
}

ncurse::global_state_::~global_state_() { endwin(); }

} // ui namespace