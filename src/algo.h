#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <numeric>

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

// sliding window (accumulated sum)
// return sum, [start, end)
std::tuple<int, std::size_t, std::size_t> subarray_max_sum_a1(const std::vector<int>& v) {
    if (v.empty()) return {0, 0, 0};

    int max = INT_MIN, curr = 0;
    std::size_t start = 0, end = 0;

    for (std::size_t window = 1; window <= v.size(); ++window) {
        for (std::size_t i = 0; i < v.size() - window + 1; ++i) {
            curr = std::accumulate(v.begin() + i, v.begin() + i + window, 0);
            //std::cout << curr << ' ' << i << ' ' << i + window << '\n';
            if (curr > max) {
                max = curr;
                start = i;
                end = i + window;
            }
        }
    }
    return {max, start, end};
}

// sliding window (accumulated sum)
// return sum, [start, end)
std::tuple<int, std::size_t, std::size_t> subarray_max_sum_a2(const std::vector<int>& v) {
    if (v.empty()) return {0, 0, 0};

    int max = INT_MIN, curr = 0;
    std::size_t start = 0, end = 0;

    for (std::size_t window = 1; window <= v.size(); ++window) {
        curr = std::accumulate(v.begin(), v.begin() + window, 0);
        //std::cout << curr << ' ' << 0 << ' ' << window << '\n';
        if (curr > max) {
            max = curr;
            start = 0;
            end = window;
        }

        for (std::size_t i = 1; i < v.size() - window + 1; ++i) {
            curr = curr - v[i - 1] + v[i + window - 1];
            //std::cout << curr << ' ' << i << ' ' << i + window << '\n';
            if (curr > max) {
                max = curr;
                start = i;
                end = i + window;
            }
        }
    }
    return {max, start, end};
}

// kadane's max sum of an subsequence
// return sum, [start, end]
std::tuple<int, std::size_t, std::size_t> subarray_max_sum_b(const std::vector<int>& v) {
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

std::tuple<int, std::size_t, std::size_t> max_prefix(const std::vector<int>& v, std::size_t l, std::size_t r) {
    if (l + 1 == r) return v[l] + v[r] > v[l] ? std::make_tuple(v[l] + v[r], l, r) : std::make_tuple(v[l], l, l);

    // middle of the segment
    std::size_t m = (l + r) / 2;
    // prefix of the left segment
    auto [ls, ll, lr] = max_prefix(v, l, m);
    // prefix of the right segment
    auto [rs, rl, rr] = max_prefix(v, m + 1, r);

    int sum = 0;
    for (auto i = ll; i <= rr; ++i) sum += v[i];
    return sum > ls ? std::make_tuple(sum, ll, rr) : std::make_tuple(ls, ll, lr);
}

std::tuple<int, std::size_t, std::size_t> max_postfix(const std::vector<int>& v, std::size_t l, std::size_t r) {
    if (l + 1 == r) return v[l] + v[r] > v[r] ? std::make_tuple(v[l] + v[r], l, r) : std::make_tuple(v[r], r, r);

    // middle of the segment
    std::size_t m = (l + r) / 2;
    // postfix of the left segment
    auto [ls, ll, lr] = max_postfix(v, l, m);
    // postfix of the right segment
    auto [rs, rl, rr] = max_postfix(v, m + 1, r);

    int sum = 0;
    for (auto i = ll; i <= rr; ++i) sum += v[i];
    return sum > rs ? std::make_tuple(sum, ll, rr) : std::make_tuple(rs, rl, rr);
}

// divide and conquer
std::tuple<int, std::size_t, std::size_t> subarray_max_sum_c1(const std::vector<int>& v, std::size_t l, std::size_t r, std::size_t c) {
    if (l + 1 == r) return v[l] + v[r] >= v[l] && v[l] + v[r] >= v[r] ? std::make_tuple(v[l] + v[r], l, r) : (v[l] > v[r] ? std::make_tuple(v[l], l, l) : std::make_tuple(v[r], r, r));

    std::size_t m = (l + r) / 2;
    auto [ls, ll, lr] = subarray_max_sum_c1(v, l, m, c + 1);
    auto [pos, pol, por] = max_postfix(v, l, m);
    auto [rs, rl, rr] = subarray_max_sum_c1(v, m + 1, r, c + 1);
    auto [prs, prl, prr] = max_prefix(v, m + 1, r);

    int sum_l = 0;
    std::size_t sum_ll = 0, sum_lr = 0;
    if (ll == pol) {
        sum_l = pos;
        sum_ll = pol;
        sum_lr = por;
    }
    else {
        for (auto i = ll; i <= por; ++i) sum_l += v[i];
        sum_ll = ll;
        sum_lr = por;
    }
    
    int sum_r = 0;
    std::size_t sum_rl = 0, sum_rr = 0;
    if (rr == prr) {
        sum_r = prs;
        sum_rl = prl;
        sum_rr = prr;
    }
    else {
        for (auto i = prl; i <= rr; ++i) sum_r += v[i];
        sum_rl = prl;
        sum_rr = rr;
    }

    int sum = 0;
    for (auto i = ll; i <= rr; ++i) sum += v[i];

    int max = std::max({ls, sum_l, rs, sum_r, pos + prs, pos + sum_r, sum_l + prs, sum});
    if (sum == max) return {sum, ll, rr};
    if (sum_l == max) return {sum_l, sum_ll, sum_lr};
    if (sum_r == max) return {sum_r, sum_rl, sum_rr};
    if (pos + prs == max) return {pos + prs, pol, prr};
    if (sum_l + prs == max) return {sum_l + prs, sum_ll, prr};
    if (sum_r + pos == max) return {sum_r + pos, pol, sum_rr};
    if (ls == max) return {ls, ll, lr};
    // rs == max
    return {rs, rl, rr};
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

            auto [sum, start, end] = subarray_max_sum_b(v);
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

// inplace (without preprocess)
bool is_palindrome_a1(const std::string& s) {
    for (std::size_t l = 0, r = s.size() - 1; l <= r; ++l, --r) {
        if (std::isspace(s[l]) || std::ispunct(s[l])) ++l;
        if (std::isspace(s[r]) || std::ispunct(s[r])) --r;

        if (std::tolower(s[l]) != std::tolower(s[r])) return false;
    }
    return true;
}

// inplace (with preprocess)
bool is_palindrome_a2(const std::string& s) {
    auto ss = s;
    std::erase_if(ss, [](char c) { return std::isspace(c) || std::ispunct(c); });
    for (std::size_t l = 0, r = ss.size() - 1; l <= r; ++l, --r) {
        if (std::tolower(ss[l]) != std::tolower(ss[r])) return false;
    }
    return true;
}

// stack inplace
bool is_palindrome_b(const std::string& s) {
    std::stack<char> st{};

    std::size_t i = 0;
    for (; i < s.size() / 2; ++i) {
        if (std::isspace(s[i]) || std::ispunct(s[i])) continue;
        st.push(std::tolower(s[i]));
    }

    if (s.size() % 2 == 1) ++i;

    for (; i < s.size(); ++i) {
        if (std::isspace(s[i]) || std::ispunct(s[i])) continue;
        if (st.top() != std::tolower(s[i])) return false;
        st.pop();
    }

    return st.empty();
}

// queue
bool is_palindrome_c(const std::string& s) {
    std::queue<char> q{};

    std::size_t i = 0;
    std::size_t middle = s.size() / 2;
    for (; i < middle; ++i) {
        if (std::isspace(s[i]) || std::ispunct(s[i])) continue;
        q.push(std::tolower(s[i]));
    }

    if (s.size() % 2 == 1) ++middle;

    for (i = s.size() - 1; i >= middle; --i) {
        if (std::isspace(s[i]) || std::ispunct(s[i])) continue;
        if (q.front() != std::tolower(s[i])) return false;
        q.pop();
    }

    return q.empty();
}

// stack + queue
bool is_palindrome_d(const std::string& s) {
    std::stack<char> st{};
    std::queue<char> q{};
    auto ss = s;
    std::erase_if(ss, [](char c) { return std::isspace(c) || std::ispunct(c); });

    std::size_t i = 0;
    std::size_t middle = ss.size() / 2;
    for (; i < middle; ++i) {
        st.push(std::tolower(ss[i]));
        q.push(std::tolower(ss[middle + (ss.size() % 2) + i]));
    }

    if (ss.size() % 2 == 1) ++middle;

    while (!st.empty() && !q.empty()) {
        if (st.top() != q.front()) return false;

        st.pop();
        q.pop();
    }

    return st.empty() && q.empty();
}