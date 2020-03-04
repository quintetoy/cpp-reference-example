# c++使用基类的小tips

浅显地理解为，基类可以管理所有的子类实例，当不知道对象具体的实现时，可以声明为基类，

当需要初始化的时候，可以使用子类类型来转换，然后转换为具体的实现，非常方便。

```cpp
class CBase{
public:
    virtual int a() = 0;
    virtual int b() = 0;
    virtual int c(char* h264, int length) = 0;

};

class CCpu : public CBase{
  
};


class CGpu : public CBase{
  
};
//使用时，可以声明为
CBase* m_decoder;

//赋值时，可以用子类给m_decoder赋值，即

m_decoder = new CCpu();

m_decoder = new CGpu();



```



























