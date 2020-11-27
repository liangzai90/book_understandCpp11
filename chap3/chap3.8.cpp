#include <iostream>
using namespace std;

//forward结合模板，实现函数包装
template <typename T, typename U>
void PerfectForward(T &&t, U &Func)
{
    cout << t << "\tforwarded..." << endl;
    //TODO: 包装后的函数
    Func(forward<T>(t));
}

void RunCode(double &&m) { cout << "para is:" << m << endl; }
void RunHome(double &&h) { cout << "para is:" << h << endl; }
void RunComp(double &&c) { cout << "para is:" << c << endl; }

int main()
{
    PerfectForward(1.5, RunComp); // 1.5     forwarded...
    PerfectForward(8, RunCode);   // 8       forwarded...
    PerfectForward(1.5, RunHome); // 1.5     forwarded...
}

// make_pair, make_unique 等都利用了完美转发
