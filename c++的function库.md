##### c++的function库

```c++
#include <functional>
#include <iostream>
struct Foo{
  Foo(int num):num_(num){}
  void print_add(int i)const{std::cout<<num_+i<<"\n";}
  int num_;
};

void print_num(int i){
  std::cout<<i<<"\n";
}

struct PrintNum{
  void operator()(int i)const{//这是一种什么表达
    std::cout<<i<<"\n";
  }
};


int main(){
  
  std::function<void(int)>f_display=print_num;
  f_display(-9);  //-9
  
  std::function<void()>f_display_42=[](){print_num(42);};
  f_display_42();//42
  
  std::function<void()>f_display_31337=std::bind(print_num,31337);
  f_display_31337();//31337
  
  std::function<void(const Foo&,int)>f_add_display=&Foo::print_add;
  const Foo foo(01245);
  f_add_display(foo,1);//01246
  f_add_display(01245,1);//01246
  
  std::function<int(Foo const&)>f_num=&Foo::num_;
  std::cout<<"num_:"<<f_num(foo)<<"\n";//num_:01245
  
  using std::placeholders::_1;
  std::function<void(int)>f_add_display2=std::bind(&Foo::print_add,foo,_1);
  f_add_display2(2);//01247


  // store a call to a member function and object ptr
  std::function<void(int)> f_add_display3 = std::bind( &Foo::print_add, &foo, _1 );
  f_add_display3(3);//01248

  // store a call to a function object
  std::function<void(int)> f_display_obj = PrintNum();
  f_display_obj(18);//18
  
}


```

- 具体的规则

  假设已经定义了一个function的变量 fun

  > 普通函数 fun=a;
  >
  > lambda表达式  auto compare_lambda=[](int a,int b){return a>b}.     fun=compare_lambda; result=fun(10,1);
  >
  > 仿函数（functor重载括号运算符实现）fun=compare_class();result=fun(10,1); 对比以上的PrintNum
  >
  > 类成员函数  需要使用bind函数，并且需要实例化对象，成员函数要加&
  >
  > 类静态成员函数 可以直接调用fun=compare::compare_static_member;result=fun(10,1);
  >
  > 类的成员变量，需要使用&符号







```
#include <iostream>
#include <functional>
 
using namespace std;
 
std::function<bool(int, int)> fun;
//普通函数
bool compare_com(int a, int b)
{
    return a > b;
}
//lambda表达式
auto compare_lambda = [](int a, int b){ return a > b;};
//仿函数
class compare_class
{
public:
    bool operator()(int a, int b)
    {
        return a > b;
    }   
};
//类成员函数
class compare
{
public:
    bool compare_member(int a, int b)
    {
        return a > b;
    }
    static bool compare_static_member(int a, int b)
    {
        return a > b;
    }
};
int main()
{
    bool result;
    fun = compare_com;
    result = fun(10, 1);
    cout << "普通函数输出, result is " << result << endl;
 
    fun = compare_lambda;
    result = fun(10, 1);
    cout << "lambda表达式输出, result is " << result << endl;
 
    fun = compare_class();
    result = fun(10, 1);
    cout << "仿函数输出, result is " << result << endl;
 
    fun = compare::compare_static_member;
    result = fun(10, 1);
    cout << "类静态成员函数输出, result is " << result << endl;
 
    ////类普通成员函数比较特殊，需要使用bind函数，并且需要实例化对象，成员函数要加取地址符
    compare temp;
    fun = std::bind(&compare::compare_member, temp, std::placeholders::_1, std::placeholders::_2);
    result = fun(10, 1);
    cout << "类普通成员函数输出, result is " << result << endl;
}



```



- placeholder占位符的说明和使用

```
下面通过代码会更容易使用和理解:

#include <iostream>
using namespace std;
class A
{
public:
    void fun_3(int k,int m)
    {
        cout<<k<<" "<<m<<endl;
    }
};
 
void fun(int x,int y,int z)
{
    cout<<x<<"  "<<y<<"  "<<z<<endl;
}
 
void fun_2(int &a,int &b)
{
    a++;
    b++;
    cout<<a<<"  "<<b<<endl;
}
 
int main(int argc, const char * argv[])
{
    auto f1 = std::bind(fun,1,2,3); //表示绑定函数 fun 的第一，二，三个参数值为： 1 2 3
    f1(); //print:1  2  3
 
    auto f2 = std::bind(fun, placeholders::_1,placeholders::_2,3);
    //表示绑定函数 fun 的第三个参数为 3，而fun 的第一，二个参数分别有调用 f2 的第一，二个参数指定
    f2(1,2);//print:1  2  3
 
    auto f3 = std::bind(fun,placeholders::_2,placeholders::_1,3);
    //表示绑定函数 fun 的第三个参数为 3，而fun 的第一，二个参数分别有调用 f3 的第二，一个参数指定
    //注意： f2  和  f3 的区别。
    f3(1,2);//print:2  1  3
 
 
    int n = 2;
    int m = 3;
 
    auto f4 = std::bind(fun_2, n,placeholders::_1);
    f4(m); //print:3  4
 
    cout<<m<<endl;//print:4  说明：bind对于不事先绑定的参数，通过std::placeholders传递的参数是通过引用传递的
    cout<<n<<endl;//print:2  说明：bind对于预先绑定的函数参数是通过值传递的
 
 
    A a;
    auto f5 = std::bind(&A::fun_3, a,placeholders::_1,placeholders::_2);//占位符，对应符合的变量，如果一致则对应，多于的输入会被舍弃
    f5(10,20);//print:10 20
 
    std::function<void(int,int)> fc = std::bind(&A::fun_3, a,std::placeholders::_1,std::placeholders::_2);
    fc(10,20);//print:10 20
 
    return 0;
}


```



- 参考博客

<https://blog.csdn.net/p942005405/article/details/84760715>

<https://blog.csdn.net/weixin_43333380/article/details/82935291>

