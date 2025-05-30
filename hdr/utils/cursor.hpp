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
    bool offset(ll offset) { 
        if (cursor + offset < 0 || cursor + offset >= size)
            return false;
        return true;
    }
    
    
public:
    void init(std::vector<T> target) {
        data = std::move(target);
        cursor = 0;
        size = data.size();
    }
    ll move(ll walk) {
        cursor += walk;
        return cursor;
    }
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
    
    ll jump(ll jump) {
        cursor = jump;
        return cursor;
    }

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

    ll prior() {
        return move(-1);
    }
    ll Prior() {
        return Move(-1);
    }
    ll next() {
        return move(1);
    }
    ll Next() {
        return Move(1);
    }

    T get() {
        return data[cursor];
    }
    T getOff(ll offset) {
        return data[cursor + offset];
    }

    T GetOff(ll offset) {
        if (cursor + offset < 0) {
            return data[0];
        } else if (cursor + offset >= size) {
            return data[size - 1];
        } else {
            return data[cursor + offset];
        }
    }
    T take() {
        auto result = data[cursor];
        move(1);
        return result;
    }

    bool atEnd() {
        return cursor >= size;
    }
};