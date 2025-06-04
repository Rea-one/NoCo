#pragma once
#include <vector>
#include <string>
#include <unordered_map>


enum class abstractType {
        // 0级类型
        Inside,
        // 1级类型
        Declare,
        Define,
        Call,
        // 2级类型
        Map,        // ()
        Pack,       // []
        Explain,    // {}
        Fit,        // <>
        // 3级类型
        Plain,      // 等价于Explain 作为默认
        Graph,
        Node,
        // 4级类型
        Valuer,
        Pointer,
        Refencer,
        // 5级类型
        Binopr,
        Judger,
        Guider,
        // 6级类型
        Fixer,
};


enum class tokenTypes {
    Intager,
    Float,
    String,
    Boolean,
    Binary,

    TrueBranch,
    FalseBranch,


    Module,
    Class,
    Tag,
    Pure,
    In,
    Out,
    Born,
    Drop,
    Have,
    Match,
    Case,
};

static std::unordered_map<tokenTypes, abstractType> abstract = {
    {tokenTypes::Intager, abstractType::Explain},
    {tokenTypes::Float, abstractType::Explain},
    {tokenTypes::String, abstractType::Explain},
    {tokenTypes::Boolean, abstractType::Explain},
    {tokenTypes::Binary, abstractType::Explain},
    {tokenTypes::TrueBranch, abstractType::Guider},
    {tokenTypes::FalseBranch, abstractType::Guider},
};

static std::unordered_map<std::string, tokenTypes> literalRegexMap = {

};
static std::unordered_map<std::string, tokenTypes> typeAction = {

};

std::string GetType(char alpha);

tokenTypes TokenType(std::string token);