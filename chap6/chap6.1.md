


### 常量表达式 
```c++
const  int  i = 1;
constexpr  int j = 1;
```
两者在大多数情况下是没有区别的。
不过有一点是肯定的，就是如果i在全局名字空间中，编译期一定会为i产生数据。
而对于j，如果不是有代码显示地使用了它的地址，编译期可以选择不为它生成数据，而仅将其当做编译时期的值
（是不是想起了光有名字没有产生数据的枚举值，以及不会产生数据的右值字面常量？事实上，他们也都只是编译时期的常量）

constexpr 关键字是不能修饰自定义类型的，比如下面这样的类型定义和使用：
```C++
constexpr  struct  MyType {int i;};
constexpr  MyType  mt = {0};
```
在C++11中，就是无法通过编译的。

正确的做法是，定义自定义常量构造函数（constent expression  constructor）
例子：
```C++
struct MyType {
    constexpr MyType(int x): i(x){}  //自定义常量构造函数
    int i; 
};
constexpr MyType mt = {0};
```



### 变长参数
```C++
#include <stdio.h>
#include <stdarg.h>

//变长函数
double SumOfFloat(int count, ...)
{
    va_list ap;
    double sum = 0;
    //va_start 函数对ap进行初始化
    va_start(ap, count); //获得变长列表的句柄 ap

    for (int i = 0; i < count; ++i)
    {
        sum += va_arg(ap, double); //每次获得一个参数
    }
    va_end(ap);
    return sum;
}

int main()
{
    double ret = SumOfFloat(3, 1.1f, 2.2f, 3.3f);
    printf("ret:%f\r\n", ret);

    return 0;
}

```










