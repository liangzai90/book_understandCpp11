
初识 lambda 函数 （匿名函数）

```C++
#include <iostream>
using namespace std;

int main()
{
    int girls = 3, boys = 4;
    auto totalChild = [](int x, int y )->int{return x+y;};

    cout<< totalChild(girls, boys)<<endl;
    return 0;
}

```























