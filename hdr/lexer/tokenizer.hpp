#include <vector>
#include <string>

#include "utils/token_gen.hpp"

struct TokenUnit {
    std::string token;
    tokenTypes tag;
};

class Token {
protected:
    std::vector<TokenUnit> tokens{};
    int cursor = 0;
    
public:
    bool empty();
    
public:
    void put(TokenUnit& token);
    TokenUnit get();
    TokenUnit take();
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