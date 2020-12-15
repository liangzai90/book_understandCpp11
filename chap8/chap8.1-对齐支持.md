
#### 数据对齐

alignof操作符查看对齐方式,
alignas修饰符修饰对齐方式

在使用常量表达式作为alignas的操作符的时候，其结果必须是2的自然数幂次作为对齐值。
对齐值越大，我们称其对齐要求越高；
而对齐值越小，其对齐要求也越低。

```C++

#include <iostream>
using namespace std;

struct HowManyBytes
{
    char a;
    int b;
    int c;
    int d;
};

struct ColorVector
{
    double r;
    double g;
    double b;
    double a;
};

//利用C++11新提供的修饰符 alignas来重新设定对齐方式
//自定义ColorVector2，对齐到32字节的边界
struct alignas(32) ColorVector2
{
    double r;
    double g;
    double b;
    double a;
};

int main()
{
    cout << "sizeof(char): " << sizeof(char) << endl;
    cout << "sizeof(short): " << sizeof(short) << endl;
    cout << "sizeof(unsigned short): " << sizeof(unsigned short) << endl;
    cout << "sizeof(int): " << sizeof(int) << endl;
    cout << "sizeof(unsigned int): " << sizeof(unsigned int) << endl;
    cout << "sizeof(long long): " << sizeof(long long) << endl;
    cout << "sizeof(long long int): " << sizeof(long long int) << endl;
    cout << "sizeof(float): " << sizeof(float) << endl;
    cout << "sizeof(double): " << sizeof(double) << endl;
    cout << "sizeof(long double): " << sizeof(long double) << endl;
    cout << "sizeof(HowManyBytes): " << sizeof(HowManyBytes) << endl;

    cout << endl;
    cout << "offset of char a: " << offsetof(HowManyBytes, a) << endl;
    cout << "offset of int b: " << offsetof(HowManyBytes, b) << endl;
    cout << "offset of int c: " << offsetof(HowManyBytes, c) << endl;
    cout << "offset of int d: " << offsetof(HowManyBytes, d) << endl;

    // C++11 标准定义的 alignof 函数可以查看对齐方式
    cout << "alignof(HowManyBytes):" << alignof(HowManyBytes) << endl;
    cout << "alignof(ColorVector):" << alignof(ColorVector) << endl;
    cout << "alignof(ColorVector2):" << alignof(ColorVector2) << endl;
    return 0;
}

// sizeof(char): 1
// sizeof(short): 2
// sizeof(unsigned short): 2
// sizeof(int): 4
// sizeof(unsigned int): 4
// sizeof(long long): 8
// sizeof(long long int): 8
// sizeof(float): 4
// sizeof(double): 8
// sizeof(long double): 16
// sizeof(HowManyBytes): 16

// offset of char a: 0
// offset of int b: 4
// offset of int c: 8
// offset of int d: 12
// alignof(HowManyBytes):4
// alignof(ColorVector):8
// alignof(ColorVector2):32

```

















