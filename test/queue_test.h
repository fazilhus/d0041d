#pragma once
#include <iostream>

#include "../src/queue.h"

void test_max_queue() {
    max_queue<int> mq;
    std::cout << "Queue: 4\n";
    mq.push(4);
    std::cout << "Queue: 4, 2\n";
    mq.push(2);
    std::cout << "Maximum element in the queue: " << mq.max() << '\n';
    std::cout << "Queue: 4, 2, 6\n";
    mq.push(6);
    std::cout << "Maximum element in the queue: " << mq.max() << '\n';
    std::cout << "Queue: 4, 2, 6, 1\n";
    mq.push(1);
    std::cout << "Queue: 2, 6, 1\n";
    mq.pop();
    std::cout << "Queue: 6, 1\n";
    mq.pop();
    std::cout << "Queue: 1\n";
    mq.pop();
    std::cout << "Maximum element in the queue: " << mq.max() << '\n';
}