#ifndef operator_base_h
#define operator_base_h

#include "windows.h"

namespace ui {

/**
 * Interface all operators must adhere to.
 * Operators take a ref to a window and use their methods to modify whats displayed.
 * The window manager calls render() on all registered operators. 
 */
class operator_base {
public:

    operator_base() = default;
 
    // this will be called when an operator is coupled to a window
    virtual void startup(window& win) = 0;

    // will becalled each time
    virtual void render(window& win) = 0;

    virtual ~operator_base() = default;
};

// concept for checking derivatives
template <typename T>
concept DerivedOperator = std::is_base_of_v<operator_base, T>;

} // ui namespace

#endif