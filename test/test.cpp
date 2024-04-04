#pragma once

#include <iostream>

#include "algo_test.h"
#include "sort_test.h"

int main() {
    test_insert_sort();
    algo_test_all();
    std::cin.get();
}