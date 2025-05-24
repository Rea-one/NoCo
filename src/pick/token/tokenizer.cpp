#include "pick/tokenizer.hpp"


Tokenizer::Tokenizer() {

}

Tokenizer::~Tokenizer() {

}

void Tokenizer::Read(std::string words) { 
    std::string preType = "";
    std::string nowType = "";
    std::string now = "";

    for (auto elem: words) {
        if (elem == ' ') {
            if (now != "") {
                tokens.push_back(now);
                now = "";
            }
            continue;
        }
        nowType = GetType(elem);
        if (nowType != preType) {
            tokens.push_back(now);
            now = elem;
            preType = nowType;
        } else {
            now += elem;
        }
    }
}