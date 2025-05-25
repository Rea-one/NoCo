#pragma once
#include <vector>
#include <string>
#include <memory>

#include "utils/group.hpp"
#include "parser/tokenizer.hpp"

class Expression {
public:
    long long ID;
    virtual void action();
};

class PRJ_AST: public Expression {
public:
    Group<std::shared_ptr<Expression>> projext_streams{};
    Group<std::shared_ptr<Expression>> units{};

    void action();
};

class ValueExpression : public Expression {
public:
    std::string value{};
    std::string type{};

    virtual void action() override;
};

class BinoprExpression : public Expression {
public:
    std::string opr{};
    std::shared_ptr<Expression> left{};
    std::shared_ptr<Expression> right{};

    virtual void action() override;
};

class ConditionExpression : public Expression {
    std::shared_ptr<Expression> conditions;
    std::shared_ptr<Expression> actions;
    virtual void action() override;
};

class LoopExpression : public Expression {
    std::shared_ptr<Expression> condition{};
    std::shared_ptr<Expression> actions{};

    virtual void action() override;
};

class FunctionExpression : public Expression {
public:
    std::string name{};
    std::vector<std::shared_ptr<Expression>> args{};
    std::vector<std::shared_ptr<Expression>> actions{};
    // 返回值为实时生成的，这里用非指针表示
    std::vector<Expression> returns{};

    virtual void action() override;
};

class Parser { 
private:
    Group<std::shared_ptr<Expression>> memory;
public:
    static Parser& getInstance();
    
    std::shared_ptr<Expression> Ana(Token& tokens);
    std::shared_ptr<Expression> Ana_value(Token& tokens);
    std::shared_ptr<Expression> Ana_binopr(Token& tokens);
    std::shared_ptr<Expression> Ana_condition(Token& tokens);
    std::shared_ptr<Expression> Ana_loop(Token& tokens);
    std::shared_ptr<Expression> Ana_function(Token& tokens);
};