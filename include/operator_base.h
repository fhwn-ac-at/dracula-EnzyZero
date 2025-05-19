#ifndef operator_base_h
#define operator_base_h

#include "window.h"

namespace ui {

/**
 * Interface all operators must adhere to.
 * Operators take a ref to a window and use their methods to modify whats displayed.
 * The window manager calls render() on all registered operators. 
 */
class operator_base {
public:

    operator_base(window& win);
 
    virtual void render() = 0;

    virtual ~operator_base() = default;

protected:
    window& winref_;
};

} // ui namespace

#endif