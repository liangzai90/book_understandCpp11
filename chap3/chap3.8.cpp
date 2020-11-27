// forward 完美转发 的例子

#include <iostream>
using namespace std;

void RunCode(int &&m) { cout << "rvalue ref" << endl; }
void RunCode(int &m) { cout << "lvalue ref" << endl; }
void RunCode(const int &&m) { cout << "const rvalue ref" << endl; }
void RunCode(const int &m) { cout << "const lvalue ref" << endl; }

template <typename T>
void PerfectForward(T &&t) { RunCode(forward<T>(t)); }

int main()
{
    int a;
    int b;
    const int c = 1;
    const int d = 0;

    PerfectForward(a);       // lvalue ref
    PerfectForward(move(b)); // rvalue ref
    PerfectForward(c);       // const lvalue ref
    PerfectForward(move(d)); // const rvalue ref
}

//  g++ -std=c++11 chap3.7.cpp

