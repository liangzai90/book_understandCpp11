
### 类与默认函数 

在C++中声明自定义的类，编译器会默认帮助程序员生成一些他们未自定义的成员函数。
这样的函数版本被称为“默认函数”。这包括了以下一些自定义类型的成员函数：

 - > 构造函数
 - > 拷贝构造函数
 - > 拷贝赋值函数 ( operator = )
 - > 移动构造函数
 - > 移动拷贝函数
 - > 析构函数
 
 此外，C++编译器还会为以下这些自定义类型提供全局默认操作符函数：
 
 - > operator,
 - > operator &
 - > operator &&
 - > operator*
 - > operator->
 - > operator->*
 - > operator new
 - > operator delete

",","&","&&","*","->", "new","delete"等操作符的重载



程序员可以在默认构造函数定义或者声明时加上" = default "，
从而显示地指示编译器生成该函数的默认版本。
```C++

#include <iostream>
#include <type_traits>
using namespace std;

class TowCstor{
    public:
    //提供了带参数版本的构造函数，再指示编译器提供默认版本，则本自定义类型依然是POD类型
    TowCstor() = default;
    TowCstor(int i):data(i){};

    private:
    int data;
};

int main()
{
    cout <<is_pod<TowCstor>::value<<endl;  // 1
    return 0;
}

```











