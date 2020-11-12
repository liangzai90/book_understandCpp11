#include <iostream>
using namespace std;

void Throw() { throw 1; }
void NoBlockThrow() { Throw(); }
//noexcept用于提高标准库的性能，以及满足一些阻止异常扩散的需求
void BlockThrow() noexcept { Throw(); }

//noexcept 在模板中的使用
template <class T>
void fun() noexcept(noexcept(T()))
{
    //T()表达式是否会抛出异常决定fun函数是否是一个noexcept函数
    //这里的第二个noexcept就是一个noexcept操作符。当其参数是一个有可能抛出异常的表达式的时候，其返回值为false，反之为true.
    //这样一来我们就可以使模板函数根据条件实现noexcept修饰的版本或无noexcept修饰的版本。
    //这是C++11支持范型编程的一个特性
}

void list2_12()
{
    try
    {
        Throw();
    }
    catch (...)
    {
        cout << "Found throw." << endl;
    }

    try
    {
        NoBlockThrow();
    }
    catch (...)
    {
        cout << "Throw is not blocked." << endl;
    }

    try
    {
        BlockThrow(); // terminate called after throwing an instance of 'int'
    }
    catch (...)
    {
        cout << "Found throw 1." << endl;
    }
}

struct A
{
    ~A() { throw 1; }
};

struct B
{
    ~B() noexcept(false) { throw 2; }
};

struct C
{
    B b;
};

int funA() { A a; }
int funB() { B b; }
int funC() { C c; }

void list2_13()
{
    try
    {
        funB();
    }
    catch (...)
    {
        cout << "caught funB." << endl; //caught funB
    }

    try
    {
        funC();
    }
    catch (...)
    {
        cout << "caught funC." << endl; //caught funC
    }

    try
    {
        //类A，其析构函数被默认为noexcept(true)，从而阻止了异常的扩散
        funA(); //terminate called after throwing an instance of 'int'
    }
    catch (...)
    {
        cout << "caught funA." << endl;
    }
}

int main()
{
    //C++11默认将delete函数设置成noexcept，可以提高应用程序的安全性
    // void operator delete(void *) noexcept;
    // void operator delete[](void *) noexcept;
    //C++11默认让所有的析构函数都是 noexcept(true)的.
    list2_12();

    list2_13();

    return 0;
}

//编译选项：  g++ -std=c++11 chap2.6.cpp
