//
// Created by khusn on 26.03.2024.
//
#pragma once
#include <vector>
#include <functional>

template <class T, class Comp = std::less<T>>
class heap {
public:
    using container_type = std::vector<T>;
    using value_compare = Comp;
    using value_type = T;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;

private:
    size_type size_;
    container_type data_;
    Comp comp_;

public:
    heap() : size_(0), data_(size_) {}
    heap(const heap& other) : size_(other.size_), data_(other.data_) {}
    heap(heap&& other) noexcept : size_(0), data_(size_) {
        std::swap(size_, other.size_);
        std:swap(data_, other.data_);
    }
    ~heap() = default;

    heap& operator=(const heap& other) {
        size_ = other.size();
        data_ = std::vector<T>(size_);
        for (auto i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
        return *this;
    }

    heap& operator=(heap&& other) noexcept {
        std::swap(size_, other.size_);
        std:swap(data_, other.data_);
        return *this;
    }

    const_reference top() const {
        const_reference ref = data_[0];
        return ref;
    }

    bool empty() const { return size_ == 0; }
    size_type size() const { return size_; }

    void push(const value_type& v) {
        data_.push_back(v);
        size_++;
        check_tree();
    }

    void push(value_type&& v) {
        data_.push_back(v);
        size_++;
        check_tree();
    }

    template <class... Args>
    void emplace(Args&& ...args) {
        data_.emplace_back(std::forward<Args>(args)...);
        size_ = data_.size();
        check_tree();
    }

    T pop() {
        std::swap(data_[0], data_.back());
        auto res = data_.back();
        data_.pop_back();
        size_--;

        size_type c = 0;
        size_type l = 1;
        size_type r = 2;
        while (r < size_ &&
            (!comp_(data_[c], data_[l]) || !comp_(data_[c], data_[r]))) {
            auto next = comp(l, r);
            std::swap(data_[c], data_[next]);
            c = next;
            l = 2 * c + 1;
            r = 2 * c + 2;
        }

        if (l < size_ && !comp_(data_[c], data_[l])) {
            std::swap(data_[c], data_[l]);
        }
        return res;
    }

    void swap(heap& other) noexcept {
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }

private:
    size_type comp(size_type a, size_type b) {
        return comp_(data_[a], data_[b]) ? a: b;
    }

    void check_tree() {
        for (size_type i = size_ - 1;
            i >= 0 && compare(data_[i], data_[(i - 1) / 2]);
            i = (i - 1) / 2) {
            std::swap(data_[i], data_[(i - 1) / 2]);
        }
    }
};
