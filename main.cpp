#include <iostream>
#include "indicators.h"
#include <chrono>


int main() {
    // make函数用来把一个任意参数的集合完美转移给一个构造函数从而生成动态分配内存的对象
    auto spin = std::make_unique<indicator::indicator>(std::chrono::milliseconds(200), 3, "Finished loading some data", "Process info: ", " Loading data...");
    spin -> start();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    spin->stop();
    return 0;
}
