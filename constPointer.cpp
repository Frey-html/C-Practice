#include <iostream>
using namespace std;

int main(){
    int x = 5;
    const int *p1 = &x; // 常量指针，指向常量 int
    int* const p2 = &x;       // 指针常量，指向 int

    // 下面的操作
    // *p1 = 10; // 错误：不能修改 p1 指向的内容
    p1 = nullptr; // 合法：可以改变 p1 的指向

    *p2 = 10; // 合法：可以通过 p2 修改 x 的值
    // p2 = nullptr; // 错误：不能改变 p2 的指向

    std::cout << "x: " << x << std::endl; // 输出 x 的值

    return 0;
}