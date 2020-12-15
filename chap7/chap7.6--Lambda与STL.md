


### lambda函数配合for_each，打印容器的所有变量
特别注意这里的书写方式
```C++
    vector<int> v(10);
    generate(v.begin(), v.end(), [] {
        return rand() % 10;
    });

    // lambda函数，传入的参数是vector的一个value
    // for_each是对vector的每个元素进行一次 函数操作，这里的元素是int类型
    for_each(v.begin(), v.end(), [](int i) { cout << i << ","; });
    cout << endl;

```

#### 传统for循环，仿函数，lambda函数
```C++
#include <vector>
#include <algorithm>
using namespace std;

vector<int> nums;
vector<int> largeNums;

class LNums{
    public:
        LNums(int u): ubound(u){}

        void operator () (int i) const
        {
            if (i > ubound)
                largeNums.push_back(i);
        }
    private:
        int ubound;
};

void Above(int ubound) {
    // 传统的for循环
    for (auto itr = nums.begin(); itr != nums.end(); ++itr) {
        if (*itr >= ubound)
            largeNums.push_back(*itr);
    }

    // 使用functor
    for_each(nums.begin(), nums.end(), LNums(ubound));

    // 使用lambda函数和算法for_each
    for_each(nums.begin(), nums.end(), [=](int i){
            if (i > ubound)
                largeNums.push_back(i);
            });

}

```






#### 传统for,内置functor，lambda函数比较
lambda还是更加简洁、高效
```C++

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<int> nums;

void Add(const int val){
    auto print = [&]{
        for (auto s: nums){ cout << s << '\t'; }
        cout<< endl;
    };

    // 传统的for循环方式
    for (auto i = nums.begin(); i != nums.end(); ++i){
        *i = *i + val;
    }
    print();

    // 试一试for_each及内置functor
    for_each(nums.begin(), nums.end(), bind2nd(plus<int>(), val));
    print();

    // 实际这里我们需要使用STL的一个变动性算法：transform 
    transform(nums.begin(), nums.end(), nums.begin(), bind2nd(plus<int>(), val));
    print();

    // 不过在lambda的支持下，我们还是可以只使用for_each
    for_each(nums.begin(), nums.end(), [=](int &i){
                i += val;
            });
    print();
}


int main(){
    for (int i = 0; i < 10; i++){
        nums.push_back(i);
    }
    Add(10);
    return 1;
}

```



#### lambda更简洁，这里特别注意for_each 配合lambda函数的语法
```C++

#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric> // std::accumulate
using namespace std;

void Stat(vector<int> &v)
{
    int errors;
    int score;
    auto print = [&] {
        cout << "Errors: " << errors << endl
             << "Score: " << score << endl;
    };
    // 使用accumulate算法，需要两次循环
    errors = accumulate(v.begin(), v.end(), 0);
    score = accumulate(v.begin(), v.end(), 100, minus<int>());
    print();

    errors = 0;
    score = 100;
    // 使用lambda则只需要一次循环
    for_each(v.begin(), v.end(), [&](int i) {
        errors += i;
        score -= i;
    });
    print();
}

int main()
{
    vector<int> v(10);
    generate(v.begin(), v.end(), [] {
        return rand() % 10;
    });

    // lambda函数，传入的参数是vector的一个value
    for_each(v.begin(), v.end(), [](int i) { cout << i << ","; });
    cout << endl;

    Stat(v);
}

```


```txt
    总的来说，lambda函数被设计的目的，就是要就地书写，就地使用。
使用lambda的用户，更倾向于在一个屏幕里看到所有的代码，而不是依靠代码浏览工具在文件间找到函数的实现。
    而在封装的思维层面上，lambda只是一种局部的封装，以及局部的共享。
而需要全局共享的代码逻辑，我们则还是需要用函数（无状态）或者仿函数（有状态）封装起来。
```

#### 简单地总结一下，使用lambda代替仿函数的应该满足如下一些条件：
 - > 是局限于一个局部作用域中使用的代码逻辑
 - > 这些代码逻辑需要被作为参数传递

关于lambda函数的捕捉列表，要注意[=], [&]，不能滥用。
 * 1.[=]，所有捕捉的变量在lambda声明一开始就被拷贝，且拷贝的值不可被更改，会有一定的开销
 * 2.[&]，如果代码存在异步操作，或者其他可能改变对象的任何操作，我们必须确定其父作用域及lambda函数间的关系
通常情况下，在使用[=],[&]这些默认捕捉列表的时候，我们需要考察其性能、与父作用域如何关联等。
捕捉列表是lambda最神奇也是最容易犯错的地方，程序员不能一味图方便了事。




