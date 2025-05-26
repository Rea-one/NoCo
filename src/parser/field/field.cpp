#pragma once

#include "parser/ast.hpp"
#include "parser/field.hpp"

using normal = Expression*;

void Field::NewSubField() {
    subfields.push(new Field);
}

Field* Field::toNewSub() {
    NewSubField();
    return subfields.pick();
}

Field* Field::toRoot() {
    return root;
}