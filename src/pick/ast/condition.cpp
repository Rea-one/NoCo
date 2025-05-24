#include "pick/ast.hpp"

void ConditionExpression::action()
{
    std::shared_ptr<Expression> condition = conditions;
    std::shared_ptr<Expression> action = actions;

    while (condition->type == "binopr")
    {
        std::shared_ptr<BinoprExpression> binopr = std::dynamic_pointer_cast<BinoprExpression>(condition);
        std::shared_ptr<ValueExpression> left = std::dynamic_pointer_cast<ValueExpression>(binopr->left);
    }
}