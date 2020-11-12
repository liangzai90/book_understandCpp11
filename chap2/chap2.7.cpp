#include <iostream>
using namespace std;

struct Mem
{
    Mem() { cout << "Mem default, num:" << num << ",num2:" << num2 << ",valc:" << valc << endl; }
    Mem(int i) : num(i) { cout << "Mem, num:" << num << endl; }
    int num = 2; //使用=初始化非静态成员
    double num2 = 1.234;
    char valc = 'a';
};

class Group
{
public:
    Group()
    {
        cout << "Group default. val:" << val << endl;
    }
    Group(int i) : val('G'), a{i} { cout << "Group. val: " << val << endl; };

    void NumOfA() { cout << "number of A: " << a.num << endl; }
    void NumOfB() { cout << "number of B: " << b.num << endl; }

private:
    char val{'g'}; //使用 {} 初始化非静态成员
    Mem a;
    Mem b{19}; //使用 {} 初始化非静态成员
};

/**
 * 就地初始化 和 初始化列表 
 * 在C++11中，标准允许非静态成员变量的初始化有多种。具体而言，除了初始化列表外，在C++11中，标准还允许使用等号=或者花括号{}进行就地的非静态成员变量初始化
 * 例如：
 * struct  inti{
 *  int a=1;
 * double b{1.2}
 * };
 * 这在C++11中是一个合法的结构体声明。
 * 
 * 注意：
 * 圆括号()，一般只用于初始化列表的时候，给变量赋值
 * 花括号{}，集合列表的形式，范围很广，可以就地赋值
 * 
 * 相对于传统的初始化列表，在类声明中对非静态成员变量进行就地列表初始化可以降低程序员的工作量。
 * 初始化列表总是看起来“后作用于”非静态成员。也就是说，如果一个遍历就地赋值了，也在初始化列表赋值了，那么他最终的值是初始化列表的值！！！
 * 初始化列表的效果总是优先于就地初始化。
 * 
 */

void list2_7()
{
    Mem member; //Mem default, num:2
    cout << "=========================================" << endl;

    Group group; //  Mem default, num: 2
                 // Mem, num: 19
                 //Group default. val:g
    cout << "=========================================" << endl;

    group.NumOfA(); // number of A:2
    cout << "=========================================" << endl;
    group.NumOfB(); //number of B:19
    cout << "=========================================" << endl;

    Group group2(7); //Mem, num: 7
                     //Mem, num: 19
                     //Group. val: G
    cout << "=========================================" << endl;

    group2.NumOfA(); //number of A: 7
    cout << "=========================================" << endl;
    group2.NumOfB(); //number of B: 19
    cout << "=========================================" << endl;
}

int main()
{
    list2_7();

    return 0;
}

//编译选项：  g++ -std=c++11 chap2.7.cpp
