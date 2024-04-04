#pragma once

#include <iostream>
#include <vector>
#include <cassert>

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
}

void test1_submatrix_max_sum() {
    std::vector<std::vector<int>> matrix = {
        { 0, -2, -7, 0 }, 
        { 9, 2, -6, 2 }, 
        { -4, 1, -4, 1 }, 
        { -1, 8, 0, -2 },
    };
    
    auto ans = submatrix_max_sum(matrix);
    auto correct = Answer{1, 2, 0, 1, 15};
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
    auto correct = Answer{1, 2, 1, 2, 29};
    std::cout << "Sub-Matrix max sum test 2 " << (ans == correct ? "finished successfully" : "failed" ) << '\n';
}

void algo_test_all() {
    test_sliding_window();
    test1_submatrix_max_sum();
    test2_submatrix_max_sum();
}