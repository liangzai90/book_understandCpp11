
### decltype 推导【规则3】的解释

```txt
规则3带来的左值引用的推导

一个简单的能够让编译器提示的方法是，
如果使用decltype定义变量，那么闲声明这个变量，再在其他语句里面对齐进行初始化。
这样一来，由于左值引用总是需要初始化的，编译器会报错提示。
另外一些时候，C++11标准库中添加的模板类 is_lvalue_reference，可以帮助程序员进行一些推导结果的识别。
```


```C++
#include <type_traits>
#include <iostream>
using namespace std;

int i = 4;
int arr[5] = {0};
int *ptr = arr;

int && RvalRef();

int main(){
    cout << is_rvalue_reference<decltype(RvalRef())>::value << endl;    // 1

    cout << is_lvalue_reference<decltype(true ? i : i)>::value << endl; // 1
    cout << is_lvalue_reference<decltype((i))>::value << endl;          // 1
    cout << is_lvalue_reference<decltype(++i)>::value << endl;          // 1
    cout << is_lvalue_reference<decltype(arr[3])>::value << endl;       // 1
    cout << is_lvalue_reference<decltype(*ptr)>::value << endl;         // 1
    cout << is_lvalue_reference<decltype("lval")>::value << endl;       // 1

    cout << is_lvalue_reference<decltype(i++)>::value << endl;          // 0
    cout << is_rvalue_reference<decltype(i++)>::value << endl;          // 0
}
```

```txt
我们使用了模板类 is_lvalue_reference 的成员 value 来查看decltype的效果（1表示是左值引用，0则反之）。
正如我们缩减，代码清单中凡是符合规则3的，都会被推导为左值引用。
如果程序员在程序的书写中不是非常确定decltype是否将类型推导为左值引用，可以通过这样的小实验辅助确定。
这里还使用了函数 is_rvalue_referencec，同样，程序员可以通过它来确定decltype是否推导出了右值引用。
```



