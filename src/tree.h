#pragma once
#include <iostream>
#include <memory>
#include <vector>

class Tree {
private:
    struct Node {
        int data;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        std::weak_ptr<Node> parent;
        unsigned num;

        Node(int n) : data(n), left(), right(), parent(), num(1) {}
    };
    using pointer = std::shared_ptr<Node>;
    using wpointer = std::weak_ptr<Node>;

    pointer root;
    float ratio;
    std::size_t c;

public:
    Tree() : Tree(0.5f) {}
    Tree(float r) : root(nullptr), ratio(r), c(0) {}
    ~Tree() = default;

    void insert(int d) {
        if (!root) {
            root = std::make_shared<Node>(d);
            return;
        }

        auto ptr = root;
        while (ptr != nullptr) {
            if (d <= ptr->data) {
                if (!ptr->left) {
                    ptr->left = std::make_shared<Node>(d);
                    ptr->left->parent = ptr;
                    break;
                }
                else {
                    ptr = ptr->left;
                }
            }
            else {
                if (!ptr->right) {
                    ptr->right = std::make_shared<Node>(d);
                    ptr->right->parent = ptr;
                    break;
                }
                else {
                    ptr = ptr->right;
                }
            }
        }

        for (; ptr != nullptr; ptr = ptr->parent.lock()) {
            ptr->num++;
        }

        for (ptr = root; ptr != nullptr;) {
            int t = ptr->num;
            int l = 0;
            int r = 0;
            if (ptr->left) l = ptr->left->num;
            if (ptr->right) r = ptr->right->num;
            //if (l == 0 || r == 0);

            if (l >= 1 && r >= 1 && (l > t * ratio || r > t * ratio)) {
                rebalance(ptr);
                break;
            }

            if (d <= ptr->data) ptr = ptr->left;
            else ptr = ptr->right;
        }
    }

    void print() const {
        print_in_order(root, 0);
        std::cout << '\n';
    }

    std::size_t info() const {
        return c;
    }

private:
    void rebalance(pointer ptr) {
        c++;
        std::vector<int> v{};
        rebalance_impl(v, ptr);
        auto parent = ptr->parent.lock();
        if (!ptr->parent.lock()) {
            root.reset();
            root = create_tree(v);
        }
        else {
            if (parent->left == ptr) {
                parent->left = nullptr;
                parent->left = create_tree(v);
            }
            else {
                parent->right = nullptr;
                parent->right = create_tree(v);
            }
        }
    }

    void rebalance_impl(std::vector<int>& v, pointer ptr) {
        if (!ptr) return;

        rebalance_impl(v, ptr->left);
        v.push_back(ptr->data);
        rebalance_impl(v, ptr->right);
    }

    pointer create_tree(const std::vector<int>& v) {
        int l = 0, r = v.size() - 1;
        pointer root = create_tree_impl(v, l, r);
        return root;
    }

    pointer create_tree_impl(const std::vector<int>& v, int l, int r) {
        if (l > r) return nullptr;
        if (l == r) return std::make_shared<Node>(v[l]);

        auto m = l + (r - l) / 2;
        auto ptr = std::make_shared<Node>(v[m]);
        ptr->left = create_tree_impl(v, l, m - 1);
        ptr->right = create_tree_impl(v, m + 1, r);
        return ptr;
    }

    void print_in_order(const pointer ptr, unsigned space) const {
        if (!ptr) return;

        space += 4;

        print_in_order(ptr->left, space);
        for (int i = 4; i < space; ++i) std::cout << ' ';
        std::cout << ptr->data << ' ' << ptr->num << '\n';
        print_in_order(ptr->right, space);
    }
};