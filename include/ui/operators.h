#ifndef operators_h 
#define operators_h

#include "operator_base.h"

namespace ui {

class GridOperator : public OperatorBase {
public:

    using OperatorBase::OperatorBase;

    void render(Interpreter& interpreter) override;

    ~GridOperator() override = default;
}; 

class StackOperator : public OperatorBase {
public:  

    using OperatorBase::OperatorBase;

    void render(Interpreter& interpreter) override;

    ~StackOperator() override = default;
};  

class CursorOperator : public OperatorBase {
public:  
  
    using OperatorBase::OperatorBase;

    void render(Interpreter& interpreter) override;

    ~CursorOperator() override = default;
};

} // ui namespace

#endif