#include <vector>
#include <string>
#include <memory>

class Expression {
public:
    virtual void action();
};

class ValueExpression : public Expression {
public:
    std::string value{};
    std::string type{};

    virtual void action() override;
};

class BinoprExpression : public Expression {
public:
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
public:
    static std::shared_ptr<Expression> Ana(std::vector<std::string>& tokens);
    static std::shared_ptr<Expression> Ana_value(std::vector<std::string>& tokens);
    static std::shared_ptr<Expression> Ana_binopr(std::vector<std::string>& tokens);
    static std::shared_ptr<Expression> Ana_condition(std::vector<std::string>& tokens);
    static std::shared_ptr<Expression> Ana_loop(std::vector<std::string>& tokens);
    static std::shared_ptr<Expression> Ana_function(std::vector<std::string>& tokens);
};