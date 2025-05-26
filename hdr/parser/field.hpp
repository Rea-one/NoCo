#pragma once
#include <vector>
#include <string>
#include <memory>

#include "parser/ast.hpp"
#include "utils/skgroup.hpp"

using normal = Expression*; 
static long long FieldID = 0;
class Field {
protected:
    std::string ID = std::to_string(FieldID++);

    Group<Field*> subfields{};
public:
    normal base{};
    normal root{};
    Group<normal> targets{};
    SkGroup<normal> dangle{};
    void NewSubField();
    Field* toNewSub();
    Field* toRoot();
    
// public:
//     normal& operator[](long long index);
//     normal& operator[](std::string ID);
//     const normal& operator[](long long index) const;
//     const normal& operator[](std::string ID) const;
};