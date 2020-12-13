
1.常量表达式  constexpr 

2.变长模板是C++引入的新的“变长”参数的工具

3.原子操作，宣告了C++来到了并行编程和多线程时代（易于学习，难于精通）

```C++
atomic<int>  a;

atomic<float> b {1.2f};

atomic<string*>  ptr;
```

4.线程局部存储（TLS,  Thread  Local  storage）

所谓线程局部存储变量，就是拥有线程生命周期及线程可见性的变量。

通过 thread_local 修饰符声明
```C++

int  thread_local  errCode;

```

5.快速退出: quick_exit 与  at_quick_exit
quick_exit是一项多线程情况下的新发明，可以用于解除因为退出造成的死锁等不良状态。
不过读者也可以尝试着使用它来免除大量的不必要的析构函数调用。

与abort不同的是，abort的结果通常是异常退出，而quick_exit 与 exit 同属于正常退出。
此外，使用 at_quick_exit 注册的函数，也可以在 quick_exit的时候被调用。
```C++
#include <cstdlib>
#include <iostream>
using namespace std;

struct A { ~A() { cout << "Destruct A. " << endl; } };

void closeDevice() { cout << "device is closed." << endl; }

int main() {
    A a;
    at_quick_exit(closeDevice);
    quick_exit(0);
}


```



