
decltype 的模板用法

```C++
enum class{K1, K2, K3}anon_e;   // 匿名的强类型枚举

union {
    decltype(anon_e) key;
    char* name;
}anon_u;    // 匿名的union

struct {
    int d;
    decltype(anon_u) id;
}anon_s[100];   // 匿名的struct数组


int main() {
    decltype(anon_s) as;
    as[0].id.key = decltype(anon_e)::K1;   // 引用匿名强类型枚举中的值
}

```



decltype 的模板用法
```C++
// s的类型被声明为decltype(t1 + t2)
template<typename T1, typename T2>
void Sum(T1 & t1, T2 & t2, decltype(t1 + t2) & s) {
    s = t1 + t2;
}

int main() {
    int a = 3;
    long b = 5;
    float c = 1.0f, d = 2.3f;

    long e;
    float f; 
    Sum(a, b, e);   // s的类型被推导为long
    Sum(c, d, f);   // s的类型被推导为float
}

```
