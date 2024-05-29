#pragma once

#include <chrono>
#include <random>
#include <set>

#include "../src/tree.h"

void test_insert() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(-10000, 10000);
    int num_elem = 5000;
    // c = 0.5
    {
        Tree t(0.5);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_elem; ++i) {
            t.insert(dist(rng));
        }
        auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
        std::cout << "C: 0.5, Number of Rebalances: " << t.info() << ", Took " << dur << "ms\n";
    }

    // c = 0.75
    {
        Tree t(0.75);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_elem; ++i) {
            t.insert(dist(rng));
        }
        auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
        std::cout << "C: 0.75, Number of Rebalances: " << t.info() << ", Took " << dur << "ms\n";
    }

    // c = 0.9
    {
        Tree t(0.9);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_elem; ++i) {
            t.insert(dist(rng));
        }
        auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
        std::cout << "C: 0.9, Number of Rebalances: " << t.info() << ", Took " << dur << "ms\n";
    }

    // c = 0.95
    {
        Tree t(0.95);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_elem; ++i) {
            t.insert(dist(rng));
        }
        auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
        std::cout << "C: 0.95, Number of Rebalances: " << t.info() << ", Took " << dur << "ms\n";
    }

    // c = 0.97
    {
        Tree t(0.97);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_elem; ++i) {
            t.insert(dist(rng));
        }
        auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
        std::cout << "C: 0.97, Number of Rebalances: " << t.info() << ", Took " << dur << "ms\n";
    }

    // c = 0.98
    {
        Tree t(0.98);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_elem; ++i) {
            t.insert(dist(rng));
        }
        auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
        std::cout << "C: 0.98, Number of Rebalances: " << t.info() << ", Took " << dur << "ms\n";
    }

    // c = 0.99
    {
        Tree t(0.99);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_elem; ++i) {
            t.insert(dist(rng));
        }
        auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
        std::cout << "C: 0.99, Number of Rebalances: " << t.info() << ", Took " << dur << "ms\n";
    }

    // STL set
    {
        std::set<int> s{};
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_elem; ++i) {
            s.insert(dist(rng));
        }
        auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
        std::cout << "STL Set: Took " << dur << "ms\n";
    }
}