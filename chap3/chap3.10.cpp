#include <iostream>
#include <type_traits>
using namespace std;

using uint = unsigned int;
typedef unsigned int UINT;
using sint = int;

//使用 using 定义类型别名
template <typename T>
using MapString = std::map<T, char *>;

int main()
{
    //使用了C++11标准模板库中的 is_same 模板类来帮助我们判断两个类型是否一致
    cout << is_same<uint, UINT>::value << endl; // 1

    MapString<int> numberdString; //在使用模板编程的时候，using的语法甚至比typedef更加灵活

    return 0;
}

//  g++ -std=c++11 chap3.10.cpp
