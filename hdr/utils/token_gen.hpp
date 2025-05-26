#pragma once
#include <vector>
#include <string>
#include <unordered_map>


enum class tokenTypes {
    Type,
    Value,
    Binopr,
    Condition,
    TrueBranch,
    FalseBranch,
    Graph,
    Node,
    SubField,
    RootField,
    In,
    Out,
    Module,
    Class,
    Born,
    Have,
    Drop,
    Match,
    Case,
    Parallel,
    WaitAll,
    Exception,
    Unknown,
    Arrow,     // 新增箭头类型
    Effect     // 新增副作用类型
};


static std::unordered_map<std::string, tokenTypes> literalRegexMap = {
    {"^-?[0-9]+$", tokenTypes::Value},          // 整数
    {"^-?[0-9]+\\.[0-9]+$", tokenTypes::Value}, // 浮点数
    {"^\".*\"$", tokenTypes::Value},            // 字符串
    {"^true$|^false$", tokenTypes::Value},      // 布尔值
    {"^0[xX][0-9a-fA-F]+$", tokenTypes::Value}, // 十六进制数
    {"^0[bB][01]+$", tokenTypes::Value},       // 二进制数
    {"^//.*$", tokenTypes::Unknown},            // 注释
    {"^\\s*$", tokenTypes::Unknown},           // 空白行
};
static std::unordered_map<std::string, tokenTypes> typeAction = {
    // 控制流与模式匹配
    {"if", tokenTypes::Condition},
    {"match", tokenTypes::Match},
    {"case", tokenTypes::Case},
    {"parallel", tokenTypes::Parallel},
    {"wait_all", tokenTypes::WaitAll},
    {"throw", tokenTypes::Exception},
    {"error", tokenTypes::Exception},
    {"->", tokenTypes::Arrow},     // 修正映射关系
    {"+>", tokenTypes::Effect},    // 新增映射关系
    // 运算符与通用类型
    {"operator", tokenTypes::Binopr},
    {"number", tokenTypes::Value},
    {"string", tokenTypes::Value},
    {"boolean", tokenTypes::Value},

    // 控制流与模式匹配
    {"if", tokenTypes::Condition},
    {"match", tokenTypes::Match},
    {"case", tokenTypes::Case},

    // 图与节点
    {"graph", tokenTypes::Graph},
    {"node", tokenTypes::Node},

    // 输入输出参数
    {"in", tokenTypes::In},
    {"out", tokenTypes::Out},

    // 类型系统与模块
    {"module", tokenTypes::Module},
    {"class", tokenTypes::Class},

    // 成员与生命周期
    {"have", tokenTypes::Have},
    {"born", tokenTypes::Born},
    {"drop", tokenTypes::Drop},

    // 子字段与根字段（保留兼容）
    {"sub field", tokenTypes::SubField},
    {"root field", tokenTypes::RootField},
};

std::string GetType(char alpha);

tokenTypes TokenType(std::string token);