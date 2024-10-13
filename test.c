#include <iostream>

class Base {
public:
    int value;
    void func() {
        std::cout << "Base::func()" << std::endl;
    }
};

class Derived1 : public Base {
};

class Derived2 : public Base {
};

class Derived : public Derived1, public Derived2 {
};

int main() {
    Derived d;

    // 访问 Base::value 会产生歧义
    //d.value;  // 错误：不明确，编译器不知道访问的是 Derived1::Base 还是 Derived2::Base

    // 访问 Base::func() 也会产生歧义
    //d.func();  // 错误：不明确，编译器无法确定调用哪一个 Base::func()
    
    // 可以明确地通过作用域访问
    d.Derived1::value = 10;  // 可以通过 Derived1 继承的 Base 访问 value
    d.Derived1::func();      // 可以明确调用 Derived1 中的 Base::func

    d.Derived2::value = 20;  // 可以通过 Derived2 继承的 Base 访问 value
    d.Derived2::func();      // 可以明确调用 Derived2 中的 Base::func
    
    std::cout << "Derived1's Base::value: " << d.Derived1::value << std::endl;
    std::cout << "Derived2's Base::value: " << d.Derived2::value << std::endl;

    return 0;
}
