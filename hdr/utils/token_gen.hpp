#pragma once
#include <vector>
#include <string>
#include <unordered_map>

enum class tokenTypes {
    Value,
    Binopr,
    Condition,
    Loop,
    Function,
    Unknown
};

std::string GetType(char alpha);

tokenTypes TokenType(std::string token);