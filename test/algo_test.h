#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <random>

#include "../src/algo.h"

void test_sliding_window() {
    std::vector<int> v{ -2, -5, 6, -2, -3, 1, 5, -6 };
    std::vector<int> ans{ 6, -2, -3, 1, 5 };
    bool flag = true;

    auto [sum, start, end] = subarray_max_sum(v);
    for (std::size_t i = start; i < end && (i - start) < ans.size(); ++i) {
        if (v[i] != ans[i - start]) {
            flag = false;
            break;
        }
    }

    std::cout << "Sub-Array max sum test 1 " << (flag ? "finished successfully" : "failed" ) << '\n';

    v = {-2, -2, 11, -4, 1, 6, -7, 8, -9, 1};
    auto res = subarray_max_sum(v, 0, v.size() - 1);
    std::cout << "Sub-Array max sum test 2 " << (res == 11 ? "finished successfully" : "failed" ) << "\n\tres = " << res << '\n';
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
    std::uniform_int_distribution<int> dist(97, 97 + 26);

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
        create_palindromes(1000),
        create_palindromes(10000),
        create_palindromes(100000),
        create_palindromes(1000000),
        create_palindromes(10000000),
        create_palindromes(100000000),
        create_palindromes(1000000000),
    };

    std::cout << "\nInplace\n";
    for (const auto& s : input) {
        auto start = std::chrono::high_resolution_clock::now();
        auto res = is_palindrome_a(s);
        auto dur = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000;
        std::cout << "Is " << (res ? "a " : "not a ") << "palindrome\n";
        std::cout << "Length " << s.size() << ", Took " << dur << "ms\n";
    }

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