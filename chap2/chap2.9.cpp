#include <iostream>
using namespace std;
//friend在模板中的使用； 一个测试用例的代码展示
#define UNIT_TEST abc

template <typename T>
class DefenderT
{
public:
    friend T;
    void Defence(int x, int y){};
    void Tackle(int x, int y){};

private:
    int pos_x = 15;
    int pos_y = 0;
    int speed = 2;
    int stamina = 120;
};

template <typename T>
class AttackerT
{
public:
    friend T;
    void Move(int x, int y){};
    void SpeedUp(float ratio){};

private:
    int pos_x = 0;
    int pos_y = -30;
    int speed = 3;
    int stamina = 100;
};

using Defender = DefenderT<int>; //普通的类定义，使用int做参数
using Attacker = AttackerT<int>;

#ifdef UNIT_TEST
class Validator;
using DefenderTest = DefenderT<Validator>; //测试专用定义， validator类为友元
using AttackerTest = AttackerT<Validator>;

class Validator
{
public:
    void Validate(int x, int y, DefenderTest &d){};
    void Validate(int x, int y, AttackerTest &a){};
};

int main()
{
    DefenderTest d;
    AttackerTest a;
    a.Move(15, 30);
    d.Defence(15, 30);
    a.SpeedUp(1.5f);
    d.Defence(15, 30);
    Validator v;
    //通过友元的方式，可以访问 DefenderTest 里面的方法
    v.Validate(7, 0, d);
    //通过友元的方式，可以访问 AttackerTest 里面的方法
    v.Validate(1, -10, a);

    return 0;
}

#endif

//编译选项：  g++ -std=c++11 chap2.9.cpp
