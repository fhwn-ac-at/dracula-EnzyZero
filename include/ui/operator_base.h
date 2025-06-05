#ifndef operator_base_h
#define operator_base_h

#include <memory>
#include <spdlog/logger.h>
#include "window_base.h"  
#include "interpreter.h"

namespace ui {

class OperatorBase {
public:

    OperatorBase(
        window_base& window,
        std::shared_ptr<spdlog::logger>& logger
    )
    :   window_( window ),
        logger_( logger )
    {}
 
    /**
     * @brief Interface derivatives will override to render internals of an interpreter
     * 
     */
    virtual void render(Interpreter& interpreter) = 0;

    virtual ~OperatorBase() = default;

protected:
    window_base& window_;
    std::shared_ptr<spdlog::logger> logger_;
};

} // ui namespace

#endif