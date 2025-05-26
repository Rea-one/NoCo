#include "parser/ast.hpp"
#include "utils/token_gen.hpp"
#include <memory>

Parser& Parser::getInstance() {
    static Parser instance;
    return instance;
}

using ty = tokenTypes;
std::unique_ptr<Expression> Parser::Ana(Token& tokens) {
    std::unique_ptr<Node> result{};
    std::unique_ptr<Expression> rcv{};
    while (!tokens.empty()) {
        auto token = tokens.get();
        switch (token.tag) {
            case ty::Value:
                rcv = Ana_value(tokens);
                result->unit.submit(rcv);
                break;
            case ty::Binopr:
                rcv = Ana_binopr(tokens);
                result->unit.submit(rcv);
                break;
            case ty::Condition:
                rcv = Ana_condition(tokens);
                result->unit.submit(rcv);
                break;
                break;
            case ty::Node:
                rcv = Ana_node(tokens);
                result->unit.submit(rcv);
                break;
            case ty::SubField:
                memory = memory->toNewSub();
                break;
            case ty::RootField:
                if (memory == memory->base)
                    break;
                memory = memory->toRoot();
                break;
            case ty::In:
                
            case ty::Unknown:
                rcv = Ana_binopr(tokens);
                result->unit.submit(rcv);
                break;
            default:
                break;
        }
        if (memory == memory->base)
                    break;
    }
}


std::unique_ptr<Expression> Parser::Ana_value(Token& tokens) {
    std::unique_ptr<Value> result = std::make_unique<Value>();
    result->type = tokens.take();
    result->name = tokens.take();
    if (tokens.pick() == "=") {
        tokens.take();
        result->value = Ana(tokens);
    }
    memory->targets.submit(result);
    return result;
}

// 目前这里实现起来有点混乱
std::unique_ptr<Expression> Parser::Ana_binopr(Token& tokens) {
    std::unique_ptr<Binopr> result = std::make_unique<Binopr>();
    result->opr = tokens.take();
    result->left = memory->targets.take();
    result->right = Ana(tokens);
    return result;
}

std::unique_ptr<Expression> Parser::Ana_condition(Token& tokens) {
    std::unique_ptr<Condition> result = std::make_unique<Condition>();
    if (tokens.pick() == "if") {
        result->name.token = "if";
        result->conditions = Ana_binopr(tokens);
        if (tokens.pick() == "+>") {
            result->piBranch = Ana(tokens);
        } else if (tokens.pick() == "->") {
            result->niBranch = Ana(tokens);
        }
        if (tokens.pick() == "+>") {
            result->piBranch = Ana(tokens);
        } else if (tokens.pick() == "->") {
            result->niBranch = Ana(tokens);
        }
    }
    return result;
}

std::unique_ptr<Expression> Parser::Ana_graph(Token& tokens) {
    
}


std::unique_ptr<Expression> Parser::Ana_node(Token& tokens) {
    if (tokens.pick() == "node") {
        tokens.take();
    }
    std::unique_ptr<Node> result = std::make_unique<Node>();
    result->name = tokens.take();
    memory->dangle.submit(result);
    Ana(tokens);
    return result;
}

Group<std::unique_ptr<Expression>> Parser::scanBunch(Token& tokens, std::string end) { 
    Group<std::unique_ptr<Expression>> result{};
    std::unique_ptr<Expression> rcv{};
    while (tokens.pick() != end) {
        rcv = Ana(tokens);
        result.submit(rcv);
    }
    tokens.take();
    return result;
}
