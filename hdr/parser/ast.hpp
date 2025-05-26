#pragma once
#include <vector>
#include <string>
#include <memory>

#include "utils/group.hpp"
#include "parser/field.hpp"
#include "lexer/tokenizer.hpp"

static long long ExpressionID = 0;

class Expression {
public:
    std::string ID = std::to_string(ExpressionID++);
    TokenUnit name;
    virtual void act();
};

class Node : public Expression {
public:
    Group<std::unique_ptr<Expression>> in{};
    Group<std::unique_ptr<Expression>> out{};
    Group<std::unique_ptr<Expression>> unit{};
    Group<std::unique_ptr<Expression>> stream{}; 

    void act();
};

class Value : public Expression {
public:
    std::unique_ptr<Expression> value{};
    TokenUnit type{};

    virtual void act() override;
};

class Binopr : public Expression {
public:
    TokenUnit opr{};
    std::unique_ptr<Expression> left{};
    std::unique_ptr<Expression> right{};

    virtual void act() override;
};

class Condition : public Expression {
public:
    std::unique_ptr<Expression> conditions{};
    std::unique_ptr<Expression> piBranch{};
    std::unique_ptr<Expression> niBranch{};
    virtual void act() override;
};



class Parser { 
protected:
    Field* memory = new Field();
public:
    static Parser& getInstance();
    
    std::unique_ptr<Expression> Ana(Token& tokens);
    std::unique_ptr<Expression> Ana_value(Token& tokens);
    std::unique_ptr<Expression> Ana_binopr(Token& tokens);
    std::unique_ptr<Expression> Ana_condition(Token& tokens);
    std::unique_ptr<Expression> Ana_node(Token& tokens);
    std::unique_ptr<Expression> Ana_graph(Token& tokens);
    std::unique_ptr<Expression> Ana_call(Token& tokens);
public:
    Group<std::unique_ptr<Expression>> scanBunch(Token& tokens, std::string end);
};