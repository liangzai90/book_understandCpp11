
#### 初识 lambda 函数 （匿名函数）

```C++
#include <iostream>
using namespace std;

int main()
{
    int girls = 3, boys = 4;
    auto totalChild = [](int x, int y )->int{return x+y;};

    cout<< totalChild(girls, boys)<<endl;
    return 0;
}

```
我们定义了 lambda 函数，该函数接受2个参数(int x, inty)，并且返回其和。
直观地看，lambda 函数跟普通函数相比不需要定义函数名，取而代之的多了一对方括号 ( [] )
此外，lambda 函数还采用了追踪返回类型的方式声明其返回值。



####  lambda 函数的语法定义如下 

```txt
 [capture]  (parameters) mutable ->return-type {statement}
```
其中，
 - > [capture]：捕捉列表。捕捉列表总是出现在lambda函数的开始处。事实上，[]是lambda引出符。
 编译器根据该引出符判断接下来的代码是否是lambda函数。
 捕捉列表能够捕捉上下文中的变量以供lambda函数使用。
 
 - > (parameters)：参数列表。与普通函数的参数列表一致。如果不需要参数传递，则可以连通括号 () 一起省略。

 - > mutable：mutable修饰符。默认情况下，lambda函数总是一个const函数，mutable可以取消其常量性。
 在使用该修饰符时，参数列表不可省略（即使参数为空）。

 - > ->return-type：返回类型。用追踪返回类型形式声明函数的返回类型。
 出于方便，不需要返回值的时候，也可以连同符号 -> 一起省略。
 此外，在返回类型明确的情况下，也可以省略该部分，让编译器对返回类型进行推导。

 - > {statement}：函数体。内容与普通函数一样，不过除了可以使用参数之外，还可以使用所有捕获的变量。

在lambda函数的定义中，参数列表和返还类型都是可选的部分。
捕捉列表可能为空。极端情况下，C++11中最为简略的lambda函数只需要声明为
```C++
[]{};
```

各种各样的 lambda 函数
```C++

int main(){
    []{};           // 最简lambda函数
    int a = 3;
    int b = 4;
    [=] { return a + b;};       // 省略了参数列表与返回类型，返回类型由编译器推断为int
    auto fun1 = [&](int c) { b = a + c; };  // 省略了返回类型，无返回值
    auto fun2 = [=, &b](int c)->int { return b += a + c; };     // 各部分都很完整
}

```












