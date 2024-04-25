#pragma once
#include <queue>
#include <deque>

template <typename T>
class max_queue {
private:
    std::queue<T> q;
    std::deque<T> dq;

public:
    max_queue() = default;

    void push(const T& v) {
        q.push(v);

        if (dq.empty()) {
            dq.push_back(v);
            return;
        }

        while (!dq.empty() && dq.front() < v) {
            dq.pop_back();
        }
        dq.push_back(v);
    }

    T pop() {
        T res = q.front();

        if (q.front() == dq.front()) {
            dq.pop_front();
        }

        q.pop();
        return res;
    }

    T max() const {
        return dq.front();
    }
};