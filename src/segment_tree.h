#pragma once
#include <vector>
#include <iostream>


class segment_tree {
private:
    std::vector<int> v;
    std::vector<int> data;

public:
    explicit segment_tree(const std::vector<int>& init) : v(init) {
        fill(v);
        data.resize(2 * v.size());
        //std::cout << "Data: " << v << '\n';
        build(1, 0, v.size() - 1);
        //std::cout << "Tree: " << data << '\n';
    }

    segment_tree(const std::initializer_list<int>& init) : v(init) {
        fill(v);
        data.resize(2 * v.size());
        //std::cout << "Data: " << v << '\n';
        build(1, 0, v.size() - 1);
        //std::cout << "Tree: " << data << '\n';
    }

    int sum_on_range(std::size_t l, std::size_t r) const {
        return sum_on_range_impl(1, 0, v.size() - 1, l, r);
    }

    int subarray_max_sum_c2() const {
        auto [sum, _1, _2] = subarray_max_sum_c2_impl(0, v.size() - 1);
        return sum;
    }

private:
    void build(std::size_t i, std::size_t l, std::size_t r) {
        //std::cout << data << '\n';
        if (l == r) {
            data[i] = v[r];
            return;
        }
        
        std::size_t m = (l + r) / 2;
        build(i * 2, l, m);
        build(i * 2 + 1, m + 1, r);
        data[i] = data[i * 2] + data[i * 2 + 1];
    }

    void fill(std::vector<int>& v) {
        std::size_t pow = 1;
        while (pow < v.size()) pow *= 2;
        for (std::size_t i = v.size(); i < pow; ++i) {
            v.push_back(0);
        }
    }

    int sum_on_range_impl(std::size_t i, std::size_t l, std::size_t r, std::size_t il, std::size_t ir) const {
        if (il > ir) return 0;
        if (l == il && ir == r) return data[i];

        std::size_t m = (l + r) / 2;
        int ls = sum_on_range_impl(2 * i, l, m, il, std::min(m, ir));
        int rs = sum_on_range_impl(2 * i + 1, m + 1, r, std::max(m + 1, il), ir);
        return ls + rs;
    }

    std::tuple<int, std::size_t, std::size_t> subarray_max_sum_c2_impl(std::size_t l, std::size_t r) const {
        if (l + 1 == r) return v[l] + v[r] >= v[l] && v[l] + v[r] >= v[r] ? std::make_tuple(v[l] + v[r], l, r) : (v[l] > v[r] ? std::make_tuple(v[l], l, l) : std::make_tuple(v[r], r, r));

        std::size_t m = (l + r) / 2;
        //std::cout << c << ' ' << l << ' ' << m << ' ' << r << '\n';
        auto [ls, ll, lr] = subarray_max_sum_c2_impl(l, m);
        auto [pos, pol, por] = max_postfix(l, m);
        auto [rs, rl, rr] = subarray_max_sum_c2_impl(m + 1, r);
        auto [prs, prl, prr] = max_prefix(m + 1, r);

        int sum_l = 0;
        std::size_t sum_ll = 0, sum_lr = 0;
        if (ll == pol) {
            sum_l = pos;
            sum_ll = pol;
            sum_lr = por;
        }
        else {
            //for (auto i = ll; i <= por; ++i) sum_l += v[i];
            sum_l = sum_on_range(ll, por);
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
            //for (auto i = prl; i <= rr; ++i) sum_r += v[i];
            sum_r = sum_on_range(prl, rr);
            sum_rl = prl;
            sum_rr = rr;
        }

        int sum = sum_on_range(ll, rr);
        //for (auto i = ll; i <= rr; ++i) sum += v[i];

        //std::cout << c << "  l  " << ls << ' ' << ll << ' ' << lr << "  pos  " << pos << ' ' << pol << ' ' << por << "  r  " << rs << ' ' << rl << ' ' << rr << "  prs  " << prs << ' ' << prl << ' ' << prr << "  sum  " << sum << ' ' << ll << ' ' << rr << '\n';
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

    std::tuple<int, std::size_t, std::size_t> max_prefix(std::size_t l, std::size_t r) const {
        if (l + 1 == r) return v[l] + v[r] > v[l] ? std::make_tuple(v[l] + v[r], l, r) : std::make_tuple(v[l], l, l);

        std::size_t m = (l + r) / 2;
        auto [ls, ll, lr] = max_prefix(l, m);
        auto [rs, rl, rr] = max_prefix(m + 1, r);

        int sum = sum_on_range(ll, rr);
        //for (auto i = ll; i <= rr; ++i) sum += v[i];
        return sum > ls ? std::make_tuple(sum, ll, rr) : std::make_tuple(ls, ll, lr);
    }

    std::tuple<int, std::size_t, std::size_t> max_postfix(std::size_t l, std::size_t r) const {
        if (l + 1 == r) return v[l] + v[r] > v[r] ? std::make_tuple(v[l] + v[r], l, r) : std::make_tuple(v[r], r, r);

        std::size_t m = (l + r) / 2;
        auto [ls, ll, lr] = max_postfix(l, m);
        auto [rs, rl, rr] = max_postfix(m + 1, r);

        int sum = sum_on_range(ll, rr);
        // for (auto i = ll; i <= rr; ++i) sum += v[i];
        return sum > rs ? std::make_tuple(sum, ll, rr) : std::make_tuple(rs, rl, rr);
    }
};