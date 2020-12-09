
### 智能指针 


```c++
#include <memory>
#include <iostream>
using namespace std;

/**
C++11标准中的智能指针：
unique_ptr
shared_ptr
weak_ptr
*/
// 智能指针的例子

int main()
{
    unique_ptr<int> up1(new int(11)); //无法复制的 unique_ptr
    // unique_ptr<int> up2 = up1;   //不能通过编译

    cout << "*up1:" << *up1 << endl; //11

    unique_ptr<int> up3 = move(up1); //现在 up3 是数据唯一的 unique_ptr 智能指针
    cout << "*up3:" << *up3 << endl; //11
                                     //    cout << "*up1:" << *up1 << endl; //运行时错误
    up3.reset();                     //显示释放内存
    up1.reset();                     //不会导致运行时错误
                                     //  cout << "*up3:" << *up3 << endl; //运行时错误

    cout << "======================================" << endl;
    shared_ptr<int> sp1(new int(22));
    shared_ptr<int> sp2 = sp1;
    cout << "sp1:" << *sp1 << endl; //22
    cout << "sp2:" << *sp2 << endl; //22

    sp1.reset();
    cout << "*sp2:" << *sp2 << endl; //22

    return 0;
}

```
