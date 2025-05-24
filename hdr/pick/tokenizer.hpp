#include <vector>
#include <string>

#include "util/token.hpp"


class Tokenizer {
public:
    Tokenizer();
    ~Tokenizer();

    std::vector<std::string> tokens{};
    void Read(std::string words);
};

class Token {
protected:
    std::vector<std::string> tokens{};

public:
    std::string consume();
};