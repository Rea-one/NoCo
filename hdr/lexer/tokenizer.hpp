#include <cstdint>
#include <vector>
#include <string>

#include "utils/token_gen.hpp"

struct TokenUnit {
    std::string token;
    tokenTypes tag;
    struct Position {
        int line = 0;
        int column = 0;
        int offset = 0;
    } pos;
};

class Token {
protected:
    std::vector<TokenUnit> tokens{};
    int cursor = 0;
    
public:
    bool empty();
    int size();
    
public:
    void put(TokenUnit& token);
    TokenUnit get();
    TokenUnit take();
    TokenUnit getNext();
    std::string pick();
};


class Tokenizer {
public:

    std::vector<std::string> tokens{};
    std::vector<tokenTypes> tags{};
    void read(std::string words);
    void submit(std::string& token);
    void tag(std::string& token);
    bool isSameType(const std::string& type1, const std::string& type2);
    
    Token trans();
};