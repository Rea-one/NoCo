#include "lexer/tokenizer.hpp"
#include "parser/ast.hpp"


void Tokenizer::read(std::string words) { 
    std::string now = "";
    bool inComment = false;  // 注释状态跟踪

    for (size_t order = 0; order < words.size(); order ++) {
        auto& elem = words[order];
        
        // 更新行号和列号
        if (elem == '\n') {
            row ++;
            column = 0;
        } else {
            column ++;
        }
        
        if (inComment) {
            // 结束注释状态
            if (inComment && (elem == '\n' || (elem == '*' && order + 1 < words.size() && words[order+1] == '/'))) {
                inComment = false;
                ++order;  // 跳过'\n'或'/'
                
            }
            continue;
        } else {
            // 优先处理注释
            if (elem == '/' && order + 1 < words.size() &&
                words[order+1] == '/') {
                if (!now.empty()) {
                    submit(now);
                    now.clear();
                }
                inComment = true;
                order ++;  // 跳过'/'
                continue;
            }
            
            // 多行注释支持
            if (elem == '/' && order + 1 < words.size() && words[order+1] == '*') {
                if (!now.empty()) {
                    submit(now);
                    now.clear();
                }
                inComment = true;
                order += 2;  // 跳过'/*'
                continue;
            }
            // 空格处理优化
            if (isspace(elem)) {
                if (!now.empty()) {
                    submit(now);
                    now.clear();
                }
                continue;
            }

            // 类型跳变检测增强
            std::string currentType = GetType(elem);
            if (!now.empty() && !isSameType(currentType, GetType(words[order+1]))) {
                now += elem;
                submit(now);
                now.clear();
                continue;
            }
            
            now += elem;
        }

        
    }
    
    // 清理残留token
    if (!now.empty()) {
        submit(now);
    }
}

void Tokenizer::submit(std::string& token) {
    TokenUnit unit;
    unit.token = token;
    unit.type = TokenType(token);
    unit.pos.row = row;
    unit.pos.column = column;
    tokens.push_back(unit);
}


// 新增类型比较函数
bool Tokenizer::isSameType(const std::string& type1, const std::string& type2) {
    // 特殊处理：操作符应视为相同类型以支持多字符符号
    if (type1 == "operator" && type2 == "operator") return true;
    return type1 == type2;
}

std::vector<TokenUnit> Tokenizer::get() {
    return tokens;
}

TokenUnit Token::get() {
    if (tokens.atEnd()) return {"", tokenTypes::Unknown};
    auto result = tokens.get();
    return std::move(result);
}

TokenUnit Token::getNext() {
    if (tokens.offset(1)) return {"", tokenTypes::Unknown};
    auto result = tokens.getOff(1);
    return std::move(result);
}

TokenUnit Token::take() {
    if (tokens.atEnd()) return {"", tokenTypes::Unknown};
    return tokens.take();
}

std::string Token::getStr() {
    return tokens.get().token;
}

std::string Token::getNextStr() {
    if (tokens.offset(1)) return "";
    return tokens.getOff(1).token;
}