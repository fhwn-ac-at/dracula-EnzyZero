#ifndef operators_h 
#define operators_h

#include "operator_base.h"

namespace ui {

class grid_operator final : public operator_base {
public:

    using operator_base::operator_base;

    void render(Interpreter& interpreter) override;

    ~grid_operator() override = default;
};

} // ui namespace

#endif