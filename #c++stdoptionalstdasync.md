# c++/std::optional/std::async



[TOC]

## std::optional

<https://blog.csdn.net/janeqi1987/article/details/100567933>

针对可能返回/传递/使用某种类型的对象，即，我们可以有某个类型的值，也可以没有任何值。

因此，需要一种方法来模拟类似指针的语义，在指针中，使用nullptr来表示没有值。



**解决方法** 定义一个特定类型的对象，并用一个额外的布尔成员/标志来表示值是否存在。



std::optional对象只是包含对象的内部内存加上一个布尔标志。**大小通常比包含的对象大一个字节**

它不仅仅是向值成员添加布尔标志功能的结构。如果没有值，就不会为所包含的类型调用构造函数，可以为对象提供没有值的默认状态。



```cpp
#include <iostream>
#include <string>
#include <optional>
using namespace std;
class Name
{
private:
  string first;
  optional<string>middle;
  string last;
  
public:
  Name(string f,optional<string>m,string l):first{move(f)},midddle{move(m)},last{move(l)}{}//另外一种语义构造函数的方法，移动构造
  friend ostream& operator<<(ostream& strm,const Name& n)
  {
    strm<<n.first<<' ';
    if (n.middle) {//可以判断成员数据是否存在，bool，是否有值
            strm << n.middle.value() << ' ';
        }
        return strm << n.last;
  }
};


int main(){
  Name n{ "Jim", std::nullopt, "Knopf" };
    std::cout << n << '\n';
    Name m{ "Donald", "Ervin", "Knuth" };
    std::cout << m << '\n';
 
    return 0;

}
```



类Name表示由一个名字，可选的中间名，姓氏组成。成员中间被定义为std::optional<>，当没有中间名字时构造函数允许传递std::nullopt参数，这与中间名称为空字符串的状态不同。



    注意，对于具有值语义的类型，定义初始化相应成员的构造函数的最佳方法是按值获取参数并将参数移动到成员。

 

  还要注意，std::optional<>改变了对成员中间值的访问。使用middle作为布尔表达式可以判断是否有中间名，如果有的话可以使用value()方法来获取值。



    另外一种访问optional值的方法是用一个成员函数value_or()，该方法如果不存在值，则允许指定的值。例如，在类名内部我们也可以实现:

```cpp
std::cout << middle.value_or(""); // print middle name or nothing
```




### std::optional<>类型和操作

本节详细描述std::optional<>的类型和操作。

####1.2.1 std::optional<>类型

    在标准库的头文件<optional>中定义了std::optional<>如下；
    namespace std 
    {
    template<typename T> class optional;
    }


此外，定义了类型和对象如下：

**std::nullopt_t**类型的**nullopt**是一种没有值的对象；
异常类std::bad_optional_access，派生自std:: Exception，用于std::optional<>对象没有值的情况下访问是抛出的异常。
可选对象还使用<utility>中定义的对象std::in_place(类型为std::in_place_t)来初始化带有多个参数的可选对象的值(参见下面)。

#### 1.2.2 std::optional<>操作

下面std::optional操作列出了为std::optional<>提供的所有操作：

```cpp
std::optional的成员定于
 成员定义	                说明
constructors	     创建一个optional对象(可能调用包含类型的构造函数)
make_optional<>()	 创建一个optional对象(传递值来初始化它)
destructor	       销毁一个optional对象
=	                 分配一个新值
emplace()	         为所包含的类型分配一个新值
reset()	           销毁任何值(使对象为空)
has_value()	        返回对象是否具有值
conversion to bool	返回对象是否具有值

*                    访问值(如果没有值，则未定义行为)
->	                访问值的成员(如果没有值，则为未定义的行为)
value()	            访问值(如果没有值，则抛出异常)
value_or()	        访问值(如果没有值，则使用提供的值)
swap()	            交换两个对象的值
==, !=, < , <=, >, >=	比较两个optional对象
hash<>	              函数对象类型来计算哈希值
  
```

#### 构造函数

​    特殊构造函数允许将参数直接传递给所包含的类型。

**从以下赋值语法来看，用值构造初始化使用的是{},或std::optional<int> o2(std::nullopt);这种形式**

可以创建一个没有值的可选对象。在这种情况下，必须指定包含的类型:

```cpp
std::optional<int> o1;
std::optional<int> o2(std::nullopt);
这里不会为所包含的类型调用任何构造函数。
```



**可以传递一个值来初始化所包含的类型。根据推导指南，不必指定所包含的类型**，如下:

```cpp
std::optional o3{42}; // deduces optional<int>
std::optional<std::string> o4{"hello"};
std::optional o5{"hello"}; // deduces optional<const char*>
```


要初始化一个具有多个参数的可选对象，必须创建该对象或将std::in_place添加为第一个参数(所包含的类型无法推断):

```cpp
std::optional o6{std::complex{3.0, 4.0}};
std::optional<std::complex<double>> o7{std::in_place, 3.0, 4.0};
```

注意，第二种形式避免创建临时对象。通过使用这种形式，甚至可以传递初始化器列表和附加参数:

```cpp
// initialize set with lambda as sorting criterion:
auto sc = [] (int x, int y) 
{
    return std::abs(x) < std::abs(y);
};

std::optional<std::set<int,decltype(sc)>> o8{std::in_place, {4, 8, -7, -2, 0, 5}, sc};
可以复制可选对象(包括类型转换)：
std::optional o5{"hello"}; // deduces optional<const char*>
std::optional<std::string> o9{o5}; // OK
```


注意，还有一个方便的函数make_optional<>()，它允许使用单个或多个参数初始化(不需要in_place参数)。像往常一样make……函数推导:

```cpp
auto o10 = std::make_optional(3.0); // optional<double>
auto o11 = std::make_optional("hello"); // optional<const char*>
auto o12 = std::make_optional<std::complex<double>>(3.0, 4.0);
```


然而，注意，没有构造函数接受一个值并根据它的值来决定是使用值初始化一个可选值还是使用nullopt。可以使用操作符?:，例如:

```cpp
std::multimap<std::string, std::string> englishToGerman;
...
auto pos = englishToGerman.find("wisdom");
auto o13 = pos != englishToGerman.end()
? std::optional{pos->second}
: std::nullopt;

```



​    在这里，o13初始化为std::optional<std::string>，这是由于类模板参数的推导std::optionalf(pos->second)。对于std::nullopt类模板参数推导不起作用，但是运算符?:在推导表达式的结果类型时也将其转换为这种类型。

####访问值

检查optional对象是否有值，可以将对象当做一个布尔表达式使用它，或者调用has_value():

```cpp
std::optional o{42};
if (o) ... // true
if (!o) ... // false
if (o.has_value()) ... // true
```

  为了访问该值，提供了指针语法。**操作符*可以直接访问它所包含类型对象的值**，而操作符->允许访问它所包含类型对象的成员：

```cpp
std::optional o{std::pair{42, "hello"}};
auto p = *o; // initializes p as pair<int,string>
std::cout << o->first; // prints 42
```




注意，这些操作符要求optional包含一个值。在没有值的情况下使用它们是未定义的行为:

```cpp
std::optional<std::string> o{"hello"};
std::cout << *o; // OK: prints ”hello”
o = std::nullopt;
std::cout << *o; // undefined behavior
```


注意，实际上第二个输出仍然会编译并执行一些输出，比如再次打印“hello”，因为用于optional对象值的底层内存没有被修改。
然而，你不能也不应该依赖它。如果你不知道一个可选对象是否有值，你只能调用以下函数:

```cpp
if (o) std::cout << *o; // OK (might output nothing)
或者，您可以使用value()，如果没有包含值，它会抛出一个std::bad_optional_access异常:

std::cout << o.value(); // OK (throws if no value)
bad_optional_access直接派生自std::exception。

最后，如果optional对象没有值，您可以请求该值并传递回退值，回退值将被使用:

std::cout << o.value_or("fallback"); // OK (outputs fallback if no value)
回退参数作为rvalue引用传递，因此，如果不使用回退，则不需要花费任何代价，如果使用回退，则支持move语义。
```



####比较操作

    可以使用通常的比较操作符。操作数可以是optional对象、包含类型的对象和std::nullopt。

如果两个操作数都是具有值的对象，则使用所包含类型的对应操作符。
如果两个操作数都是没有值的对象，则认为它们是相等的(==产生true，所有其他比较产生false)。
如果只有一个操作数是有值的对象，则没有值的操作数被认为小于另一个操作数。
例如：

```cpp
std::optional<int> o0;
std::optional<int> o1{42};
o0 == std::nullopt // yields true
o0 == 42 // yields false
o0 < 42 // yields true
o0 > 42 // yields false
o1 == 42 // yields true
o0 < o1 // yields true
```



这意味着对于**无符号整型的optional对象有一个小于0的值**，对于bool的optional对象有一个小于0的值:

```cpp
std::optional<unsigned> uo;
uo < 0 // yields true
std::optional<bool> bo;
bo < false // yields true
同样，支持底层类型的隐式类型转换:

std::optional<int> o1{42};
std::optional<double> o2{42.0};

o2 == 42 // yields true
o1 == o2 // yields true
```



注意，optional的bool值或原始指针值可能会导致一些意外。

####修改值

通过赋值和emplace来修改值：

```cpp
std::optional<std::complex<double>> o; // has no value
std::optional ox{77}; // optional<int> with value 77
o = 42; // value becomes complex(42.0, 0.0)
o = {9.9, 4.4}; // value becomes complex(9.9, 4.4)
o = ox; // OK, because int converts to complex<double>
o = std::nullopt; // o no longer has a value
o.emplace(5.5, 7.7); // value becomes complex(5.5, 7.7)
```


赋值std::nullopt将删除该值，如果之前有值，该值将调用所包含类型的析构函数。也可以通过调用reset()获得相同的效果:

```cpp
o.reset(); // o no longer has a value
或赋值为空花括号:

o = {}; // o no longer has a value
```



最后，我们还可以使用操作符*修改值，因为它通过引用生成值。但是，请注意，这需要修改一个有存在的值:

```cpp
std::optional<std::complex<double>> o;
*o = 42; // undefined behavior
...
if (o) 
{
    *o = 88; // OK: value becomes complex(88.0, 0.0)
    *o = {1.2, 3.4}; // OK: value becomes complex(1.2, 3.4)
}
```



####移动语义

    std::optional<>也支持移动语义。如果将对象作为一个整体移动，则会复制状态并移动所包含的对象(如果有的话)。因此，一个从对象中移出的对象仍然具有相同的状态，但是移动后的值会变成是未指定的。但是也可以将一个值移动到或移出所包含的对象。例如:

```cpp
std::optional<std::string> os;
std::string s = "a very very very long string";
os = std::move(s); // OK, moves
std::string s2 = *os; // OK copies
std::string s3 = std::move(*os); // OK, moves
```


​    注意，在最后一次调用之后os仍然有一个字符串值，但是对于os对象这个值未指定的。因此，不能对移动后的对象的值做任何假设就去使用它。当然，可以给移动后的对象分配一个新的值。

#### Hashing



std::optional对象的哈希值是包含的非常量类型(如果有的话)的哈希值。

1.3 特定情况
    特定的可选值类型可能导致特殊或意外的行为。

1.3.1 bool或者原始指针的optional
注意，使用比较操作符与使用optional对象作为布尔值具有不同的语义。如果包含的类型是bool或指针类型，这就会变得很混乱:例如:

```cpp
std::optional<bool> ob{false}; // has value, which is false
if (!ob) ... // yields false
if (ob == false) ... // yields true
std::optional<int*> op{nullptr};
if (!op) ... // yields false
if (op == nullptr) ... // yields true
```



1.3.2 Optional的Optional
原则上，你也可以定义一个optional的optional值:

```cpp
std::optional<std::optional<std::string>> oos1;
std::optional<std::optional<std::string>> oos2 = "hello";
std::optional<std::optional<std::string>> oos3{std::in_place, std::in_place, "hello"};
std::optional<std::optional<std::complex<double>>> ooc{std::in_place, std::in_place, 4.2, 5.3};
```




你也可以分配新的值，即使隐式转换:

```cpp
oos1 = "hello"; // OK: assign new value
ooc.emplace(std::in_place, 7.2, 8.3);
```



由于optional的无值有两个层次，optional的optional使“无值”出现在外部或内部，可以有不同的语义含义:

```cpp
*oos1 = std::nullopt; // inner optional has no value
oos1 = std::nullopt; // outer optional has no value
```



但必须特别注意处理optional值:

```cpp
if (!oos1) std::cout << "no value\n";
if (oos1 && !*oos1) std::cout << "no inner value\n";
if (oos1 && *oos1) std::cout << "value: " << **oos1 << '\n';
```































