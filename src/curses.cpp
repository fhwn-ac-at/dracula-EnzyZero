#include <map>
#include <string>
#include <string_view>
#include <utility>
#include <memory>
#include <array>

#include <spdlog/sinks/base_sink.h>
#include <spdlog/details/null_mutex.h>
#include <spdlog/pattern_formatter.h>
#include <spdlog/formatter.h>

namespace ncurse {
#include <ncurses.h>
}

class Ncurses  {
public:

    /**
     * Custom sink for spdlog to write into specific window
     */
    class sink_st;

    Ncurses()
    {
        ncurse::initscr();
        ncurse::curs_set(0); 
        ncurse::start_color();
        ncurse::refresh(); // for some reason, not refreshing at start breaks stuff later :(
        // cbreak();
        // noecho()
        // keypad(stdscr, TRUE)
    }

    void add_win(const std::string name, int height, int width, int start_y, int start_x) { 

        using namespace ncurse;

        WINDOW* win = ncurse::newwin(height, width, start_y, start_x);
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

    auto sink_for_win(const std::string name) -> std::shared_ptr<sink_st> {

        return std::make_shared<sink_st>( windows_.at(name) );
    }

    void del_win(const std::string name)
    {
        ncurse::delwin(windows_.at(std::string(name)));
        windows_.erase(name);
    }

    auto get_dimensions() const noexcept -> std::pair<int, int> { return {ncurse::LINES, ncurse::COLS}; }

    ~Ncurses() { 

        // destroy all windows
        for (auto window : windows_)
            ncurse::delwin(window.second);

        ncurse::endwin();
    }

private:
    std::map<std::string, ncurse::WINDOW*> windows_;
};


class Ncurses::sink_st : public spdlog::sinks::base_sink<spdlog::details::null_mutex>  {
public:

    sink_st(ncurse::WINDOW* win)
    :   width_( getmaxx(win)-2 ),
        window_( ncurse::derwin(win, getmaxy(win) -2, width_ , 1, 1) )
    {
        // make window scrollable
        ncurse::scrollok(window_, true);

        // define colors for spdlog::levels enum
        ncurse::init_pair(1, COLOR_CYAN, COLOR_BLACK);    // trace
        ncurse::init_pair(2, COLOR_MAGENTA, COLOR_BLACK); // debug
        ncurse::init_pair(3, COLOR_GREEN, COLOR_BLACK);   // info
        ncurse::init_pair(4, COLOR_YELLOW, COLOR_BLACK);  // warn
        ncurse::init_pair(5, COLOR_RED, COLOR_BLACK);     // error
        ncurse::init_pair(6, COLOR_WHITE, COLOR_RED);     // critical
        ncurse::init_pair(7, COLOR_BLUE, COLOR_BLACK);    // off
        ncurse::init_pair(8, COLOR_WHITE, COLOR_BLACK);   // n_levels (idk)
    }

protected:

    void sink_it_(const spdlog::details::log_msg& msg) override {

        using namespace ncurse;

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

    void flush_() override { ncurse::wrefresh(window_); }

private: 

    const int width_;
    ncurse::WINDOW* window_;

    static constexpr auto level_what_(const spdlog::level::level_enum level) -> std::pair<std::string_view, int> {

        using namespace spdlog::level;

        switch (level)
        {
            case trace:    return {"[TRACE]", 1};
            case debug:    return {"[DEBUG]", 2};
            case info:     return {"[INFO]",  3};
            case warn:     return {"[WARN]",  4};
            case err:      return {"[ERROR]", 5};
            case critical: return {"[CRIT]",  6};
            case off:      return {"[OFF]",   7};
            default:       return {"[IDK]",   8};
        }

        std::unreachable();
    };
};
