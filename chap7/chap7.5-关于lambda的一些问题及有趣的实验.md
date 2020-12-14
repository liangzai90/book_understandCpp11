

捕捉列表不同会导致不同的结果。
按值方式传递捕捉列表和按引用方式传递捕捉列表效果是不一样的。
```C++
#include <iostream>
using namespace std;

int main()
{
    int j = 12;
    auto by_val_lambda = [=] { return j + 1; };  //这个位置 j 是什么值， lambda 里面就一直是什么值了
    auto by_ref_lambda = [&] { return j + 1; };
    
    cout << "00 by_val_lambda: " << by_val_lambda() << endl; // 13
    cout << "00 by_ref_lambda: " << by_ref_lambda() << endl; // 13

    j++;
    cout << "11 by_val_lambda: " << by_val_lambda() << endl; // 13
    cout << "11 by_ref_lambda: " << by_ref_lambda() << endl; // 14

    j++;
    cout << "22 by_val_lambda: " << by_val_lambda() << endl; // 13
    cout << "22 by_ref_lambda: " << by_ref_lambda() << endl; // 15
}

```


C++11标准将lambda的类型定义为“闭包”的类。
而每个lambda表达式则会产生一个闭包类型的临时对象（右值）
因此，严格意义上讲，lambda函数并非函数指针。
不过C++11标准却允许lambda表达式向函数指针的转换，前提是lambda函数没有捕获任何变量，
且函数指针所指示的函数原型，必须跟lambda函数有着相同的调用方式。

例如：

```C++
int main() {
    int girls = 3, boys = 4;
    auto totalChild = [](int x, int y)->int{ return x + y; };
    typedef int (*allChild)(int x, int y);
    typedef int (*oneChild)(int x);

    allChild p;
    p = totalChild;

    oneChild q;
    q = totalChild;     // 编译失败，参数必须一致

    decltype(totalChild) allPeople = totalChild;    // 需通过decltype获得lambdas的类型
    decltype(totalChild) totalPeople = p;           // 编译失败，指针无法转换为lambda
    return 0;
}

```

关于 lambda函数 的常量性及 mutable 关键字
```C++
int main(){
    int val;
    // 编译失败, 在const的lambda中修改常量
    auto const_val_lambda = [=]() { val = 3;};

    // 非const的lambda,可以修改常量数据
    auto mutable_val_lambda = [=]() mutable { val = 3;};  

    // 依然是const的lambda，不过没有改动引用本身
    auto const_ref_lambda = [&] { val = 3;};

    // 依然是const的lambda，通过参数传递val
    auto const_param_lambda = [&](int v) { v = 3;};
    const_param_lambda(val);

    return 0;
}

```


































