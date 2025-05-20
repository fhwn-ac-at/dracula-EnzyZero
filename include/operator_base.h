#ifndef operator_base_h
#define operator_base_h

#include <memory>
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
 
    virtual void render(std::weak_ptr<window> window) = 0;

    virtual ~operator_base() = default;

protected:
    window& winref_;
};

} // ui namespace

#endif