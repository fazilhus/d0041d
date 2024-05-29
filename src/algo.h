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

// tuple contains the sum, it's beginning index and it's ending index
std::tuple<int, std::size_t, std::size_t> max_prefix(const std::vector<int>& v, std::size_t l, std::size_t r) {
    if (l + 1 == r) return v[l] + v[r] > v[l] ? std::make_tuple(v[l] + v[r], l, r) : std::make_tuple(v[l], l, l);

    // middle of the segment
    std::size_t m = (l + r) / 2;
    // prefix of the left segment
    auto [ls, ll, lr] = max_prefix(v, l, m);
    // prefix of the right segment
    auto [rs, rl, rr] = max_prefix(v, m + 1, r);

    int sum = 0;
    /*
    sum of the segment from start of the left segment's max prefix to the
    end of the right's max prefix
    */
    for (auto i = ll; i <= rr; ++i) sum += v[i];
    return sum > ls ? std::make_tuple(sum, ll, rr) : std::make_tuple(ls, ll, lr);
}

// tuple contains the sum, it's beginning index and it's ending index
std::tuple<int, std::size_t, std::size_t> max_postfix(const std::vector<int>& v, std::size_t l, std::size_t r) {
    if (l + 1 == r) return v[l] + v[r] > v[r] ? std::make_tuple(v[l] + v[r], l, r) : std::make_tuple(v[r], r, r);

    // middle of the segment
    std::size_t m = (l + r) / 2;
    // postfix of the left segment
    auto [ls, ll, lr] = max_postfix(v, l, m);
    // postfix of the right segment
    auto [rs, rl, rr] = max_postfix(v, m + 1, r);

    int sum = 0;
    /*
    sum of the segment from start of the left segment's max postfix to the
    end of the right's max postfix
    */
    for (auto i = ll; i <= rr; ++i) sum += v[i];
    return sum > rs ? std::make_tuple(sum, ll, rr) : std::make_tuple(rs, rl, rr);
}

// divide and conquer
// tuple contains the sum, it's beginning index and it's ending index
std::tuple<int, std::size_t, std::size_t> subarray_max_sum_c1(const std::vector<int>& v, std::size_t l, std::size_t r) {
    if (l + 1 == r) return v[l] + v[r] >= v[l] && v[l] + v[r] >= v[r] ? std::make_tuple(v[l] + v[r], l, r) : (v[l] > v[r] ? std::make_tuple(v[l], l, l) : std::make_tuple(v[r], r, r));

    // middle of the segment
    std::size_t m = (l + r) / 2;
    // left segment's max subsequence
    auto [ls, ll, lr] = subarray_max_sum_c1(v, l, m);
    // left segment's max postfix
    auto [pos, pol, por] = max_postfix(v, l, m);
    // right segment's max subsequence
    auto [rs, rl, rr] = subarray_max_sum_c1(v, m + 1, r);
    // right segment's max prefix
    auto [prs, prl, prr] = max_prefix(v, m + 1, r);

    int sum_l = 0;
    std::size_t sum_ll = 0, sum_lr = 0;
    // combined sum of the left segment
    if (ll == pol) {
        // if the left segment's max postfix contains the max subsequence
        sum_l = pos;
        sum_ll = pol;
        sum_lr = por;
    }
    else {
        // if the left segment's max postfix and max subsequence do not overlap
        for (auto i = ll; i <= por; ++i) sum_l += v[i];
        sum_ll = ll;
        sum_lr = por;
    }
    
    int sum_r = 0;
    std::size_t sum_rl = 0, sum_rr = 0;
    // combined sum of the right segment
    if (rr == prr) {
        // if the right segment's max prefix contains the max subsequence
        sum_r = prs;
        sum_rl = prl;
        sum_rr = prr;
    }
    else {
        // if the right segment's max prefix and max subsequence do not overlap
        for (auto i = prl; i <= rr; ++i) sum_r += v[i];
        sum_rl = prl;
        sum_rr = rr;
    }

    /*
    sum of the segment from start of the left segment's max subsequence to the
    end of the right's max subsequence
    */
    int sum = sum_l + sum_r;

    // finding the greatest segment
    std::vector<std::tuple<int, std::size_t, std::size_t>> sums = {
        {ls, ll, lr}, {rs, rl, rr}, {sum_l + prs, sum_ll, prr}, {sum_r + pos, pol, sum_rr},
        {pos + prs, pol, prr}, {sum_r, sum_rl, sum_rr}, {sum_l, sum_ll, sum_lr}, {sum, ll, rr},
    };
    std::sort(sums.begin(), sums.end(), [](const std::tuple<int, std::size_t, std::size_t>& A, 
        const std::tuple<int, std::size_t, std::size_t>& B){
            return std::get<0>(A) > std::get<0>(B);});

    return sums[0];
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int max(int a, int b, int c) {
    return max(max(a, b), c);
}

int maxCrossingSum(const std::vector<int>& arr, int l, int m, int h) {
    int sum = 0;
    int left_sum = INT_MIN;
    for (int i = m; i >= l; i--) {
        sum += arr[i];
        if (sum > left_sum)
            left_sum = sum;
    }

    sum = 0;
    int right_sum = INT_MIN;
    for (int i = m + 1; i <= h; i++) {
        sum += arr[i];
        if (sum > right_sum)
            right_sum = sum;
    }

    return max(left_sum + right_sum - arr[m], left_sum, right_sum);
}

int maxSubArraySum(const std::vector<int>& arr, int l, int h) {
    if (l > h)
        return INT_MIN;
    if (l == h)
        return arr[l];

    int m = (l + h) / 2;
    return max(maxSubArraySum(arr, l, m - 1),
               maxSubArraySum(arr, m + 1, h),
               maxCrossingSum(arr, l, m, h));
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

    std::size_t i = 0;
    std::size_t middle = s.size() / 2;
    for (; i < middle; ++i) {
        if (std::isspace(s[i]) || std::ispunct(s[i])) continue;
        st.push(std::tolower(s[i]));
    }
    middle += s.size() % 2;
    for (i = middle; i < s.size(); ++i) {
        if (std::isspace(s[i]) || std::ispunct(s[i])) continue;
        q.push(s[i]);
    }

    if (s.size() % 2 == 1) ++middle;

    while (!st.empty() && !q.empty()) {
        if (st.top() != q.front()) return false;

        st.pop();
        q.pop();
    }

    return st.empty() && q.empty();
}

// O(n^2)
int pairs_impl(const std::vector<int>& v, std::size_t start, std::size_t end) {
    auto m = start + (end - start) / 2;
    if (m == start || m == end) {
        return v[start] > v[end] ? 1 : 0;
    }

    int count = 0;
    count += pairs_impl(v, start, m);
    count += pairs_impl(v, m + 1, end);

    for (std::size_t i = start; i <= m; ++i) {
        for (std::size_t j = m + 1; j <= end; ++j) {
            if (v[i] > v[j]) count++;
        }
    }
    return count;
}

int pairs(const std::vector<int>& v) {
    return pairs_impl(v, 0, v.size() - 1);
}

int merge(std::vector<int>& v, std::size_t l, std::size_t m, std::size_t r) {
    std::vector<int> lsub{};
    auto lb = m - l  + 1;
    lsub.reserve(lb);
    for (auto i = l; i <= m; ++i) {
        lsub.push_back(v[i]);
    }

    std::vector<int> rsub{};
    auto rb = r - m;
    rsub.reserve(rb);
    for (auto i = m + 1; i <= r; ++i) {
        rsub.push_back(v[i]);
    }

    int count = 0, total = 0;
    // for (std::size_t il = 0, ir = 0; (il < lb) && (ir < rb);) {
    //     if (lsub[il] > rsub[ir]) {
    //         count++;
    //         ir++;
    //     }
    //     else {
    //         total += count;
    //         il++;
    //     }
    // }


    std::size_t im = l, il = 0, ir = 0;
    for (; (il < lb) && (ir < rb); ++im) {
        //std::cout << "pair " << lsub[il] << ' ' << rsub[ir] << '\n';
        if (lsub[il] <= rsub[ir]) {
            v[im] = lsub[il];
            il++;
            total += count;
        }
        else {
            v[im] = rsub[ir];
            ir++;
            count++;
        }
        //std::cout << "count " << total << ' ' << count << '\n';
    }
    
    if (il < lb) total += count;
    for (; il < lb; ++il, ++im) {
        v[im] = lsub[il];
    }

    for (; ir < rb; ++ir, ++im) {
        v[im] = rsub[ir];
    }
    return total;
}

int mergesort_and_count_impl(std::vector<int>& v, std::size_t l, std::size_t r) {
    if (l >= r) return 0;

    auto m = l + (r - l) / 2;
    //std::cout << "indexes " << l << ' ' << m << ' ' << r << '\n';
    int left_pair = mergesort_and_count_impl(v, l, m);
    int right_pair = mergesort_and_count_impl(v, m + 1, r);
    int combined = merge(v, l, m, r);
    //std::cout << left_pair << ' ' << right_pair << ' ' << combined << '\n';
    // for (auto i = l; i <= r; ++i) {
    //     std::cout << v[i] << ' ';
    // }
    // std::cout << '\n';
    return left_pair + right_pair + combined;
}

int mergesort_and_count(std::vector<int>& v) {
    return mergesort_and_count_impl(v, 0, v.size() - 1);
}