#include <expected>
#include <string>
#include "window_manager.h"

namespace ui { 

using error = window_manager::error;

auto window_manager::create_window(int height, int width, int startx, int starty) -> std::expected<int, error> {

    auto res_pair = windows_.emplace( id_generator_++, std::make_unique<window>(height, width, starty, startx));
    if (!res_pair.second)
        return std::unexpected(creation_failed);

    return id_generator_;
}

auto window_manager::create_window(window&& other) -> std::expected<int, error> {

    auto res_pair = windows_.emplace( id_generator_++, std::make_unique<window>( std::move(other) ));
    if (!res_pair.second)
        return std::unexpected(creation_failed);

    return id_generator_;
} 

error window_manager::remove_window(int id) { 

    // remove all window_operator pairs with the window
    std::erase_if(window_operator_pairs_, [&id](const auto& pair) {
        return id == pair.first;
    }); 

    // remove from map 
    if (auto it = windows_.find(id); it != windows_.end())
    {
        windows_.erase( it );
        return ok;
    }
        
    return not_found;
}

template <DerivedOperator Op, typename... Args>
auto window_manager::create_operator(Args&& ...args) -> std::expected<int, error> {

    auto res_pair = operators_.emplace( id_generator_++, std::make_unique<window>( std::forward<Args>(args)... ));
    if (!res_pair.second) 
        return std::unexpected(creation_failed);

    return id_generator_;
}
    
error window_manager::remove_operator(int id) { 
        
    // remove all window_operator pairs with the operator
    std::erase_if(window_operator_pairs_, [&id](const auto& pair) {
        return id == pair.second;
    });

    // remove from map 
    if (auto it = operators_.find(id); it != operators_.end())
    {
        operators_.erase( it );
        return ok;
    }
        
    return not_found;
} 

error window_manager::pair_window_operator(int window_id, int operator_id) {
        
    auto win_it = windows_.find(window_id);
    auto op_it  = operators_.find(operator_id); 

    if (win_it == windows_.end() || op_it == operators_.end() ) 
        return not_found;

    // call startup method of operator here
    op_it->second->setup( *win_it->second );

    // register the pair
    if (auto res_pair = window_operator_pairs_.emplace_back(window_id, operator_id); 
        res_pair.second)
        return ok;
        
    return creation_failed;
}

void window_manager::render() { 

    // call render on all windows
    for (std::pair<int, int>& pair : window_operator_pairs_) 
    { 
        std::unique_ptr<operator_base>& op = operators_.at(pair.second); 
        op->render( *windows_.at(pair.first) );
    }
}

} // ui namespace 

