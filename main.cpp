#include <iostream>
#include <iomanip>

#include "src/sort.h"
#include "src/algo.h"


int main() {
    std::vector<std::vector<int>> matrix = {
        { 1, 2, -1, -4, -20, 1 }, 
        { -8, -3, 4, 2, 1, -3 }, 
        { 3, 8, 10, 1, 3, 0 }, 
        { -4, -1, 1, 7, -6, -4 },
        { 0, 3, -30, 0, -3, -1 },
    };
    for (std::size_t i = 0; i < matrix.size(); ++i) {
        for (std::size_t j = 0; j < matrix[0].size(); ++j) {
            std::cout << std::setw(4) << matrix[i][j];
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    
    auto ans = submatrix_max_sum(matrix);
    for (std::size_t i = ans.i; i <= ans.i + ans.n; ++i) {
        for (std::size_t j = ans.j; j <= ans.j + ans.m; ++j) {
            std::cout << std::setw(4) << matrix[i][j];
        }
        std::cout << '\n';
    }

    std::cin.get();
    return 0;
}
