### final / override 控制

```txt
final 使得父类的函数不可以被子类重载
虚函数也可以用final修饰，不过那样就失去了虚函数的意义了。
final 通常只在继承关系的“中途”终止派生类的重载中有意义。
从接口的角度而言，final可以在派生过程中任意地阻止一个接口的可重载性，这就给面向对象的程序员带来了更大的控制力。
```

```cpp
struct Object
{
    virtual void fun() = 0;
};

struct Base : public Object
{
    void fun() final; //声明为 final
};

struct Derived : public Base
{
    void fun(); //无法通过编译...编辑阶段就报错了！！！
};
```


```txt
在C++中重载还有有个特点，就是对基类声明为 virtual 的函数，之后的重载版本都不需要再声明该重载函数为virtual。、
书写便利了，但是会带来一些阅读上的困难。
在C++11中为了帮助程序员写继承结构复杂的类型，引入了虚函数描述符 override，如果派生类在虚函数声明时使用了 override 描述符，
那么该函数必须重载其积累中的同名函数，否则代码将无法通过编译。
```


```cpp
struct Base
{
    virtual void Turing() = 0;
    virtual void Dijkstra() = 0;
    virtual void VNeumann(int g) = 0;
    virtual void DKnuth() const;
    void Print();
};

struct DerivedMid : public Base
{
    // void VEnumann(double g);
    //接口被隔离了，曾想多一个版本的 VNeumann 函数
};

struct DerivedTop : public DerivedMid
{
    void Turing() override;

    //TODO:如果没有 override 修饰符，下面4类错误发现不了
    void Dikjstra() override;       //无法通过编译，拼写错误，并非重载
    void VNeumann(double) override; //无法通过编译，参数不一致，并非重载
    void DKnuth() override;         //无法通过编译，常量性不一致，并非重载
    void Print() override;          //无法通过编译，非虚函数重载
};
```

```txt
final/override可以定义为正常变量名，只有在其出现在函数后时才是能够控制继承/派生的关键字。
建议在C++11中应该尽可能避免这样的变量名称或将其定义在宏中，以防发生不必要的错误。
```
