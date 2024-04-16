#pragma once

#include <iostream>

#include "algo_test.h"
#include "sort_test.h"
//#include "hashtable_test.h"

int main() {
    test_insert_sort_random();
    test_insert_sort_almost_sorted();
    test_insert_sort_sorted();
}