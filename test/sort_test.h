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

void test_insert_sort_random() {
    std::cout << "Random\n";
    std::size_t size = 10000;
    {
        auto l = rfilled(size);
        auto start = std::chrono::high_resolution_clock::now();
        l.sort();
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
        std::cout << "QuickSort" << ": " << (double)dur.count() / 1000000000 << "s\n";
    }
    std::cout << '\n';

    {
        auto l = rfilled(size);
        auto start = std::chrono::high_resolution_clock::now();
        insert_sort(l);
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
        std::cout << "Insert Sort " << ": " << (double)dur.count() / 1000000000 << "s\n";
    }
    std::cout << '\n';

    {
        auto l = rfilled(size);
        auto start = std::chrono::high_resolution_clock::now();
        bSort(l);
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
        std::cout << "bSort " << ": " << (double)dur.count() / 1000000000 << "s\n";
    }
    std::cout << '\n';
}

void test_insert_sort_almost_sorted() {
    std::cout << "Almost Sorted\n";
    std::size_t size = 10000;
    {
        std::list<int> l = rfilled(size);
        l.sort();
        auto pos = std::next(l.begin(), size / 2);
        l.insert(pos, *l.begin());
        l.erase(l.begin());

        auto start = std::chrono::high_resolution_clock::now();
        l.sort();
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
        std::cout << "QuickSort " << ": " << (double)dur.count() / 1000000000 << "s\n";
    }
    std::cout << '\n';

    {
        std::list<int> l = rfilled(size);
        l.sort();
        auto pos = std::next(l.begin(), size / 2);
        l.insert(pos, *l.begin());
        l.erase(l.begin());

        auto start = std::chrono::high_resolution_clock::now();
        insert_sort(l);
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
        std::cout << "Insertion Sort " << ": " << (double)dur.count() / 1000000000 << "s\n";
    }
    std::cout << '\n';

    {
        std::list<int> l = rfilled(size);
        l.sort();
        auto pos = std::next(l.begin(), size / 2);
        l.insert(pos, *l.begin());
        l.erase(l.begin());

        auto start = std::chrono::high_resolution_clock::now();
        bSort(l);
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
        std::cout << "bSort " << ": " << (double)dur.count() / 1000000000 << "s\n";
    }
    std::cout << '\n';
}

void test_insert_sort_sorted() {
    std::cout << "Sorted\n";
    std::size_t size = 10000;
    {
        std::list<int> l = rfilled(size);
        l.sort();

        auto start = std::chrono::high_resolution_clock::now();
        l.sort();
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
        std::cout << "QuickSort " << ": " << (double)dur.count() / 1000000000 << "s\n";
    }
    std::cout << '\n';

    {
        std::list<int> l = rfilled(size);
        l.sort();

        auto start = std::chrono::high_resolution_clock::now();
        insert_sort(l);
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
        std::cout << "Insertion Sort " << ": " << (double)dur.count() / 1000000000 << "s\n";
    }
    std::cout << '\n';

    {
        std::list<int> l = rfilled(size);
        l.sort();
        
        auto start = std::chrono::high_resolution_clock::now();
        bSort(l);
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
        std::cout << "bSort " << ": " << (double)dur.count() / 1000000000 << "s\n";
    }
    std::cout << '\n';
}