#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <random>

#include "../src/algo.h"
#include "../src/segment_tree.h"

std::vector<int> rfilled_vector(std::size_t n = 1000) {
    auto l = std::vector<int>();

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(-10, 10);
    for (std::size_t i = 0; i < n; ++i) {
        int num = 0;
        do {
            num = dist(rng);
        } while (num == 0);
        l.push_back(num);
    }

    return l;
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
    for (auto el : v) {
        os << el << ' ';
    }
    return os;
}

void test_subsequence_max_sum() {
    std::vector<std::vector<int>> input{};
    // input.push_back({-2, 10, -8, 7, 7, -8, 10, -2});
    // input.push_back({-6, -5, 3, 6, 2, -4,  3, -7});
    // input.push_back({-2, -7, 6, -8, 10, 5, -2, 6});
    // input.push_back({-2, -2, 11, -4, 1, 6, -7, 8, -9, 1});
    // input.push_back({-5, -6, -1, 1, 9, 5, 2, -8, 3, -9});
    // input.push_back({5, -6, 7, -8, 5, 1, 4, -9, 9, -2});
    // input.push_back({-2, -6, 7, 5, 0, 5, -9, -5, 6, 4});
    // input.push_back({1, 2, -4, 4, -8, 10, 5, 1, 4, -9, 1, 1, 3, -7, 6, -1});
    // input.push_back({6, -7, -2, 6, 8, 5, 5, -8});
    for (std::size_t i = 8; i <= 4096; i *= 2) {
        input.push_back(rfilled_vector(i));
        //std::cout << input.back() << '\n';
    }

    for (int i = 0; i < 10000; ++i) {
        auto v = rfilled_vector(32);
        auto [sumk, _k1, _k2] = subarray_max_sum_b(v);
        auto [sumdnc, _dnc1, _dnc2] = subarray_max_sum_c1(v, 0, 31, 0);
        if (sumk != sumdnc) {
            std::cout << v << ' ' << sumk << ' ' << sumdnc << '\n';
            break;
        }
    }

    // std::cout << "\nKadane's\n";
    // for (const auto& v : input) {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     auto [sum, _1, _2] = subarray_max_sum_b(v);
    //     auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
    //     std::cout << "Result: " << sum << ", Took " << dur << "ms\n";
    // }

    // std::cout << "\nDivide and Conquer\n";
    // for (const auto& v : input) {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     auto [sum, _1, _2] = subarray_max_sum_c1(v, 0, v.size() - 1, 0);
    //     auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
    //     std::cout << "Result: " << sum << ", Took " << dur << "ms\n";
    // }

    // std::cout << "\nDivide and Conquer (precalculated sums using segment tree)\n";
    // for (const auto& v : input) {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     segment_tree sg{v};
    //     auto sum = sg.subarray_max_sum_c2();
    //     auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
    //     std::cout << "Result: " << sum << ", Took " << dur << "ms\n";
    // }

    // std::cout << "\nSliding Window\n";
    // for (const auto& v : input) {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     auto [sum, _1, _2] = subarray_max_sum_a1(v);
    //     auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
    //     std::cout << "Result: " << sum << ", Took " << dur << "ms\n";
    // }
    
    // std::cout << "\nSliding Window (accumulated sum)\n";
    // for (const auto& v : input) {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     auto [sum, _1, _2] = subarray_max_sum_a2(v);
    //     auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
    //     std::cout << "Result: " << sum << ", Took " << dur << "ms\n";
    // }
}

void test1_submatrix_max_sum() {
    std::vector<std::vector<int>> matrix = {
        { 0, -2, -7, 0 }, 
        { 9, 2, -6, 2 }, 
        { -4, 1, -4, 1 }, 
        { -1, 8, 0, -2 },
    };
    
    auto ans = submatrix_max_sum(matrix);
    auto correct = MatrixMask{1, 2, 0, 1, 15};
    std::cout << "Sub-Matrix max sum test 1 " << (ans == correct ? "finished successfully" : "failed" ) << '\n';
}

void test2_submatrix_max_sum() {
    std::vector<std::vector<int>> matrix = {
        { 1, 2, -1, -4, -20, 1 }, 
        { -8, -3, 4, 2, 1, -3 }, 
        { 3, 8, 10, 1, 3, 0 }, 
        { -4, -1, 1, 7, -6, -4 },
        { 0, 3, -30, 0, -3, -1 },
    }; 
    
    auto ans = submatrix_max_sum(matrix);
    auto correct = MatrixMask{1, 2, 1, 2, 29};
    std::cout << "Sub-Matrix max sum test 2 " << (ans == correct ? "finished successfully" : "failed" ) << '\n';
}

std::string create_palindromes(std::size_t length) {
    std::string res{};
    std::stack<char> st{};

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(72, 172);

    for (std::size_t i = 0; i < length / 2; ++i) {
        char c = 'a' + dist(rng);
        res.push_back(c);
        st.push(c);
    }

    while (!st.empty()) {
        res.push_back(st.top());
        st.pop();
    }

    return res;
}

void test_palindrome() {
    std::vector<std::string> input{
        "Anna",
        "rosor",
        "Du har bra hud",
        create_palindromes(100),
        create_palindromes(10000),
        create_palindromes(1000000),
        create_palindromes(100000000),
    };

    std::cout << "\nInplace\n";
    for (const auto& s : input) {
        auto start = std::chrono::high_resolution_clock::now();
        auto res = is_palindrome_a1(s);
        auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
        std::cout << "Is " << (res ? "a " : "not a ") << "palindrome\n";
        std::cout << "Length " << s.size() << ", Took " << dur << "ms\n";
    }

    // std::cout << "\nInplace with preprocess\n";
    // for (const auto& s : input) {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     auto res = is_palindrome_a2(s);
    //     auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
    //     std::cout << "Is " << (res ? "a " : "not a ") << "palindrome\n";
    //     std::cout << "Length " << s.size() << ", Took " << dur << "ms\n";
    // }

    std::cout << "\nStack\n";
    for (const auto& s : input) {
        auto start = std::chrono::high_resolution_clock::now();
        auto res = is_palindrome_b(s);
        auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
        std::cout << "Is " << (res ? "a " : "not a ") << "palindrome\n";
        std::cout << "Length " << s.size() << ", Took " << dur << "ms\n";
    }

    std::cout << "\nQueue\n";
    for (const auto& s : input) {
        auto start = std::chrono::high_resolution_clock::now();
        auto res = is_palindrome_c(s);
        auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
        std::cout << "Is " << (res ? "a " : "not a ") << "palindrome\n";
        std::cout << "Length " << s.size() << ", Took " << dur << "ms\n";
    }

    std::cout << "\nStack + Queue\n";
    for (const auto& s : input) {
        auto start = std::chrono::high_resolution_clock::now();
        auto res = is_palindrome_d(s);
        auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
        std::cout << "Is " << (res ? "a " : "not a ") << "palindrome\n";
        std::cout << "Length " << s.size() << ", Took " << dur << "ms\n";
    }
}

void algo_test_all() {
    test_palindrome();
}