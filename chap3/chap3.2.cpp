#include <iostream>
#include <string>
using namespace std;

// 委派 构造函数
class Info
{
public:
    Info() { InitRest(); }

    //委派构造函数不能有初始化列表，只能在函数体中为type,name等成员赋初值
    Info(int i) : Info() { type = i; }
    Info(char e) : Info() { name = e; }

    //我们不能在初始化列表中既初始化成员，又委托其他构造函数完成构造
    //todo:无法通过编译
    //Info(int a, int b) : Info(), a(0){};

private:
    void InitRest(){/*其他 初始化*/};
    int type{1};    //C++11的就地初始化
    char name{'a'}; //C++11的就地初始化
};

// 委派 构造函数2..在委派构造函数里面初始化若干成员变量
class Info2
{
public:
    Info2() : Info2(1, 'a') {}
    Info2(int i) : Info2(i, 'a') {}
    Info2(char e) : Info2(1, e) {}

private:
    Info2(int i, char e) : type(i), name(e){/*其他 初始化*/};
    int type;  //C++11的就地初始化
    char name; //C++11的就地初始化
};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
