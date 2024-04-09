#pragma once

#include <vector>
#include <unordered_map>

template <class K, class V>
class ChainHashTable {
public:
    using size_type = std::size_t;
    using pair = std::pair<K, V>;
    using value_type = std::vector<pair>;

private:
    size_type size_;
    size_type cap_;
    value_type data_;
    std::vector<bool> fill_;
    float lf_;

public:
    ChainHashTable(float lf = 0.5f) : size_(0), cap_(16), data_(cap_), fill_(cap_), lf_(lf) {}
    ~ChainHashTable() = default;

    void insert(const K& key, V val) {
        if ((float)data_/cap_ > lf_) {
            rehash();
        }

        auto h = hash(*key, sizeof(key));
        size_type i = 0;
        while (fill_[h]) {
            h = hash(*key, sizeof(key), ++i);
        }

        data_[h] = {key, val};
        fill_[h] = true;
        size_++;
    }

    const V& search(const K& key) const {
        auto res = search_(key);
        if (!res.has_value()) {
            throw std::out_of_range("No such element in map");
        }

        return res.value().second;
    }

    void erase(const K& key) {
        size_type idx;
        auto res = search_(key, &idx);
        if (!res.has_value()) {
            throw std::out_of_range("No such element in map");
        }

        fill_[idx] = false;
    }

    class Iterator {
    private:
        reference it;
        size_type idx;

    public:
        friend class ChainHashTable;
        
        Iterator(pointer ptr, idx) : it(ptr), idx(idx) {}
        
        Iterator& operator++() {
            for (; !fill_[idx] && idx < fill_.size(); ++idx) {}
            it = data_[idx];
            return *this;
        }

        bool operator==(const Iterator& other) { return }
    };

private:
    size_type hash(void* key, size_type len_bytes, size_type idx = 0) {
        unsigned char *p = key;
        unsigned h = 0x811c9dc5;

        for (size_type i = 0; i < len_bytes; ++i) {
            h = (h ^ p[i]) * 0x01000193;
        }

        return ((h % cap_) + idx) % cap_;
    }

    void rehash() {
        auto new_cap = cap_ * 2;
        auto buff_data = value_type(new_cap);
        auto buff_fill = std::vector<bool>(new_cap);

        for (size_type i = 0; i < cap_; ++i) {
            if (!fill_[i]) continue;

            K key = data_[i].first;
            V val = data_[i].second;
            auto h = hash(*key, sizeof(key));
            size_type idx = 0;
            while (buff_fill[h]) {
                h = hash(*key, sizeof(key), ++idx);
            }

            buff_data[h] = {key, val};
            buff_fill[h] = true;
        }

        std::swap(data_, buff_data);
        std::swap(fill_, buff_fill);
    }

    std::optional<const pair&> search_(const K& key) const {
        auto h = hash(*key, sizeof(key));
        size_type i = 0;
        while (fill_[h] && key != data_[h].first) {
            h = hash(*key, sizeof(key), ++i);
        }
        if (fill_[h]) return data_[h];
        else return;
    }

    std::optional<const pair&> search_(const K& key, size_type& idx) const {
        auto h = hash(*key, sizeof(key));
        size_type i = 0;
        while (fill_[h] && key != data_[h].first) {
            h = hash(*key, sizeof(key), ++i);
        }
        idx = h;
        if (fill_[h]) return data_[h];
        else return;
    }
};