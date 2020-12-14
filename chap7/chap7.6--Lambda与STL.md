

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






传统for,内置functor，lambda函数比较
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











