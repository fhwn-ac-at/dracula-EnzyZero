#ifndef ui_h
#define ui_h

#include <string>
#include <string_view>
#include <map>

#include <spdlog/sinks/base_sink.h>
#include <spdlog/details/null_mutex.h>
#include <spdlog/common.h>

#include <ncurses.h>

namespace ui {


class window_base {
public:

    /**
     * @brief Construct a new window base object
     * @param win window handle
     */
    window_base(WINDOW* win);

    /**
     * @brief print to a window
     * 
     * Strings that are too long will not be cut off and will instead wrap around
     * 
     * @tparam Args 
     * @param format fmt format like in fmt::print
     * @param args any args the format takes
     */
    template <typename... Args>
    void print(const std::string_view format, Args&&... args);

    /**
     * @brief print to a window without wrapping
     * 
     * The s stands for safe.
     * This printing function will print to the window and cut off strings that are too long.
     * 
     * @tparam Args 
     * @param format fmt format like in fmt::print
     * @param args any args the format takes
     */
    template <typename... Args>
    void sprint(const std::string_view format, Args&&... args);

    /**
     * @brief refresh and load any changes in memory
     */
    void refresh() { wrefresh(window_); }

    virtual ~window_base() = default;

private:
    const int width_; // width is saved for sprint
    WINDOW* window_;
};

/**
 * Concept for classes derived from window_base
 */
template <typename T>
concept DerivedWindow = std::is_base_of_v<window_base, T>;

/**
 * @brief custom sink for spdlog, singe threaded (st)
 */
class sink_st : public spdlog::sinks::base_sink<spdlog::details::null_mutex>  {
public:

    /**
     * @brief Construct a new sink st object with a window handle
     * @param win window handle
     */
    sink_st(WINDOW* win);

protected:

    /**
     * @brief overload, this will print to the window directly with a coloured level
     * 
     * @param msg spdlog internal buffer
     */
    void sink_it_(const spdlog::details::log_msg& msg) override;

    /**
     * @brief overload, refreshes window
     * used by spdlog internally
     */
    void flush_() override { wrefresh(window_); }

private: 

    const int width_;
    WINDOW* window_;

    /**
     * Used internally to return the level and id of the color_pair 
     * Color_pairs are defined in the source file of the global_state_ constructor
     */
    static constexpr auto level_what_(const spdlog::level::level_enum level) -> std::pair<std::string_view, int> {

        using namespace spdlog::level;

        switch (level)
        {
            case spdlog::level::trace:    return {"[TRACE]", 1};
            case debug:                   return {"[DEBUG]", 2};
            case info:                    return {"[INFO]",  3};
            case warn:                    return {"[WARN]",  4};
            case err:                     return {"[ERROR]", 5};
            case critical:                return {"[CRIT]",  6};
            case off:                     return {"[OFF]",   7};
            default:                      return {"[IDK]",   8};
        }

        std::unreachable();
    }
}; 

class ncurse  {
public:

    ncurse() = default;

    /**
     * @brief add a window to ncurses
     * 
     * As a map is used internally, this may throw an exception if a duplicate value etc.
     * is inserted.
     * 
     * @param name name of what to call the window
     * @param height 
     * @param width 
     * @param start_y 
     * @param start_x 
     */
    void add_win(const std::string name, int height, int width, int start_y, int start_x);

    /**
     * @brief returns a shared_ptr to a custom sink obj linked to the window specified by name
     * 
     * @param name name of the window
     * @return std::shared_ptr<sink_st> the sink created
     */
    auto sink_for_win(const std::string name) -> std::shared_ptr<sink_st>;

    /**
     * @brief returns a base_ptr to a derived window_base obj holding a handle to a window
     * 
     * @tparam T derived of the window
     * @param name name of the window 
     * @return std::unique_ptr<window_base> unique_ptr to the base
     */
    template <DerivedWindow T>
    auto base_for_win(const std::string name) -> std::unique_ptr<window_base>;

    /**
     * @brief delete a window by its name
     * 
     * May throw an exception if name is a window that does not exist
     * 
     * @param name name of the window
     */
    void del_win(const std::string name);
 
    /**
     * @brief Get the lines and colums of the stdscr screen
     * 
     * @return std::pair<int, int> lines, colums
     */
    auto get_dimensions() const noexcept -> std::pair<int, int> { return {LINES, COLS}; }

    // destroys all windows in the map
    ~ncurse();

private:
    std::map<std::string, WINDOW*> windows_;

    struct global_state_ {
        global_state_();  // calls ncurses initscr(), makes colour pairs etc.
        ~global_state_(); // calls ncurses endwin()
    };

    static global_state_ global_automatic_;
};

} // ncurses namespace 


template <typename... Args>
void ui::window_base::print(const std::string_view format, Args&&... args) {
        
    std::string msg = fmt::format(format, std::forward<Args>(args)... ); 
    waddstr(window_, msg.c_str());
}

template <typename... Args>
void ui::window_base::sprint(const std::string_view format, Args&&... args) {
        
    std::string msg = fmt::format(format, std::forward<Args>(args)... ); 
    waddnstr(window_, msg.c_str(), width_); // cut off long outputs
} 

template <ui::DerivedWindow T>
auto ui::ncurse::base_for_win(const std::string name) -> std::unique_ptr<window_base> {
    return std::make_unique<T>( windows_.at(name) );
}

#endif