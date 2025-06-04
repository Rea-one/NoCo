#include <vector>

/* 
    在移动系列中
    大写表示会检查边界
    小写表示不会检查边界
*/
using ll = long long;
template <typename T>
class Cursor { 
protected:
    std::vector<T> data;
    ll cursor = 0;
    ll size = 0;

public:
    // 检测移动位置是否合法
    bool offset(ll offset) { 
        if (cursor + offset < 0 || cursor + offset >= size)
            return false;
        return true;
    }
    
    
public:
    // 初始化
    void init(std::vector<T> target) {
        data = std::move(target);
        cursor = 0;
        size = data.size();
    }

    // 移动游标（不检查边界）
    ll move(ll walk) {
        cursor += walk;
        return cursor;
    }

    // 移动游标（检查边界）
    ll Move(ll walk) {
        auto then = cursor + walk;
        if (then < 0) {
            cursor = 0;
        } else if (then >= size) {
            cursor = size - 1;
        } else {
            cursor = then;
        }
        return cursor;
    }
    
    // 跳转至（不检查边界）
    ll jump(ll jump) {
        cursor = jump;
        return cursor;
    }

    // 跳转至（检查边界）
    ll Jump(ll jump) {
        if (jump < 0) {
            cursor = 0;
        } else if (jump >= size) {
            cursor = size - 1;
        } else {
            cursor = jump;
        }
        return cursor;
    }

    // 前移
    ll prior() {
        return move(-1);
    }
    // 前移
    ll Prior() {
        return Move(-1);
    }
    // 后移
    ll next() {
        return move(1);
    }
    // 后移
    ll Next() {
        return Move(1);
    }

    // 获取游标处数据
    T get() {
        return data[cursor];
    }
    // 获取即时跳转处的数据（不移动，不检查边界）
    T getOff(ll offset) {
        return data[cursor + offset];
    }
    // 获取即时跳转处数据（移动，不检查边界）
    T getOn(ll offset) {
        cursor = cursor + offset;
        return data[cursor];
    }

    // 获取即时跳转处数据（不移动，检查边界）
    T GetOff(ll offset) {
        if (cursor + offset < 0) {
            return data[0];
        } else if (cursor + offset >= size) {
            return data[size - 1];
        } else {
            return data[cursor + offset];
        }
    }
    // 获取即时跳转处数据（移动，检查边界）
    T GetOn(ll offset) {
        auto then = cursor + offset;
        if (then < 0) {
            cursor = 0;
        } else if (then >= size) {
            cursor = size - 1;
        } else {
            cursor = then;
        }
        return data[cursor];
    }

    // 获取游标处数据并移动
    T take() {
        auto result = data[cursor];
        move(1);
        return result;
    }

    bool atEnd() {
        return cursor >= size;
    }
};