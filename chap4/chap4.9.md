
### 基于范围的 for 循环


```c++
#include <algorithm>
#include <iostream>

using namespace std;

int action1(int &e) { e *= 2; }
int action2(int &e) { cout << e << '\t'; }

// int func(int a[])
// {
//     for (auto e : a)
//     {
//         cout << e << " ";
//     }
// }

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    //todo   for_each
    for_each(arr, arr + sizeof(arr) / sizeof(arr[0]), action1);

    for_each(arr, arr + sizeof(arr) / sizeof(arr[0]), action2);

    cout << endl;

    // func(arr)   会报错，因为参数a的数组范围不确定

    // 基于范围的 for
    for (auto &e : arr)
    {
        e++; //如果要修改数组，需要使用 &
    }

    for (auto e : arr)
    {
        cout << e << " ";
    }

    cout << endl;
    return 0;
}

// g++ -std=c++11 chap4.8.cpp

```
