#include <array>
#include <vector>
#include <string>

#include "parser/ast.hpp"
#include "utils/token_gen.hpp"
#include "utils/cursor.hpp"

struct TokenUnit {
    std::string token;
    tokenTypes type;
    struct Position {
        int row = 0;
        int column = 0;
    } pos;
};

class Token {
protected:
    Cursor<TokenUnit> tokens{};    
public:    
public:
    void put(TokenUnit& token);
    TokenUnit get();
    TokenUnit take();
    TokenUnit getNext();

    std::string getStr();
    std::string getNextStr();
};

class Tokenizer {
protected:
    int row = 0;
    int column = 0;
public:
    std::vector<TokenUnit> tokens{};
    void read(std::string words);
    void submit(std::string& token);
    bool isSameType(const std::string& type1, const std::string& type2);
    
    std::vector<TokenUnit> get();
};