#include "utils/token_gen.hpp"

static std::unordered_map<char, std::string> token_map = {
    {'+', "operator"},
        {'-', "operator"},
        {'*', "operator"},
        {'/', "operator"},
        {'(', "paren"},
        {')', "paren"},
        {'{', "brace"},
        {'}', "brace"},
        {',', "comma"},
        {';', "semi"},
        {'=', "equal"},
        {'"', "string"}
};

std::string GetType(char c) {
    if (token_map.find(c) != token_map.end()) {
        return token_map[c];
    } else {
        if (isdigit(c)) {
            return "number";
        } else if (isalpha(c)) {
            return "identifier";
        } else {
            return "unknown";
        }
    }
}

