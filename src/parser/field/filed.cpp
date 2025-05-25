#pragma once

#include "parser/ast.hpp"
#include "parser/field.hpp"

using normal = std::shared_ptr<Expression>;


void Field::put(normal& target) {
    if (targets.freeSize() > 0) {
        
    } else {
        dangle = targets.size();
    }
    targets.put(target);
}

bool Field::submit(normal& target) {
    if (!targets.submit(target) && targets.freeSize() == 0) {
        dangle = targets.size();
        return true;
    }
    return false;
}

normal Field::get(long long index) {
    if (index < targets.size()) {
        return targets.get(index);
    }
    return targets.get(dangle);
}

normal Field::get(std::string ID) {
    return targets.get(dangle);
}

normal Field::take(long long index) {
    if (index < targets.size()) {
        return targets.take(index);
    }
    return  targets.take(dangle);
}

normal Field::take(std::string ID) {
    return targets.take(dangle);
}

void Field::push(normal& target) {
    targets.push(target);
}

normal Field::pick() {
    return targets.pick();
}