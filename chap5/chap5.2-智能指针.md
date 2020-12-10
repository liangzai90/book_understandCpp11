
### 智能指针 

从实现上来讲， unique_ptr 是一个删除了拷贝构造函数、保留了移动构造函数的指针封装类型。

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


一段代码片段。new 一个数组
```c++
int* abc = new int[10];
	abc[0] = 0;
	abc[1] = 1;
	abc[2] = 2;
	cout <<"0:"<< abc[0] << ",1:" << abc[1] << ",2:" << abc[2] << ",3:" << abc[3] << endl;


	unique_ptr<int[]> up1(new int[10]); //无法复制的 unique_ptr
	// unique_ptr<int> up2 = up1;   //不能通过编译
	up1[1] = 11;
	up1[2] = 22;
	up1[3] = 33;

	cout << "1:" << up1[1] << ",2:" << up1[2] << ",3:" << up1[3] << ",4:" << up1[4] << endl;


```



### 注意 weak_ptr 的用法
```
#include <iostream>
#include <memory>
using namespace std;

/*
shared_ptr 形如其名，允许多个该智能指针共享地“拥有”同一堆分配对象的内存。
与unique_ptr不同的是，由于在实现上采用了引用计数，所以一旦一个shared_ptr指针放弃了“所有权”*（失效），
其他的shared_ptr对 对象内存的引用并不会受到影响。

weak_ptr可以指向shared_ptr指针指向的对象内存，却并不拥有该内存。
使用 weak_ptr 成员 lock， 则可返回其指向内存的一个shared_ptr对象，
且在所指对象内存已经无效时，返回指针空值（nullptr）
这在验证shared_ptr智能指针的有效性上会很有作用

*/

// weak_ptr 没有影响其指向的内存的引用计数，因此可以验证 shared_ptr 指针的有效性
void Check(weak_ptr<int> &wp)
{
    shared_ptr<int> sp = wp.lock(); //转为 shared_ptr<int>
    if (sp != nullptr)
    {
        cout << "still " << *sp << endl;
    }
    else
    {
        cout << "pointer is invalid." << endl;
    }
}

int main()
{
    shared_ptr<int> sp1(new int(22));
    shared_ptr<int> sp2 = sp1;
    weak_ptr<int> wp = sp1; //指向 shared_ptr<int> 所指对象

    cout << *sp1 << endl; //22
    cout << *sp2 << endl; //22
    Check(wp);            // still 22

    sp1.reset();
    cout << *sp2 << endl; //22
    Check(wp);            //still 22

    sp2.reset();
    Check(wp); //pointer is invalid

    return 0;
}


```

