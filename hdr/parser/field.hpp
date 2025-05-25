#pragma once
#include <vector>
#include <string>
#include <memory>

#include "ast.hpp"
#include "parser/ast.hpp"
#include "utils/group.hpp"

using normal = std::shared_ptr<Expression>; 
class Field {
protected:
    normal base{};
    normal root{};
    Group<normal> targets{};
    long long dangle{};
    std::vector<std::shared_ptr<Field>> subfields{};
public:
    void put(normal& target);
    bool submit(normal& target);
    normal get(std::string ID);
    normal get(long long index);
    normal take(std::string ID);
    normal take(long long index);
    void push(normal& target);
    normal pick();
    
public:
    normal& operator[](long long index);
    normal& operator[](std::string ID);
    const normal& operator[](long long index) const;
    const normal& operator[](std::string ID) const;
};