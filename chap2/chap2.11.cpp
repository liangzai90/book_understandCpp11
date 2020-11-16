#include <iostream>
using namespace std;

//定义一个函数模板
template <typename T>
void TempFun(T a)
{
    cout << "TempFun:" << a << endl;
}

//默认模板参数
void DefParm(int m = 3){}; //C++98编译通过，C++11编译通过

template <typename T = int>
class DefClass
{
}; //C++98编译通过，C++11编译通过

//C++98不支持函数模板的默认模板参数
template <typename T = int>
void DefTempParm(){}; //C++98编译失败，C++11编译通过

//类模板,默认参数位置从右到左
template <typename T1, typename T2 = int>
class DefClass1; //编译通过

template <typename T3 = int, typename T4>
class DefClass2; //编译不通过

template <typename T4, int i = 0>
class DefClass3; //编译通过

//函数模板，默认参数位置没有要求
template <typename T1 = int, typename T2>
void DefFunc1(T1 a, T2 b);

template <int i = 0, typename T>
void DefFunc2(T a);

// int main()
// {
//     TempFun(123); //实例化为 TempFun<const int>(123)
//
//     TempFun("12345"); //实例化为 TempFun<const char*>("12345")
// }

///C++11标准草案的例子
template <class T, class U = double>
void f(T t = 0, U u = 0);
void g()
{
    //默认模板参数通常是需要跟默认函数参数一起使用的
    //模板函数的默认形参不是模板参数推导的依据。函数模板参数的选择，总是由函数的实参推导而来的，这点在使用中应当注意。
    f(1, 'c');      // f<int,char>(1,'c')
    f(1);           // f<int,double>(1,0)，使用了默认模板参数double
    f();            //错误！！T无法被推导出来
    f<int>();       //f<int,double>(0,0) 使用了默认模板参数double
    f<int, char>(); //f<int,char>(0,0)
}

// g++ -std=c++11 chap2.11.cpp
