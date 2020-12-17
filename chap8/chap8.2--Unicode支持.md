
#### C++11定义了一些常量字符串的前缀
 - > u8 表示为 UTF-8 编码
 - > u 表示为 UTF-16 编码
 - > U 表示为 UTF-32 编码
 - > 基于宽字符 wchar_t 的前缀 "L"

对于Unicode编码字符的书写，C++11中还规定了一些简明的方式，
即在字符串中用 '\u' 加4个十六进制数编码的 Unicode 码位（UTF-16）来标识一个Unicode字符。
比如 '\u4F60' 表示的就是Unicode中的中文字符“你”，
而 '\u597D' 则是 Unicode 中的“好”。
此外，也可以通过 '\U' 后跟8个十六进制数编码的 Unicode 码位（UTF-32）的方式来书写 Unicode 字面常量。



美国用了英文和UTF-8编码，这样的local可以表示为 en_US.UTF-8

中国使用简体中并文采用GB2312文字编码的local则表示为 zh_CN.GB2312



通过 has_facet 来查询该 locale 在本机上的支持情况
```C++
#include <iostream>
#include <locale>
using namespace std;

int main()
{
    // 定义一个locale并查询该locale是否支持一些facet
    locale lc("en_US.UTF-8");
    bool can_cvt = has_facet<codecvt<wchar_t, char, mbstate_t>>(lc);
    if (!can_cvt)
        cout << "Do not support char-wchar_t facet!" << endl;

    can_cvt = has_facet<codecvt<char16_t, char, mbstate_t>>(lc);
    if (!can_cvt)
        cout << "Do not support char-char16 facet!" << endl;

    can_cvt = has_facet<codecvt<char32_t, char, mbstate_t>>(lc);
    if (!can_cvt)
        cout << "Do not support char-char32 facet!" << endl;

    can_cvt = has_facet<codecvt<char, char, mbstate_t>>(lc);
    if (!can_cvt)
        cout << "Do not support char-char facet!" << endl;

    return 0;
}


```


通过一些设定，让 stream 自动进行一些编码的转换
```C++

#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <iomanip>
using namespace std;

int main()
{
    // UTF-8字符串, "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9d\x84\x8b";
    ofstream("text.txt") << u8"z\u00df\u6c34\U0001d10b";

    wifstream fin("text.txt");
    // 该locale的facet - codecvt<wchar_t, char, mbstate_t>
    // 可以将UTF-8转化为UTF-32
    fin.imbue(locale("en_US.UTF-8"));

    cout << "The UTF-8 file contains the following wide characters: \n";
    for (wchar_t c; fin >> c;)
        cout << "U+" << hex << setw(4) << setfill('0') << c << '\n';
}

// The UTF-8 file contains the following wide characters:
// U+007a
// U+00df
// U+6c34
// U+1d10b

```




```
wstring_convert
codecvt_utf8
codecvt_utf16

```

