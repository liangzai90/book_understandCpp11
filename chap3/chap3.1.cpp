#include <iostream>
#include <string>
using namespace std;

class Base
{
public:
    Base() { cout << "base 1" << endl; };
    Base(int a) { cout << "base 2.a:" << a << endl; };
    Base(int a, int b) { cout << "base 3.a" << a << ",b:" << b << endl; };
    Base(float c) { cout << "base 4.c:" << c << endl; };
    void print(string str) { cout << "Base print:" << str << endl; }
};

class Drive : public Base
{
public:
    //通过using Base::Base 的声明，把基类中的构造函数继承到派生类B中。
    //C++11标准集成构造函数被设计为跟派生类中的各种默认函数一样，是隐式声明的。
    //这意味着如果一个继承构造函数不被相关代码使用，编译器不会为其产生真正的函数代码。节省目标代码空间。
    using Base::Base;
    void print2(string str)
    {
        cout << "Drive print2:" << str << endl;
    }
};

int main()
{
    Drive objD1;
    Drive objD2(2);
    Drive objD3(3, 4);
    Drive objD4(1.2345f);

    return 0;
}

// g++ -std=c++11 chap3.1.cpp
