#pragma once

#include "utils/group.hpp"

template<typename T>
class SkGroup : public Group<T> {
public:
    // 覆盖put方法实现栈顶插入
    void put(T& tar) override {
        // 注销已有同名ID
        if (this->fast.find(tar.ID) != this->fast.end()) {
            return;
        }
        // 注册新元素到栈顶
        this->registerItem(tar.ID, this->the.size());
        this->the.push_back(tar);
    }

    // 添加栈顶弹出方法
    T pick() {
        if (this->_size == 0) return T();
        // 取出并删除栈顶元素
        return this->take(this->_size - 1);
    }

protected:
    // 覆盖unregisterItem防止栈元素被复用
    bool unregisterItem(long long index) override {
        if (this->defast.find(index) == this->defast.end()) return false;
        // 清除元素但不加入空闲队列
        this->the[index] = T();
        // 移除双向映射
        auto id = this->defast[index];
        this->defast.erase(index);
        this->fast.erase(id);
        this->_size--;
        return true;
    }
};
