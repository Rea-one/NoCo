#include "parser/ast.hpp"
#include "utils/token_gen.hpp"
#include <memory>

Parser& Parser::getInstance() {
    static Parser instance;
    return instance;
}

using ty = tokenTypes;
std::shared_ptr<Expression> Parser::Ana(Token& tokens) {
    std::shared_ptr<PRJ_AST> result{};
    std::shared_ptr<Expression> rcv{};
    while (!tokens.empty()) {
        std::string token = tokens.get();
        tokenTypes type = TokenType(token);
        switch (type) {
            case ty::Value:
                rcv = Ana_value(tokens);
                result->units.submit(rcv);
                break;
            case ty::Binopr:
                rcv = Ana_binopr(tokens);
                result->units.submit(rcv);
                break;
            case ty::Condition:
                rcv = Ana_binopr(tokens);
                result->units.submit(rcv);
                break;
            case ty::Loop:
                rcv = Ana_binopr(tokens);
                result->units.submit(rcv);
                break;
            case ty::Function:
                rcv = Ana_binopr(tokens);
                result->units.submit(rcv);
                break;
            case ty::Unknown:
                rcv = Ana_binopr(tokens);
                result->units.submit(rcv);
                break;
            default:
                break;
        }

    }
}

std::shared_ptr<Expression> Parser::Ana_value(Token& tokens) {
    std::shared_ptr<ValueExpression> result = std::make_shared<ValueExpression>();
    result->type = tokens.take();
    result->value = tokens.take();
    return result;
}

// 目前这里实现起来有点混乱
std::shared_ptr<Expression> Parser::Ana_binopr(Token& tokens) {
    std::shared_ptr<BinoprExpression> result = std::make_shared<BinoprExpression>();
    result->opr = tokens.take();
    result->left = memory.pick();
    auto rcv = Ana_value(tokens);
    result->right = rcv;
    return result;
}

std::shared_ptr<Expression> Parser::Ana_condition(Token& tokens) {
    // TODO
}

std::shared_ptr<Expression> Ana_loop(Token& tokens) {
    // TODO
}

std::shared_ptr<Expression> Parser::Ana_function(Token& tokens) {
    // TODO
}