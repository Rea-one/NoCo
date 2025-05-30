#include "parser/ast.hpp"
#include "utils/token_gen.hpp"
#include <memory>

using pe = std::unique_ptr<Expression>;

Parser& Parser::getInstance() {
    static Parser instance;
    return instance;
}

using ty = tokenTypes;
pe Parser::Ana(Token& tokens) {
    std::unique_ptr<Node> result{};
    pe rcv{};
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
                rcv = Ana_if(tokens);
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


pe Parser::Ana_value(Token& tokens) {
    std::unique_ptr<Value> result = std::make_unique<Value>();
    result->type = tokens.take();
    result->name = tokens.take();
    if (tokens.pick() == "=") {
        tokens.take();
    }
    memory->targets.submit(result);
    return result;
}

// 目前这里实现起来有点混乱
pe Parser::Ana_binopr(Token& tokens) {
    std::unique_ptr<Binopr> result = std::make_unique<Binopr>();
    result->opr = tokens.take();
    result->left = memory->targets.take();
    memory->targets.submit(result);
    return result;
}

pe Parser::Ana_if(Token& tokens) {
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

pe Parser::Ana_graph(Token& tokens) {
    
}


pe Parser::Ana_node(Token& tokens) {
    if (tokens.pick() == "node") {
        tokens.take();
    }
    std::unique_ptr<Node> result = std::make_unique<Node>();
    result->name = tokens.take();
    memory->dangle.submit(result);
    Ana(tokens);
    return result;
}

Group<pe> Parser::scanBunch(Token& tokens, std::string end) { 
    Group<pe> result{};
    pe rcv{};
    while (tokens.pick() != end) {
        rcv = Ana(tokens);
        result.submit(rcv);
    }
    tokens.take();
    return result;
}

pe Parser::Ana_paren(Token& tokens) {
    tokens.pick();
    while (tokens.pick() != ")") {
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
                rcv = Ana_if(tokens);
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
    }
}

pe Parser::Ana_square(Token& tokens) {
}

pe Parser::Ana_curl(Token& tokens) {
}


pe Parser::Ana_field(Token& tokens) {
    std::unique_ptr<Node> result = std::make_unique<Node>();
    memory->targets.submit(result);
    pe rcv;
    while (tokens.pick() != "}") {
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
                rcv = Ana_if(tokens);
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
    }
    return result;
}