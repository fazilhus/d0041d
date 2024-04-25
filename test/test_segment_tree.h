#pragma once
#include "../src/segment_tree.h"

void test_clt() {
    {
        segment_tree clt{7, 3, 2, 4, 5, 6, 1};
        std::cout << "Max sum: " << clt.sum_on_range(0, 1) << '\n';
    }

    {
        segment_tree clt{-2, -7, 6, -8, 10, 5, -2, 6};
        std::cout << "Max sum: " << clt.sum_on_range(4, 5) << '\n';
    }
}