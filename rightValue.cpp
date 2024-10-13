#include <iostream>
#include <utility>

class MyClass {
private:
    int value;

public:
    MyClass(int v) : value(v) {
        std::cout << "Constructor: Initialized with value " << value << ".\n";
    }

    // 移动构造函数
    MyClass(MyClass&& other) noexcept : value(other.value) {
        std::cout << "Move Constructor: Moved value " << value << ".\n";
    }

    void print() const {
        std::cout << "Current value: " << value << "\n";
    }

    ~MyClass(){
        std::cout << "Destructor called" << \n;
    }
};

MyClass&& createTemporary() {
    MyClass temp(42); // 创建临时对象
    return std::move(temp); // 返回右值引用
}

int main() {
    MyClass&& ref = createTemporary(); // 试图绑定到右值引用
    ref.print(); // 这里会导致未定义行为
    return 0;
}
