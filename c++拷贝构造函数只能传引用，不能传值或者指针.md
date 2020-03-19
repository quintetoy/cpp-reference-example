# c++拷贝构造函数只能传引用，不能传值或者指针

```cpp
#include <iostream>
using namespace std;
class CExample{
private:
    int m_nTest;
public:
    //构造函数1
    CExample(int x):m_nTest(x){cout<<"contruct with argument"<<endl;}
    //构造函数2
    //一把传入即成功，不会递归去调用赋值函数，不会形成递归的结果
    CExample(const CExample& ex){
        m_nTest=ex.m_nTest;
        cout<<"copy constructor"<<endl;
    }
    
    CExample& operator=(const CExample&ex){
        cout<<"assignment operator"<<endl;
        m_nTest=ex.m_nTest;
        return *this;
    }
    
    void myTestFunc(CExample ex){
        
    }
};


int main(void){
    
    CExample aaa(2);//调用传参构造函数
    CExample bbb(3);//调用传参构造函数
    bbb = aaa;//赋值运算符构造函数
    
    CExample ccc = aaa;//拷贝构造函数，因为ccc还没有构造出来，但是它需要参数
    
    
    bbb.myTestFunc(aaa);//拷贝构造函数
    
    return 0;
}

//程序分析，因为bbb已经实例化了，所以不需要调用构造函数，只需要调用g赋值函数。
//ccc还没有实例化，所以需要调用拷贝构造函数，构造出ccc

//第二个拷贝构造函数分析，首先将aaa作为参数传递给bbb.myTestFunc(CExample aaa)，即CExample ex=aaa
//拷贝一份aaa的副本，所以需要调用拷贝构造函数

//如果拷贝构造函数是传值而不是传引用，当调用Example ccc = aaa，ccc.CExample(aaa)时，需要执行将aaa作为入参赋值给CExample ex=aaa，因为ex没有被初始化，那么要调用拷贝构造函数，即此时ex作为要实例化的对象，其接收的参数是由aaa传递的，一层一层的参数传递，最终没有停止会无限调用下去
//就会继续掉用拷贝构造函数构造出ex，ex(CExample aaa)，必然又会有aaa传给CExample(CExample ex)，即CExample ex = aaa；那么又会触发拷贝构造函数，这样就无限递归下去了。


//所以拷贝构造函数中一定要传引用，传值和传指针都不可以

```

