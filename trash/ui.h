#ifndef ui_h
#define ui_h

#include <string>
#include <string_view>
#include <memory>
#include <utility>
#include <map>

#include <spdlog/logger.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/details/null_mutex.h>
#include <spdlog/common.h>

#include <ncurses.h>

namespace ui {

/**
 * A window is a window.
 * Apart from its dimensions, it owns an WINDOW* handle from ncurses.
 */
class window_base {
public:

    window_base(WINDOW* win)
    :   window_(win),
        height_( getmaxy(win) ),
        width_( getmaxy(win) ),
        starty_( getbegy(win) ),
        startx_( getbegx(win) )
    {}   

    window_base(
        WINDOW* win,
        int height,
        int width,
        int starty,
        int startx
    )
    :   window_(win),
        height_(height),
        width_(width),
        starty_(starty),
        startx_(startx)
    {}
    
    window_base(
        int height,
        int width,
        int starty = 0,
        int startx = 0
    )
    :   window_( newwin(height, width, starty, startx) ),
        height_(height),
        width_(width),
        starty_(starty),
        startx_(startx)
    {}

    WINDOW* window_;
    int height_;
    int width_;
    int starty_;
    int startx_;

    virtual ~window_base() = default; // leaving destruction to derivatives
};  

class window : public window_base { 

    window(
        int height,
        int width,
        int starty = 0,
        int startx = 0
    )
    :   window_base(height, width, starty, startx)
    {}

    window(window& other) = delete;
    window& operator=(window& other) = delete;

    // window owns its window and destroys it
    ~window() override { delwin(window_); }
};

class derived_window : public window_base {
    
    derived_window(
        WINDOW* win, 
        int height,
        int width,
        int starty,
        int startx
    )
    :   window_base( derwin(win, height, width, starty, startx) )
    {}

    ~derived_window() override = default; // derived windows do not own anything
};

class operator_base {
public:

    /**
     * @brief Construct a new window handler base object
     * @param win window handle
     */
    operator_base();
 
    /**
     * @brief function that will be called to update whats displayed on the screen
     * 
     * This function shall be implemented by all derived classes.
     * It will be called for all registered window handlers.
     */
    virtual void update() = 0;

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
     * This printing function will print to the window and cut off strings that are longe than width_.
     * 
     * @tparam Args 
     * @param format fmt format like in fmt::print
     * @param args any args the format takes
     */
    template <typename... Args>
    void sprint(const std::string_view format, Args&&... args);

    /**
     * @brief get the position of the cursor in the terminal
     * 
     * @return std::pair<int, int> height, then width
     */
    auto get_cursor() const noexcept -> std::pair<int, int>; 

    /**
     * @brief set the position of the cursor in the window
     * 
     * @param y height
     * @param x width
     */
    void set_cursor(int y, int x) noexcept { wmove(window_, y, x); }

    /**
     * @brief refresh and load any changes in memory
     */
    void refresh() { wrefresh(window_); }

    virtual ~window_handler_base() = default;

protected:
    const int height_;
    const int width_; 
    WINDOW* window_;
};

/**
 * Concept for classes derived from window_base
 */
template <typename T>
concept DerivedWindowHandler = std::is_base_of_v<window_handler_base, T>;

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
     * @brief Overload for window_section structs
     * 
     * @param name name of what to call the window
     * @param section window_section struct
     */
    void add_win(const std::string name, const window_section section) { 
        add_win(name, section.height, section.width, section.starty, section.startx); 
    }

    /**
     * @brief returns a shared_ptr to a custom sink obj linked to the window specified by name
     * 
     * @param name name of the window
     * @return std::shared_ptr<sink_st> the sink created
     */
    auto sink_for_window(const std::string name) -> std::shared_ptr<sink_st>;

    /**
     * @brief register a window handler for a window
     * 
     * @tparam T derived class of 
     * @tparam Args 
     * @param name 
     * @param args 
     */
    template <DerivedWindowHandler T, typename ...Args>
    void register_window_handler(const std::string name, Args ...args) { 
        window_handlers_.insert(name, std::make_unique<T>(windows_.at(name), std::forward<Args>(...args) ) ); 
    }  

    /**
     * @brief call the update method of all registered window handlers
     */
    void update() {
        for(auto& handler : window_handlers_)
            handler.second->update();
    }

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
    std::map<std::string, std::unique_ptr<window_handler_base>> window_handlers_;

    // TODO find better solution for colors
    struct global_state_ { 
        global_state_();  // calls ncurses initscr(), makes colour pairs etc.
        ~global_state_(); // calls ncurses endwin()
    };
 
    static global_state_ global_automatic_;
};


} // ui namespace 


template <typename... Args>
void ui::window_handler_base::print(const std::string_view format, Args&&... args) {
        
    std::string msg = fmt::format(format, std::forward<Args>(args)... ); 
    waddstr(window_, msg.c_str());
}

template <typename... Args>
void ui::window_handler_base::sprint(const std::string_view format, Args&&... args) {
        
    std::string msg = fmt::format(format, std::forward<Args>(args)... ); 
    waddnstr(window_, msg.c_str(), width_); // cut off long outputs
} 


#endif