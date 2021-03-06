

### 认识 指针空值 nullptr

void*  无类型指针

nullptr  指针空值 

```C++
#include <iostream>
using namespace std;

void f(char* p)
{
    cout <<"invoke f(char*)"<<endl;
}

void f(int){
    cout <<"invoke f(int)"<<endl;
}


int main() {
    f(nullptr);  //调用 f(char*) 版本
    f(0);     //调用 f(int) 版本
cout <<"sizeof(nullptr):"<<sizeof(nullptr)<<endl; // 8
    return 0;
}
```

### nullptr 和 void* 的讨论
```
nullptr 是一个编译时期的常量，它的名字是一个编译时期的关键字，能够为编译器所识别。
而 (void*)0 只是一个强制转换表达式，其返回的也是一个 void* 指针类型。

  而且最为重要的是，在C++语言中，nullptr 到任何指针的转换都是隐式的，
而 (void*)0 则必须经过类型转换后才能使用。
```

```C++

#include <cstdio>
#include <cstddef>
using namespace std;

int main(){
    nullptr_t my_null;
    printf("%x\n", &my_null);

    // printf("%x", &nullptr);      // 根据C++11的标准设定，本句无法编译通过
    printf("%d\n", my_null == nullptr);

    const nullptr_t && default_nullptr = nullptr;    // default_nullptr是nullptr的一个右值引用
    printf("%x\n", &default_nullptr);

    const nullptr_t && default_nullptr2 = nullptr;    // default_nullptr是nullptr的一个右值引用
    printf("%x\n", &default_nullptr2);
}

```










