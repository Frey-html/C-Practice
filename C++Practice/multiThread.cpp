#include <iostream>
#include <thread>   // 确保包含了这个头文件
#include <mutex>

void threadFunction() {
    std::cout << "Hello from thread!" << std::endl;
}

int main() {
    std::thread t(threadFunction); // 创建线程
    t.join();                      // 等待线程结束
    return 0;
}
