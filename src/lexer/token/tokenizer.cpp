#include "lexer/tokenizer.hpp"


void Tokenizer::read(std::string words) { 
    std::string now = "";
    bool inComment = false;  // 注释状态跟踪

    for (size_t i = 0; i < words.size(); ++i) {
        auto& elem = words[i];
        
        // 优先处理注释
        if (!inComment && elem == '/' && i + 1 < words.size() && words[i+1] == '/') {
            if (!now.empty()) {
                tokens.push_back(now);
                now.clear();
            }
            inComment = true;
            ++i;  // 跳过'/'
            continue;
        }
        
        // 多行注释支持
        if (!inComment && elem == '/' && i + 1 < words.size() && words[i+1] == '*') {
            if (!now.empty()) {
                tokens.push_back(now);
                now.clear();
            }
            inComment = true;
            i += 2;  // 跳过'/*'
            continue;
        }
        
        // 结束注释状态
        if (inComment && (elem == '\n' || (elem == '*' && i + 1 < words.size() && words[i+1] == '/'))) {
            inComment = false;
            ++i;  // 跳过'\n'或'/'
            continue;
        }
        
        // 跳过注释内容
        if (inComment) continue;
    
        
        // 空格处理优化
        if (isspace(elem)) {
            if (!now.empty()) {
                tokens.push_back(now);
                now.clear();
            }
            continue;
        }

        // 类型跳变检测增强
        std::string currentType = GetType(elem);
        if (!now.empty() && !isSameType(currentType, GetType(words[i+1]))) {
            now += elem;
            tokens.push_back(now);
            now.clear();
            continue;
        }
        
        now += elem;
    }
    
    // 清理残留token
    if (!now.empty()) {
        tokens.push_back(now);
    }
}

void Tokenizer::submit(std::string& token) {
    tag(token);
    tokens.push_back(token);
}

void Tokenizer::tag(std::string& token) {
    auto type = TokenType(token);
    tags.push_back(type);
}


// 新增类型比较函数
bool Tokenizer::isSameType(const std::string& type1, const std::string& type2) {
    // // 特殊处理：操作符应视为相同类型以支持多字符符号
    // if (type1 == "operator" && type2 == "operator") return true;
    return type1 == type2;
}

Token Tokenizer::trans() {
    Token result{};
    for (size_t i = 0; i < tokens.size(); ++i) {
        TokenUnit now = {tokens[i], tags[i]};
        result.put(now);
    }
    return result;
}

void Token::put(TokenUnit& tar) {
    tokens.push_back(tar);
}
TokenUnit Token::get() {
    if (empty()) return {"", tokenTypes::Unknown};
    auto& result = tokens[cursor];
    return result;
}

TokenUnit Token::take() {
    if (empty()) return {"", tokenTypes::Unknown};
    auto& result = tokens[cursor];
    ++cursor;
    return result;
}