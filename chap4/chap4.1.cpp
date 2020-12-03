
/**
 * 
 * 1.右尖括号 > 的改进
 * C++98版本中>>之间要空格，否则会被解释为右移
 * C++11中，>> 不再需要空格
 * 
 * 2.auto类型推导
 * 从技术上严格来讲，静态类型和动态类型的主要区别在于对变量进行类型检查的时间点。
 * 对于所谓的静态类型，类型检查主要发生在编译阶段；
 * 而对于动态类型，类型检查主要发生在运行阶段。
 * 
 * auto 并非一种“类型”声明，而是一个类型声明时的“占位符”，编译器在编译时期会将auto 替代为实际的类型
 * 
 * 3.decltype
 * 
 * 4.追踪返回类型
 * 
 * 5.基于范围的 for 循环
 * 
 * 
*/

#include <iostream>
using namespace std;

#define Max1(a, b) ((a) > (b)) ? (a) : (b)
//将a,b都先算出来，再使用三元运算符进行比较，性能就比上面的好很多
#define Max2(a, b) ({ auto _a = (a); auto _b=(b);  (_a>_b)?_a:_b })

int main()
{
    int x;
    int *y = &x;
    double foo();
    int &bar();

    auto *a = &x;     // int*
    auto &b = x;      // int&
    auto c = y;       // int*
    auto *d = y;      // int*
    auto *e = &foo(); // 编译失败, 指针不能指向一个临时变量
    auto &f = foo();  // 编译失败, nonconst的左值引用不能和一个临时变量绑定
    auto g = bar();   // int
    auto &h = bar();  // int&

    return 0;
}
