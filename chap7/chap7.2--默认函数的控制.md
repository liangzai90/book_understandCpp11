
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


 限制一些默认函数的生成
```C++
#include <iostream>
#include <type_traits>
using namespace std;
class NoCopyCstor{
    public:
    NoCopyCstor() = default;

    private:
    //将拷贝构造函数声明为 private 成员并不提供实现
    //可以有效阻止用户错用拷贝构造函数
    NoCopyCstor(const NoCopyCstor&);
};

int main()
{
    NoCopyCstor a;
    NoCopyCstor b(a);//无法通过编译

    return 0;
}

```


限制一些默认函数的生成，C++11标准提供的方法

```C++

#include <iostream>
#include <type_traits>
using namespace std;
class NoCopyCstor{
    public:
    NoCopyCstor() = default;

    //使用 "= delete"，同样可以有效阻止用户错用拷贝构造函数
    NoCopyCstor(const NoCopyCstor&) = delete;
};

int main()
{
    NoCopyCstor a;
    NoCopyCstor b(a);//无法通过编译

    return 0;
}

```
使用"=default"删除拷贝构造函数的缺省版本的实例。
值得注意的是，一旦缺省版本被删除了，重载该函数也是非法的。



###  "= defalut"  与  "= delete"
C++11称 "= defalut" 修饰的函数为显示缺省（explicit  defaulted）函数，
而称 "= delete" 修饰的函数为删除（deleted）函数。
























