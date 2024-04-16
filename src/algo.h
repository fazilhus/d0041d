#pragma once

#include <iostream>
#include <vector>

struct MatrixMask {
    std::size_t i, n, j, m;
    int sum;

    bool operator==(const MatrixMask& other) const {
        return i == other.i &&
            j == other.j &&
            n == other.n &&
            m == other.m &&
            sum == other.sum;
    }
};

std::ostream& operator<<(std::ostream& os, const MatrixMask& ans) {
        os << "Sum " << ans.sum << '\n';
        os << "\t i from " << ans.i << " for " << ans.n << '\n';
        os << "\t j from " << ans.j << " for " << ans.m << '\n';
        return os;
    }

std::tuple<int, std::size_t, std::size_t> subarray_max_sum(const std::vector<int>& v) {
    if (v.empty()) return {0, 0, 0};

    std::size_t max_start = 0, start = 0, end = 0;
    int curr = v[0];
    int max = v[0];

    for (std::size_t i = 1; i < v.size(); ++i) {
        if (v[i] > v[i] + curr) {
            curr = v[i];
            start = i;
        }
        else {
            curr = v[i] + curr;
        }
 
        if (curr > max) {
            max = curr;
            end = i;
            max_start = start;
        }
    }

    return {max, max_start, end};
}

MatrixMask submatrix_max_sum(const std::vector<std::vector<int>>& mat) {
    MatrixMask res{ 0, 0, 0, 0, INT_MIN };
    auto n = mat.size();
    auto m = mat[0].size();

    auto prefix = std::vector<std::vector<int>>(n, std::vector<int>(m, 0));

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < m; ++j) {
            if (j == 0) prefix[i][j] = mat[i][j];
            else prefix[i][j] = mat[i][j] + prefix[i][j - 1];
        }
    }

    for (std::size_t left = 0; left < m; ++left) {
        for (std::size_t right = left; right < m; ++right) {
            std::vector<int> v{};
            for (std::size_t i = 0; i < n; ++i) {
                int el = 0;
                if (left == 0) el = prefix[i][right];
                else el = prefix[i][right] - prefix[i][left - 1];
                v.push_back(el);
            }

            auto [sum, start, end] = subarray_max_sum(v);
            if (sum > res.sum) {
                res.i = start;
                res.n = end - start;
                res.j = left;
                res.m = right - left;
                res.sum = sum;
            }
        }
    }

    return res;
}

int subarray_max_sum(const std::vector<int>& v, std::size_t start, std::size_t end) {
    if (end - start == 0)
        return v[start];
    if (end - start == 1)
        return std::max({v[start], v[end], v[start] + v[end]});

    auto left = subarray_max_sum(v, start, (start + end) / 2);
    auto right = subarray_max_sum(v, (start + end) / 2 + 1, end);
    for (std::size_t i = start; i <= end; ++i) {
        std::cout << v[i] << ' ';
    }
    std::cout << "\n\t left: " << left << " right: " << right << " sum: " << left + right << '\n';
    return std::max({left, right, left + right});
}