#ifndef window_manager_h
#define window_manager_h

#include <unordered_map>
#include <string>
#include <string_view>
#include <memory> 
#include <utility>
#include <vector>

#include "windows.h"
#include "operator_base.h"

namespace ui {

class window_manager {
public:

    window_manager() = default;

    /**
     * @brief Create a window 
     * 
     * @param name name of the window
     * @param height 
     * @param width 
     * @param startx 
     * @param starty 
     * @return true if emplacement was possible
     * @return false if window could not be implaced
     */
    bool create_window(std::string name, int height, int width, int startx, int starty) {
        auto res = windows_.emplace( std::move(name), std::make_unique<window>(height, width, starty, startx));
        return res.second;
    }

    /**
     * @brief Overload, create a window object by another moved window
     * 
     * @param name name of the window
     * @param other 
     * @return true emplace successful
     * @return false emplace failed
     */
    bool create_window(std::string name, window&& other) {
        auto res = windows_.emplace( std::move(name), std::make_unique<window>(other));
        return res.second;
    }

    /**
     * @brief remove a window by its name
     * 
     * @param name name of the window
     * @return true window could be removed 
     * @return false window coudl not be removed/was not found
     */
    bool remove_window(std::string name) { 

        // remove all window_operator pairs with the window
        std::erase_if(window_operator_pairs_, [&name](const auto& pair) {
            return name == pair.first;
        }); 

        return windows_.erase(name); 
    }

    template <DerivedOperator Op, typename... Args>
    bool create_operator(std::string name, Args&& ...args) {
        auto res = operators_.emplace( std::move(name), std::make_unique<Op>( std::forward<Args>(args)... ));
        return res.second;
    }
    
    bool remove_operator(std::string name) { 
        
        // remove all window_operator pairs with the operator
        std::erase_if(window_operator_pairs_, [&name](const auto& pair) {
            return name == pair.second;
        });

        return operators_.erase(name); 
    }


    ~window_manager() = default;
 
private:
    std::unordered_map<std::string, std::unique_ptr<window>> windows_;
    std::unordered_map<std::string, std::unique_ptr<operator_base>> operators_;
    std::vector<std::pair<std::string_view, std::string_view>> window_operator_pairs_;
};


} // ui namespace

#endif