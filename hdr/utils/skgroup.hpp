#pragma once



#include "utils/group.hpp"


template <typename T>
class SkGroup: public Group<T> { 
protected:
    // 继承基类的所有保护成员
    using Group<T>::the;
    using Group<T>::defast;
    using Group<T>::fast;
    using Group<T>::free;
    using Group<T>::_size;
    using Group<T>::registerItem;
    using Group<T>::unregisterItem;

public:
    T pick() const {
        assert(!_size && "尝试获取空集合的元素");
        // 从末尾向前查找第一个不在free中的索引
        long long index = the.size() - 1;
        while (index >= 0) {
            if (free.find(index) == free.end()) {
                return the[index];
            }
            --index;
        }
        return T(); // 找不到有效元素时返回默认值
    }

    void push(T tar) {
        registerItem(tar.ID, the.size());
        the.push_back(tar);
    }
};
