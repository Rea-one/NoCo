#include "utils/token_gen.hpp"



std::string GetType(char c) {
    // 数字字面量（包含十六进制、二进制前缀检测）
    if (isdigit(c)) {
        return "number";
    }
    
    // 字符串字面量起始符
    if (c == '"') {
        return "string";
    }

    // 特殊符号分类
    if (ispunct(c)) {
        return "punctuation";
    }

    // 标识符与关键字（字母、下划线）
    if (isalpha(c) || c == '_') {
        return "identifier";
    }

    // 不可识别字符
    return "unknown";
}
