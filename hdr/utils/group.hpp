/*
 * Group 模块方法说明:
 * 
 * 【受保护方法 - 内部使用】
 * void registerItem(std::string ID, long long index): 注册新元素到指定索引
 * bool unregisterItem(std::string ID): 通过ID注销元素
 * bool unregisterItem(long long index): 通过索引注销元素
 * 
 * 【公共方法 - 外部接口】
 * void put(T& tar): 插入/覆盖元素（自动处理空闲块）
 * bool submit(T& tar): 提交新元素（仅当ID不存在时插入）true: 插入成功， false: 插入失败
 * T get(std::string ID): 通过ID获取元素拷贝
 * T get(long long index): 通过索引获取元素拷贝
 * T take(std::string ID): 取出并删除指定ID的元素
 * T take(long long index): 取出并删除指定索引的元素
 * void push(T tar): 强制追加新元素到末尾
 * T pick() const: 获取最后一个有效元素（不删除）
 * 【操作符重载】
 * T& operator[](std::string ID): 通过ID访问元素（带断言检查）
 * T& operator[](long long index): 通过索引访问元素（带断言检查）
 * const T& operator[](std::string ID) const: 常量版本的ID访问
 * const T& operator[](long long index) const: 常量版本的索引访问
 */

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
        // 检查ID和索引是否已存在
        if (fast.find(ID) != fast.end() || defast.find(index) != defast.end()) {
            return; // 避免重复注册
        }
        fast[ID] = index;

        defast[index] = ID;
        _size++;
    }

    bool unregisterItem(std::string ID) {
        if (fast.find(ID) == fast.end()) {
            return false;
        }
        long long index = fast[ID];
        the[index] = T();
        fast.erase(ID);
        defast.erase(index);
        free.push(index); // 将索引加入空闲队列

        _size--;
        return true;
    }

    bool unregisterItem(long long index) {
        if (defast.find(index) == defast.end()) {
            return false;
        }

        std::string ID = defast[index];
        the[index] = T();
        defast.erase(index);
        fast.erase(ID);
        free.push(index); // 将索引加入空闲队列

        _size--;
        return true;
    }
    
    void shorten() { 
        while (_size > 0 && defast.find(_size - 1) == defast.end()) {
            _size--;
        }
        if (_size < the.size()) {
            the.resize(_size);
        }
    }

    long long get_free() {
        while (!free.empty()) {
            if (free.front() >=  _size) {
                free.pop();
            } else {
                return free.front();
            }
        }
        return -1;
    }
    
public:
    bool empty() { return _size == 0; }
    long long size() { return _size; }
    
    int freeSize() { return free.size(); }

public:
    void put(T& tar) {
        auto position = get_free();
        if (position == -1) {
            registerItem(tar.ID, the.size());
            the.push_back(tar);
        } else {
            long long index = position;
            free.pop();
            registerItem(tar.ID, index);
            the[index] = tar;
        }
    }

    bool submit(T& tar) {
        if (fast.find(tar.ID) != fast.end()) {
            return false;
        } else {
            put(tar);
            return true;
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
        free.push(fast[ID]);

        unregisterItem(ID);
        return result;
    }

    T take(long long index) {
        if (index >= the.size() || defast.find(index) == defast.end()) {

            return T();
        }
        auto result = std::move(get(index));
        free.push(index);
        unregisterItem(index);
        return result;
    }

    void push(T tar) {
        registerItem(tar.ID, the.size());
        the.push_back(tar);
    }

    T pick() const {
        assert(!_size && "尝试获取空集合的元素");
        // 先缩短数组确保末尾有效
        shorten();
        if (_size == 0) return T();
        // 取最后一个有效元素并删除
        return take(the[_size - 1].ID);
    }

    void pock() {
        assert(!_size && "尝试获取空集合的元素");
        assert(the.size() && "尝试获取空集合的元素");
        _size = the.size() - 1;
        shorten();
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