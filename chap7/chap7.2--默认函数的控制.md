
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


 在类定义外用"= default"来指明使用缺省版本
```C++

class DefaultedOptr{
public:
    // 使用"= default"来产生缺省版本
    DefaultedOptr() = default;   

    // 这里没使用"= default"
    DefaultedOptr & operator = (const DefaultedOptr & );
};

// 在类定义外用"= default"来指明使用缺省版本
inline DefaultedOptr & DefaultedOptr::operator =( const DefaultedOptr & ) = default; 

```


显示删除可以避免编译器做一些不必要的隐式数据类型转换
```C++
class ConvType {
public:
    ConvType(int i) {};
    ConvType(char c) = delete;  // 删除char版本
};

void Func(ConvType ct) {}

int main() {
    Func(3);
    Func('a');  // 无法通过编译

    ConvType ci(3);
    ConvType cc('a');   // 无法通过编译
}
    

```


不建议用户将 explicit 关键字和显示删除合用，会引起一些混乱性。
```C++
class ConvType {
public:
    ConvType(int i) {};
    explicit ConvType(char c) = delete;  // 删除explicit的char构造函数
};

void Func(ConvType ct) {}

int main() {
    Func(3);
    Func('a');      // 可以通过编译

    ConvType ci(3);
    ConvType cc('a');   // 无法通过编译
}
    
```


对于一些普通的函数，我们依然可以通过显示删除来禁止类型转换
```C++
void Func(int i){};
void Func(char c) = delete;  // 显式删除char版本

int main(){
    Func(3);
    Func('c');  // 本句无法通过编译
    return 1;
}
```


#### 显示删除的一些有趣用法

使用显示删除来删除自定义类型的 operator new 操作符，就可以避免在堆上分配该class的对象
```C++
#include <cstddef>

class NoHeapAlloc{
public:
    void * operator new(std::size_t) = delete;
};

int main(){
    NoHeapAlloc nha;
    NoHeapAlloc * pnha = new NoHeapAlloc;   // 编译失败
    return 1;
}
```


我们需要对象在指定内存位置进行内存分配，并且不需要析构函数来完成一些对象级别的清理。
我们可以通过显示删除析构函数来限制自定义类型在栈上或者静态的构造。
```C++
#include <cstddef>
#include <new>

extern void* p;

class NoStackAlloc{
public:
    ~NoStackAlloc() = delete;
};

int main(){
    NoStackAlloc nsa;   // 无法通过编译
    new (p) NoStackAlloc(); // placement new, 假设无需析构
    return 1;
}

```
由于placement new 构造的对象，编译器不会为其调用析构函数，
因此，析构函数被删除的类能够正常地构造。

### 推而广之，将显示删除析构函数用于 构件单件模式（singleton）


