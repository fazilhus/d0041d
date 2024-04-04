#pragma once

#include <iostream>
#include <list>
#include <chrono>
#include <random>

#include "../src/sort.h"

std::list<int> rfilled(std::size_t n = 1000) {
    auto l = std::list<int>();

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(1, 100);
    for (std::size_t i = 0; i < n; ++i) {
        l.push_back(dist(rng));
    }

    return l;
}

void test_insert_sort() {
    int pow = 10000;
    auto l1 = rfilled(pow);
    auto start1 = std::chrono::high_resolution_clock::now();
    insert_sort(l1);
    auto dur1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start1);

    auto l2 = rfilled(pow);
    auto start2 = std::chrono::high_resolution_clock::now();
    bSort(l2);
    auto dur2 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start2);

    auto l3 = rfilled(pow);
    auto start3 = std::chrono::high_resolution_clock::now();
    l3.sort();
    auto dur3 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start3);

    std::cout << "Insert sort: " << dur1.count() << '\n';
    std::cout << "bSort: " << dur2.count() << '\n';
    std::cout << "Quick sort: " << dur3.count() << '\n';
}