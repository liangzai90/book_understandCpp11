#include <iostream>
using namespace std;

//浅拷贝示例
//这样的构造方式称为  浅拷贝 shollow copy.在未声明构造函数的情况下，C++也会为类生成一个浅拷贝的构造函数。
//通常解决方案是用户自定义拷贝构造函数实现“深拷贝 deep copy”
class HasPtrMem
{
public:
    HasPtrMem() : d(new int(0)) { cout << "construct default 111" << endl; };
    //这里的拷贝构造函数由编译器隐式生成，其作用是执行类似于memcpy的按位拷贝。这样的构造方式有一个问题，就是a.d和b.d都指向了同一块堆内存。
    ~HasPtrMem() { delete d; }
    int *d;
};  //运行会报错，d被析构了2次


//深拷贝示例
//用户自定义拷贝构造函数
//拷贝构造函数从堆中分配新内存，将该分配来的内存的指针交换给d，又使用 *(h.d) 对 *d 进行了初始化
//通过这样的方法，就避免了悬挂指针的困扰
// class HasPtrMem
// {
// public:
//     HasPtrMem() : d(new int(0)) { cout << "construct default 333" << endl; };
//     HasPtrMem(const HasPtrMem &h) : d(new int(*h.d)) { cout << "construct zidingyi 444" << endl; };
//     ~HasPtrMem() { delete d; }
//     int *d;
// };

int main()
{
    HasPtrMem a;
    HasPtrMem b(a);
    cout << "-------------------------------" << endl;

    cout << "dddddd" << endl;
    cout << a.d << endl;
    cout << b.d << endl;

    cout << *b.d << endl;
    cout << *a.d << endl;
    ///   getchar();
}

//  g++ -std=c++11  chap3.4.cpp
