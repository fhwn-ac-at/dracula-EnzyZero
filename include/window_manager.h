#ifndef window_manager_h
#define window_manager_h

#include <unordered_map> 
#include <vector>
#include <expected>
#include <memory> 
#include <utility>

#include "global_ncurses.h"
#include "windows.h"
#include "operator_base.h"

namespace ui {

class window_manager {
public:

    window_manager() = default;

    enum error : int { 
        ok,
        creation_failed,
        removing_failed,
        not_found
    };

    [[nodiscard]] auto create_window(window&& other) -> std::expected<int, error>; 

    [[nodiscard]] auto create_window(int height, int width, int startx, int starty) -> std::expected<int, error>; 

    error remove_window(int id); 

    template <DerivedOperator Op, typename... Args>
    [[nodiscard]] auto create_operator(Args&& ...args) -> std::expected<int, error>;
   
    error remove_operator(int id);

    error pair_window_operator(int window_id, int operator_id);

    void render();

    ~window_manager() = default;
 
private:
    unsigned id_generator_{1};
    std::unordered_map<int, std::unique_ptr<window>> windows_;
    std::unordered_map<int, std::unique_ptr<operator_base>> operators_;
    std::vector<std::pair<int, int>> window_operator_pairs_;
};

} // ui namespace

#endif