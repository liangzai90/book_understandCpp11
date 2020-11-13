#include <iostream>
using namespace std;

struct People
{
public:
    int hand;
    static People *all;
};

/**非静态成员的sizeof*/
void list2_18()
{
    People p;
    cout << sizeof(p.hand) << endl;       //C++98 中通过，C++11 中通过
    cout << sizeof(People::all) << endl;  //C++98 中通过，C++11 中通过
    cout << sizeof(People::hand) << endl; //C++98 中错误，C++11 中通过

    //这里我们强制转换0为一个People类的指针，继而通过指针的解引用获得其成员变量，并用sizeof求得该成员变量的大小。
    //在C++11中不需要这样的技巧，因为sizeof可以作用的表达式包括了类成员表达式。
    //C++98中通过强转实现
    cout << sizeof(((People *)0)->hand) << endl;
}

/**扩展的friend语法*/
class Poly;
typedef Poly P;
class LiLei
{
    friend class Poly; //C++98 通过，C++11 通过
};
class Jim
{
    friend Poly; //C++98 失败，C++11 通过
};
class HanMeiMei
{
    friend P; //C++98 失败，C++11 通过
};

//在C++11中，程序可以为类模板声明友元了。

class P2;
template <typename T>
class People2
{
    friend T;
};
void list2_20()
{
    People2<P2> PP;  //类型P2在这里是People2类型的友元
    People2<int> Pi; //对于int类型模板参数，友元声明被忽略
}

int main()
{
    list2_18();
    list2_20();

    return 0;
}

//编译选项：  g++ -std=c++11 chap2.8.cpp
