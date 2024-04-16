//
// Created by khusn on 25.03.2024.
//
#pragma once
#include <list>
#include <forward_list>

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
        auto insert_ptr = it;
        while (insert_ptr != l.begin() && *insert_ptr >= *ptr) {
            std::advance(insert_ptr, -1);
        }
        l.insert(insert_ptr, *ptr);
        l.erase(ptr);
    }
}

template <typename It>
It fast_slow(It l, It r) {
    It fast = l, slow = l;
    while (fast != r && fast != std::next(r)) {
        std::advance(fast, 2);
        ++slow;
    }
    return slow;
}

template <typename It, typename V>
It bin_search(It l, It r, V v) {
    auto c = fast_slow(l, r);
    while (l != r && std::next(l) != r) {
        if (*c < v) {
            l = c;
        }
        else if (*c > v){
            r = c;
        }
        else {
            return c;
        }
        c = fast_slow(l, r);
    }
    if (v < *l)
        return l;

    return c;
}

template <typename T>
void bSort(std::list<T>& l) {
    for (auto it = std::next(l.begin()); it != l.end(); ++it) {
        auto insert_ptr = bin_search(l.begin(), it, *it);
        l.insert(insert_ptr, *it);
        l.erase(it);
    }
}