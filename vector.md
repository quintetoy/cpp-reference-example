##### vector



向量是数组的抽象和泛化，不局限于基本数据类型

```
//遍历
//利用函数指针机制，只读或局部性修改
template<typename T>
void Vector<T>::traverse(void (*)visit(T&)){
  for(int i=0;i<_size;i++)visit(_elem[i]);
}

//利用函数对象机制，可全局性修改
template<typename T> template<typename VST>
void Vector<T>::traverse(VST& visit)//函数对象
{
  for(int i=0;i<_size;i++)visit(_elem[i]);//这种方法通用性更强
}



template <typename T>
struct Increase{
  virtual void operator()(T &e){e++;}
};

template <typename T>void increase(Vector<T>& V){
  V.traverse(Increase<T>());
}
```



```
Q:作为一个函数对象的类XXX，它必须显式定义以下哪个成员函数：
XXX（）
～XXX()
operator[]()
operator()()//这个选项是正确的
```



```
A:http://c.biancheng.net/view/354.html
如果一个类将（）运算符重载为成员函数，这个类就称为函数对象类。
这个类的对象就是函数对象，函数对象是一个对象，但是使用的形式看起来像函数调用，实际上也执行了函数调用，因而得名


#include <iostream>
using namespace std;

class CAverage
{
public:
	double operator()(int a1,int a2,int a3){
    return (double)(a1+a2+a3)/3;
	}
};

int main(){
  CAverage average;//函数对象
  cout<<average(3,2,3);
  return 0;
}

```



#### 函数对象应用实例1:在accumulate算法中的应用



STL中有以下实现“累加”功能的算法（函数模板）：

```
template<class InIt,class T,class Pred>
T accumulate(InIt first,Init last,T init,Pred op){
  for(;first!=last;++first)
  	init=op(init,*first);
  return init;
}
```

此模板被实例化以后，`op(init,*first)`必须要有定义，则op只能是函数指针或者函数对象。因此调用该accumulate模板时，行参op对应的实参只能是函数名，函数指针或者函数对象。





下面的程序通过accumulate模板求一个vector中元素的平方和，其中用到了函数对象。

```c++
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;
template<class T>
  
  void PrintInterval(T first,T last){
  for (;first!=last;++first){
    cout<<*first<<" ";
    
  }
  
  cout<<endl;
}


int SumSquares(int total,int value){
  return total+value*value;
}


template <class T>
class SumPowers
{
private:
  int power;
  
public:
  SumPowers(int p):power(p){}//有构造函数，所以作为函数对象的时候，必须传值
  const T operator()(const T& total,const T &value){
    T v=value;
    for(int i=0;i<power-1;++i)
      v=v*value;
    return total+v;
  }
};


int main(){
  const int SIZE=10;
  int a1[]={1,2,3,4,5,6,7,8,9,10};
  vector<int> v(a1,a1+SIZE);//初始化
  PrintInterval(v.begin(),v.end());
  
  int result=accumulate(v.beigin(),v.end(),0,SumSquares);
//注释，SumSquares，函数名字的类型是函数指针，因此accumulate模板实例化后得到的模板函数定义如下：
  int accumulate(vector <int>::interator first,vector<int>::iterator last,int init,int(*op)(int,int)){
    for(;first!=last;++first)
      init=op(init,*first);
    return init;
  }
  //形参op是一个函数指针，而op(init,*first)就调用了指针op指向的函数
  
  
  
  
  
  
  result=accumulate(v.begin(),v.end(),0,SumPowers<int>(3));
  //SumPower是类模板的名字，SumPowers<int>就是类名字，类名字后面跟着构造函数的参数列表，就代表一个临时对象。
 
  //accumulate模板实例化成以下函数
  int accumulate(vector<int>::iterator first,vector<int>::interator last,int init,SumPower<int>op){
     for (; first != last; ++first)
        init = op(init, *first);
    return init;
  }
  
//  op是一个函数对象，op.operator()(init,*first);
  
  
  result=accumulate(v.begin(),v.end(),0,SumPowers<int>(4));
  
  return 0;
}
```





















