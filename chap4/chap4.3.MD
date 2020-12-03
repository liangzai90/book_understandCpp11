
```c++
#include <iostream>
#include <typeinfo>
using namespace std;

class White
{
};
class Black
{
};

int main()
{
    White a;
    Black b;

    cout << typeid(a).name() << endl; // 5White
    cout << typeid(b).name() << endl; // 5Black

    White c;

    bool a_b_sametype = (typeid(a).hash_code() == typeid(b).hash_code());
    bool a_c_sametype = (typeid(a).hash_code() == typeid(c).hash_code());

    cout << "Same type? " << endl;
    cout << "A and B? " << (int)a_b_sametype << endl; // 0
    cout << "A and C? " << (int)a_c_sametype << endl; // 1
}
```


```C++
#include <typeinfo>
#include <iostream>
using namespace std;

int main() {
    int i;
    decltype(i) j = 0; 
    cout << typeid(j).name() << endl;   // 打印出"i", g++表示integer

    float a;
    double b;
    decltype(a + b) c;
    cout << typeid(c).name() << endl;   // 打印出"d", g++表示double
}

```


decltype 的用法 
```C++
#include <vector>
using namespace std;

int main() {
    vector<int> vec;
    typedef decltype(vec.begin()) vectype;

    vectype i;  // 这是auto无法做到的
    for (i = vec.begin(); i < vec.end(); i++) {
        // 做一些事情
    }

    for (decltype(vec)::iterator i = vec.begin(); i < vec.end(); i++) {
        // 做一些事情
    }
}
```



