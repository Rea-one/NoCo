#include "parser/ast.hpp"
#include "utils/token_gen.hpp"
#include <memory>

Parser& Parser::getInstance() {
    static Parser instance;
    return instance;
}

using ty = tokenTypes;
std::shared_ptr<Expression> Parser::Ana(Token& tokens) {
    std::shared_ptr<Action> result{};
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

std::shared_ptr<Expression> Parser::Ana_action(Token& tokens) {
    std::shared_ptr<Action> result = std::make_shared<Action>();
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
    std::shared_ptr<ConditionExpression> result = std::make_shared<ConditionExpression>();
    result->conditions = Ana_binopr(tokens);
    result->actions = Ana_action(tokens);
    return result;
}

std::shared_ptr<Expression> Parser::Ana_loop(Token& tokens) {
    std::shared_ptr<LoopExpression> result = std::make_shared<LoopExpression>();
    result->conditions = Ana_binopr(tokens);
    result->actions = Ana_action(tokens);
    return result;
}

std::shared_ptr<Expression> Parser::Ana_function(Token& tokens) {
    std::shared_ptr<FunctionExpression> result = std::make_shared<FunctionExpression>();
    result->name = tokens.take();
    result->args = scanBunch(tokens, ")");
    result->actions = scanBunch(tokens, "}");
    result->returns = Ana_value(tokens);
    return result;
}

Group<std::shared_ptr<Expression>> Parser::scanBunch(Token& tokens, std::string end) { 
    Group<std::shared_ptr<Expression>> result{};
    std::shared_ptr<Expression> rcv{};
    while (tokens.get() != end) {
        rcv = Ana(tokens);
        result.submit(rcv);
    }
    tokens.take();
    return result;
}
