
仿函数简单地说，就是重定义了成员函数 operator() 的一种自定义类型对象。

```C++
class _functor {
public: 
    int operator()(int x, int y) { return x + y; }
};

int main(){
    int girls = 3, boys = 4;
    _functor totalChild;
    return totalChild(5, 6);
}

```


仿函数和lambda函数比较
```C++
class AirportPrice{
private:
    float _dutyfreerate;
public: 
    AirportPrice(float rate): _dutyfreerate(rate){}
    float operator()(float price) { 
        return price * (1 - _dutyfreerate/100); 
    }
};

int main(){
    float tax_rate = 5.5f;
    AirportPrice Changi(tax_rate);

    auto Changi2 = 
        [tax_rate](float price)->float{ return price * (1 - tax_rate/100); };

    float purchased = Changi(3699);

    float purchased2 = Changi2(2899);
}

```















