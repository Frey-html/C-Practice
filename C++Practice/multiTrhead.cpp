#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;  // 全局互斥量

void printMessage(const std::string& message, int n) {
    // 上锁
    mtx.lock();
    for (int i = 0; i < n; ++i) {
        std::cout << message << " " << i << "\n";
    }
    // 解锁
    mtx.unlock();
}

int main() {
    std::thread t1(printMessage, "Thread 1", 5);
    std::thread t2(printMessage, "Thread 2", 5);

    t1.join();
    t2.join();
    return 0;
}