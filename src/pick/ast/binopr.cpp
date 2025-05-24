#include "pick/ast.hpp"

void BinoprExpression::action()
{
    left->action();
    right->action();
}