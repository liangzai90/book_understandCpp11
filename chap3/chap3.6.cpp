#include <iostream>
using namespace std;
#include <vector>

/**
 * 一种最典型的判别方法就是，在赋值表达式中，出现在等号左侧的就是“左值”，而在等号右侧的，则称为“右值”
 * 比如：
 * 
 * a = b + c
 * 
 * a是左值，b+c是右值。
 * ************************************
 * C++中广泛认同的说法：
 * 可以取地址的、有名字的就是左值
 * 不能取地址的，没有名字的就是右值
 * 
 * &a 是允许的操作， &(b+c)这样的操作不会通过编译
 * 因此a是左值， b+c 是右值
 * 
 * **************************************
 * 
 * 更为细致地，在C++11中，右值是由两个概念构成的，一个是将亡值(xvalue, eXpiring Value)，另一个则是纯右值(prvalue, Pure Rvalue)
 * 
 * 纯右值：比如非引用返回的函数返回的临时变量值；一些运算表达式，比如1+3产生的临时变量值；不跟对象关联的字面变量，比如：2，‘c’，true 也是纯右值
 * 此外，类型转换函数的返回值、lambda表达式等，也都是右值。
 * 
 * 将亡值是C++11新增的跟右值引用相关的表达式，这样表达式通常是将要移动的对象（移为他用），
 * 比如返回右值引用 T&& 的函数返回值、std::move的返回值，或者转换为 T&& 的类型转换函数的返回值。
 * 
 * 剩余的，可以标识函数、对象的值都属于左值。
 * 
 * 在C++11的程序中， 所有的值必须属于 左值、将亡值、纯右值三者之一。
 * 
 * 
 * 右值引用就是对一个右值进行引用的类型，由于右值通常不具有名字，我们也只能通过引用的方式找到它的存在。
 * 通常情况下我们只能是从右值表达式获得其引用，比如：
 * T && a = ReturnRvalue();
 * 
 * 
 * 
*/

// struct Copyable{
//     Copyable(){};
//     Copyable(const Copyable& obj){
//         cout << "Copied" << endl;
//     }
// };

// Copyable ReturnRvalue() { return Copyable(); }

// void AcceptVal(Copyable){};

// void AcceptRef(const Copyable &){};

// int main()
// {
//     cout << "Pass by value: " << endl;
//     AcceptVal(ReturnRvalue());//临时值被拷贝传入
//     cout << "Pass by reference: " << endl;
//     AcceptRef(ReturnRvalue());//临时值被作为引用传递

//     cout << "Hello Left And Right VALUE" << endl;
//     return 0;
// }

class Copyable
{
public:
    Copyable() {}
    Copyable(const Copyable &o)
    {
        cout << "Copied" << endl;
    }
};

Copyable ReturnRvalue()
{
    Copyable a;
    return a;
}
void AcceptVal(Copyable) {}
void AcceptRef(const Copyable &cp) {} //Copyable c = std::move(cp);}
void AcceptRRef(int &&i)
{
    i += 3;
    cout << i << endl;
}

int main()
{
    cout << "is_rvalue_reference:" << is_rvalue_reference<string &&>::value << endl;
    cout << "is_reference<string:" << is_reference<string &&>::value << endl;
    cout << "is_lvalue_reference:" << is_lvalue_reference<string &&>::value << endl;

    int x = 0;
    decltype(x) y; //decltype 只是借用别人的类型而已，没感觉推导的作用
    cout << "decltype:" << sizeof(decltype(x)) << endl;
    cout << endl;

    cout << "Pass by value: " << endl;
    AcceptVal(ReturnRvalue()); // 临时值被拷贝传入
    cout << "Pass by reference: " << endl;
    AcceptRef(ReturnRvalue()); // 临时值被作为引用传递
    AcceptRRef(1);             // 临时值被作为引用传递
}
// g++ -std=c++11 chap3.6.cpp
