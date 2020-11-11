#include <iostream>
#include <stdio.h>
#include <climits>
#include <cstdio>
//NDEBUG 必须在 <assert> 引用之前！否则无效！
//#define NDEBUG 0
#include <cassert>
#include <error.h>
#include <cstring>
using namespace std;

/**预定义宏*/
void list2_1()
{
    cout << "Standard Clib" << __STDC_HOSTED__ << endl;
    cout << "Standard C:" << __STDC__ << endl;
    cout << "ISO/IEC " << __STDC_ISO_10646__ << endl;

    //error(1, 1, "some error .top program");
}

/**__func__预定义标识符*/
const char *hello() { return __func__; }
const char *world() { return __func__; }

struct TestStruct
{
    TestStruct() : name(__func__) {}
    const char *name;
};

void list2_2()
{
    cout << hello() << ", " << world() << endl;
    TestStruct ts;
    cout << "ts.name:" << ts.name << endl; // TestStruct
}

/** _Pragma 操作符*/
void list2_3()
{
#define CONCAT(x) PRAGMA(concat on #x)
#define PRAGMA(x) _Pragma(#x)
    CONCAT(..\concat.dir)
}

/**边长参数的宏定义以及  __VA_ARGS__ */
#define LOG(...)                                               \
    {                                                          \
        fprintf(stderr, "%s: Line %d:\t", __FILE__, __LINE__); \
        fprintf(stderr, __VA_ARGS__);                          \
        fprintf(stderr, "\n");                                 \
    }
void list2_4()
{
    int x = 3;
    LOG("X=%d", x);
}

/**宽窄字符串连接*/

void list2_5()
{
    //char     窄字符串
    //wchar_t  宽字符串
}

/**long long*/
void list2_6()
{
    long long int lli = -900000000000000LL;
    unsigned long long int ulli = -90000000000000ULL;
    cout << "lli:" << lli << endl;
    cout << "ulli:" << ulli << endl;

    long long ll_min = LLONG_MIN;
    long long ll_max = LLONG_MAX;
    unsigned long long ull_max = ULLONG_MAX;

    printf("min of long  long:%lld \r\n", ll_min);          //min of long  long:-9223372036854775808
    printf("max of long long : %lld \r\n", ll_max);         //max of long long : 9223372036854775807
    printf("max of unsigned long long:%llu \r\n", ull_max); //max of unsigned long long:18446744073709551615
    //TODO: 注意，这里不能写成 %ull, 必须是 %llu
}

/**__cplusplus*/
void list2_7()
{
    //#error在编译阶段报错，一般用来做环境判断
#if __cplusplus < 201103L
#error "should use C++11 implementation";
#endif

#warning "this is a warning message"
}

/**静态断言*/
//枚举编译器对各种特性的支持，每个枚举值占一位
enum FeatureSupports
{
    C99 = 0x0001,
    ExtInt = 0x0002,
    SAssert = 0x0004,
    NoExcept = 0x0008,
    SMAX = 0x0010,
};
//一个编译器类型，包括名称、特性支持等
struct Compiler
{
    const char *name;
    int spp; //使用FeatureSupports枚举
};

template <typename T, typename U>
//bit_copy被调用，才会检查错误
int bit_copy(T &a, U &b)
{
    assert(sizeof(b) == sizeof(a));
    memcpy(&a, &b, sizeof(b)); //need include <cstring> file
}

#define assert_static(e)               \
    do                                 \
    {                                  \
        enum                           \
        {                              \
            assert_static__ = 1 / (e), \
        };                             \
    } while (0)

//模板实例化时就可以检测错误
template <typename T, typename U>
int bit_copy2(T &a, U &b)
{
    assert_static(sizeof(b) == sizeof(a));
    memcpy(&a, &b, sizeof(b)); //need include <cstring> file
}

//C++11的 static_assert ，能表达更多的意思，让调试人员更快明白报错的含义
template <typename T, typename U>
int bit_copy3(T &a, U &b)
{
    //static_assert 编译期的断言，只能检测常量。
    static_assert(sizeof(b) == sizeof(a), "the parameters of bit_copy3 must have same width.");
    memcpy(&a, &b, sizeof(b)); //need include <cstring> file
}

char *list2_8(int n)
{
    //检查枚举值是否完备
    assert((SMAX - 1) == (C99 | ExtInt | SAssert | NoExcept));
    Compiler a = {"abc", (C99 | SAssert)};
    //...
    if (a.spp & C99)
    {
        cout << "list2_8 output " << endl;
    }

    int b = 0x2468;
    int d = 0x2469;
    double c;
    //    bit_copy(b, c);
    //    bit_copy2(b, d);
    //bit_copy2(b, c);
    bit_copy3(b, c);

    //一个简单的堆内存数组分配函数
    assert(n > 0); //断言，n必须大于0
    return new char[n];
}

int main()
{
    list2_1();
    list2_2();
    list2_4();
    list2_6();
    list2_7();
    char *a = list2_8(1);

    return 0;
}

//编译选项：  g++ -std=c++11 chap2.1.cpp
