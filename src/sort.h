//
// Created by khusn on 25.03.2024.
//
#pragma once
#include <list>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::list<T>& l) {
    for (auto it : l) {
        os << it << ' ';
    }
    return os;
}

// insertion sort for STL list
template <typename T>
void insert_sort(std::list<T>& l) {
    for (auto it = l.begin(); it != l.end(); ++it) {
        auto ptr = std::next(it);
        auto insert_ptr = l.begin();
        while (insert_ptr != it && *insert_ptr < *ptr) {
            ++insert_ptr;
        }
        l.insert(insert_ptr, *ptr);
        l.erase(ptr);
    }
}

template <typename T>
T fast_slow(T l, T r) {
    T fast = l, slow = l;
    while (fast != r && fast != std::next(r)) {
        fast = std::next(fast, 2);
        slow = std::next(slow);
    }
    return slow;
}

template <typename T, typename V>
T bin_search(T l, T r, V v) {
    auto c = fast_slow(l, r);
    while (l != r && std::next(l) != r) {
        if (*c <= v) {
            l = c;
        }
        else {
            r = c;
        }
        c = fast_slow(l, r);
    }
    return c;
}

template <typename T>
void bSort(std::list<T>& l) {
    for (auto it = l.begin(); it != l.end(); ++it) {
        auto ptr = std::next(it);
        auto insert_ptr = bin_search(l.begin(), it, *ptr);
        l.insert(insert_ptr, *ptr);
        l.erase(ptr);
    }
}