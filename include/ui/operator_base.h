#ifndef operator_base_h
#define operator_base_h

#include <memory>
#include <spdlog/logger.h>
#include "window_base.h"  
#include "interpreter.h"

namespace ui {

class operator_base {
public:

    operator_base(
        window_base& window,
        std::shared_ptr<spdlog::logger>& logger
    )
    :   window_( window ),
        logger_( logger )
    {}

    virtual void render(Interpreter& interpreter) = 0;

    virtual ~operator_base() = default;

protected:
    window_base& window_;
    std::shared_ptr<spdlog::logger> logger_;
};

// concept for checking derivatives
template <typename T>
concept DerivedOperator = std::is_base_of_v<operator_base, T>;

} // ui namespace

#endif