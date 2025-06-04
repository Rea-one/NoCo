#include "lexer/token.hpp"
#include "parser/ast.hpp"

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


bool Token::atEnd() {
    return tokens.atEnd();
}


ll Token::move(ll walk) {
    return tokens.move(walk);
}

ll Token::Move(ll walk) {
    return tokens.Move(walk);
}

ll Token::prior() {
    return tokens.prior();
}

ll Token::Prior() {
    return tokens.Prior();
}

ll Token::next() {
    return tokens.next();
}

ll Token::Next() {
    return tokens.Next();
}