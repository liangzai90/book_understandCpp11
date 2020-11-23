#include <iostream>
using namespace std;

class HasPtrMem
{
public:
    HasPtrMem() : d(new int(0))
    {
        cout << "Construct: " << ++n_cstr << endl;
    }
    HasPtrMem(const HasPtrMem &h) : d(new int(*h.d))
    {
        cout << "Copy construct: " << ++n_cpstr << endl;
    }

    //TODO:注意这里的参数类型 &&
    //TODO:移动构造函数，接受一个所谓的“右值引用”的参数
    HasPtrMem(HasPtrMem &&h) : d(h.d)
    {

        //1. d=h.d ， d指向h.d指向的内容
        //2. h.d=nullptr, 将h.d指向一个空地址，h.d析构的时候，就不会析构之前的堆内存了

        //移动构造函数，将临时值的指针成员置空
        h.d = nullptr; //如果不改变h.d的话，则临时对象会析构本是我们“偷”来的堆内存。这样一来，本对象d指针就成了一个悬挂指针
        cout << "Move construct" << ++n_mvstr << endl;
    }

    ~HasPtrMem()
    {
        delete d;
        cout << "Destruct: " << ++n_dstr << endl;
    }

    int *d;
    static int n_cstr;
    static int n_dstr;
    static int n_cpstr;
    static int n_mvstr;
};

int HasPtrMem::n_cstr = 0;
int HasPtrMem::n_dstr = 0;
int HasPtrMem::n_cpstr = 0;

HasPtrMem GetTemp()
{
    HasPtrMem h;
    cout << "Resource from " << __func__ << ": " << hex << h.d << endl;
    return h;
}

int main()
{
    HasPtrMem a = GetTemp();
    cout << "Resource from" << __func__ << ": " << hex << a.d << endl;
}

//  g++ -std=c++11 chap3.5.cpp
