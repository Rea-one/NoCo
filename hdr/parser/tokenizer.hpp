#include <vector>
#include <string>

#include "utils/token_gen.hpp"


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
    bool empty();

public:
    std::string get();
    std::string take();
};