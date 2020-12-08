### 追踪返回类型的函数

C++ 在通往范型编程的路上狂奔不止，语法越来越高深复杂


auto占位符 和 ->return_type  是构成追踪返回类型函数的两个基本元素
在模板的类型推导中用的比较多
```c++
auto  func(char* a, int b) -> int

```


### 返回类型后置，使模板中的一些类型推导称为可能

下面是使用追踪返回类型的例子
```c++
#include <iostream>
using namespace std;

template<typename T1, typename T2>
auto Sum(const T1 & t1, const T2 & t2) -> decltype(t1 + t2){
    return t1 + t2; 
} 

template <typename T1, typename T2>
auto Mul(const T1 & t1, const T2 & t2) -> decltype(t1 * t2){
    return t1 * t2;
}

int main() {
    auto a = 3;
    auto b = 4L;
    auto pi = 3.14;
    
    auto c = Mul(Sum(a, b), pi);
    cout << c << endl;  // 21.98
}

```


### 追踪返回类型也被广泛地应用在转发函数中 

范型编程，至少在我目前这个阶段，感觉是很复杂、抽象的
```C++
#include <iostream>
using namespace std;

double foo(int a) {
    return (double)a + 0.1;
}

int foo(double b) {
    return (int)b;
}

template <class T> 
auto Forward(T t) -> decltype(foo(t)){
    return foo(t);
}

int main(){
    cout << Forward(2) << endl;     // 2.1
    cout << Forward(0.5) << endl;   // 0
}

```




