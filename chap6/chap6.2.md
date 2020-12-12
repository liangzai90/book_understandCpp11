
### 变长模板：模板参数包和函数参数包

```C++
#include <iostream>
using namespace std;

template <long... nums> struct Multiply;

template <long first, long... last>
struct Multiply<first, last...> {
    static const long val = first * Multiply<last...>::val;
};

template<>
struct Multiply<> {
    static const long val = 1;
};

int main() {
    cout << Multiply<2, 3, 4, 5>::val << endl;          // 120
    cout << Multiply<22, 44, 66, 88, 9>::val << endl;   // 50599296
    return 0;
}

```


### 进阶

  只适合例子中的书写格式，再增加 %d，这种写法就 不行了 

```c++
#include <iostream>
#include <stdexcept>
using namespace std;

void Printf(const char* s) {
    while (*s) {
        if (*s == '%' && *++s != '%')
            throw runtime_error("invalid format string: missing arguments");
                cout << *s++;
    }
}

template<typename T, typename... Args>
void Printf(const char* s, T value, Args... args) {
    while (*s) {
        if (*s == '%' && *++s != '%') {
            cout << value;
            return Printf(++s, args...);
        }
        cout << *s++;
    }
    throw runtime_error("extra arguments provided to Printf");
}

int main() {
    Printf("hello %s\n", string("world"));  // hello world
}


```














