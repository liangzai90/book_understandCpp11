### 显示的实例化与外部模板的声明

#### 编译器不用每次都产生一份 fun<int>(int)的代码，可以减少编译时间
```cpp
////test.h
template <typename T>
void fun(T){};
```

```cpp
/////test.cpp
#include "test.h"
template void fun<int>(int); //显示地实例化
void test1() { fun(3); }
```

```cpp
////test2.cpp
#include "test.h"
extern template void fun<int>(int); //外部模板的生命 。和外部变量是一个道理
void test2() { fun(3); }
```

```txt
在广泛使用模板的项目中，编译器会产生大量冗余代码，会极大地增加编译器的编译时间和链接时间。 
解决这个问题的方法基本跟变量共享的思路是一样的，就是使用“外部的”模板。 

外部模板的使用实际依赖于C++ 98中一个已有的特性，即显示实例化（Explicit Instantiation）
```
对于模板

```cpp
template <typename T>
void fun(T){};
```
我们只需要声明：
```cpp
template void fun<int>(int);
```
C++11标准中，加入了外部模板的声明。语法上，外部模板的声明跟显示的实例化差不多，只是多了一个关键字 extern。

在实际上，C++11中“模板的显示实例化定义、外部模板声明和使用”好比“全局变量的定义、外部声明和使用”方式的再次应用。


```txt
在使用外部模板的时候，我们还需要注意以下问题：

  1.如果外部模板声明出现在某个编译单元中，那么与之对应的显示实例化必须出现于另一个编译单元中（即，声明和extern定义在不同.h文件中）
  或者同一个编译单元的后续代码中；

  2.外部模板声明不能用于一个静态函数（即文件域函数），但可以用于类静态成员函数（这一点是显而易见的，因为静态成员函数没有外部链接属性，
  不可能在本编译单元之外出现）。
```


局部和匿名类型作为模板实参
```cpp
template <typename T>
class X
{
};
template <typename T>
void TempFun(T t){};

struct A
{
} a;

//struct 之后没有跟一个名字，所以匿名了
struct
{
    int i;
} b; //b是匿名类型变量

typedef struct
{
    int i;
} B; //B是匿名类型

void Fun()
{
    struct C
    {
    } c; //c是局部类型

    X<A> x1;    //C++98通过，C++11通过
    X<B> x2;    //C++98错误，C++11通过
    X<C> x3;    //C++98错误，C++11通过
    TempFun(a); //C++98错误，C++11通过
    TempFun(b); //C++98错误，C++11通过
    TempFun(c); //C++98错误，C++11通过
}
```


匿名类型的声明不能在模板实参位置

虽然匿名类型可以被模板参数所接受，但是下面的写法是不可以编译通过的
```cpp
template <typename T>
struct MyTemplate
{
};
int main()
{
    //把匿名的结构体直接放在了模板实参的位置，不符合C/C++语法
    //在C++中，即使是匿名类型的声明，也需要独立的表达式语句。
    MyTemplate < struct
    {
        int a;
    } > t; //无法编译通过，匿名类型的声明不能在模板实参位置
    return 0;
}
```
