#pragma once
#include <cassert>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>


template <typename T>
class Group {
protected:
    std::vector<T> the{};

    long long _size{};

    // 快速映射
    std::unordered_map<std::string, long long> fast{};
    std::unordered_map<long long, std::string> defast{};

    // 空闲块
    std::queue<long long> free{};

protected:
    void registerItem(std::string ID, long long index) {
        fast.at(ID) = index;
        defast[index] = ID;
        _size++;
    }

    bool unregisterItem(std::string ID) {
        if (fast.find(ID) == fast.end()) {
            return false;
        }
        the[fast.at(ID)] = T();
        fast.erase(ID);
        defast.erase(fast.at(ID));
        _size--;
        return true;
    }

    bool unregisterItem(long long index) {
        if (defast.find(index) == defast.end()) {
            return false;
        }
        the[index] = T();
        defast.erase(index);
        fast.erase(defast[index]);
        _size--;
        return true;
    }

public:
    bool empty() { return _size == 0; }
    long long size() { return _size; }

public:
    void put(T& tar) {
        if (free.empty()) {
            registerItem(tar.ID, the.size());
            the.push_back(tar);
        } else {
            long long index = free.front();
            free.pop();
            registerItem(tar.ID, index);
            the[index] = tar;
        }
    }

    void submit(T& tar) {
        if (fast.find(tar.ID) != fast.end()) {
            return;
        } else {
            put(tar);
        }
    }

    T get(std::string ID) {
        return the[fast.at(ID)];
    }

    T get(long long index) {
        return the[index];
    }

    T take(std::string ID) {
        if (fast.find(ID) == fast.end()) {
            return T();
        }
        auto result = std::move(get(ID));
        free.push(fast.at(ID));
        unregisterItem(ID);
        return result;
    }

    T take(long long index) {
        if (index >= the.size()) {
            return T();
        }
        auto result = std::move(get(index));
        free.push(index);
        unregisterItem(index);
        return result;
    }

public:
    T& operator[](std::string ID) {
        assert(fast.find(ID) != fast.end() && "ID 不存在");
        return the[fast.at(ID)];
    }
    
    T& operator[](long long index) {
        assert(index < the.size() && "访问的索引 不存在");
        return the[index];
    }

    // const 版本
    const T& operator[](std::string ID) const {
        assert(fast.find(ID) != fast.end() && "ID 不存在");
        return the[fast.at(ID)]; // 使用 at() 可在 debug 模式下增加安全性
    }

    const T& operator[](long long index) const {
        assert(index < the.size() && "访问的索引 不存在");
        return the[index];
    }
};