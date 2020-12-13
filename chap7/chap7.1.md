

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

    return 0;
}
```



