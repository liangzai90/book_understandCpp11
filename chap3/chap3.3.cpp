#include <iostream>
#include <vector>
#include <list>
#include <deque>
using namespace std;

//委派构造函数的一个很实际的应用就是使用构造模板函数产生目标构造函数
//委派构造使得构造函数的范型编程成为了一种可能
// class TDConstructed2
// {
//     template <class T>
//     TDConstructed2(T first, T last) : l(first, last){};
//     list<int> l;

// public:
//     TDConstructed2(vector<short> &v) : TDConstructed2(v.begin(), v.end()) { cout << "vec2 construct" << endl; };
//     TDConstructed2(deque<int> &d) : TDConstructed2(d.begin(), d.end()) { cout << "deq2 construct " << endl; };
// };

class TDConstructed
{
    template <class T>
    TDConstructed(T first, T last) : l(first, last) {}
    list<int> l;

public:
    TDConstructed(vector<short> &v) : TDConstructed(v.begin(), v.end()) { cout << "vec construct" << endl; }
    TDConstructed(deque<int> &d) : TDConstructed(d.begin(), d.end()) { cout << "deq construct " << endl; }
};

//在异常处理方面，如果在委派构造函数中使用try的话，那么从目标构造函数中产生的异常，
//都可以在委派构造函数中被捕捉到
class DCExcept
{
public:
    DCExcept(double d)
    try : DCExcept(1, d)
    {
        cout << "Run the body." << endl;
        // 其它初始化
    }
    catch (...)
    {
        cout << "caught exception." << endl;
    }

private:
    DCExcept(int i, double d)
    {
        cout << "going to throw!" << endl;
        throw 0;
    }
    int type;
    double data;
};

int main()
{
    //模板捕获异常
    //DCExcept a(1.2);

    vector<short> vecSt;
    vecSt.push_back(12);
    vecSt.push_back(13);
    vecSt.push_back(14);

    deque<int> deqI;
    deqI.push_back(6666);
    deqI.push_back(7777);
    deqI.push_back(8888);

    TDConstructed vecOjb(vecSt);
    TDConstructed deqObj(deqI);

    return 0;
}

// g++ -std=c++11 chap3.3.cpp
