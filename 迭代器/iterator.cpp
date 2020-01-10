#include <iostream>
#include <algorithm>

template<long FROM,long TO>
class Range{
public:
    class iterator:public std::iterator<std::input_iterator_tag,long,long,const long*,long>{
        long num=FROM;
    public:
        explicit iterator(long _num=0):num(_num){}
        iterator& operator++(){num=TO>=FROM?num+1:num-1;return *this}
        iterator operator++(int){iterator retval=*this;++(*this);return retval;}
        bool operator==(iterator other)const{return num==other.num;}
        bool operator!=(iterator other)const{return !(*this==other);}


    } ;

    iterator begin(){return iterator(FROM);}
    iterator end(){return iterator(TO>=FROM?TO+1:TO-1);}
};


int main(){
    auto range=Range<15,25>();//<>这种符号代表什么意思？代表输入的模板类型  vector<int>  模板函数
    auto itr=std::find(range.begin(),range.end(),18);

    std::cout<<*itr<<"\n";

    for(long l:Range<3,5>()){
        std::cout<<l<<' ';

    }

    std::cout<<'\n';

}


//常见的容器取值  auto&表示引用  auto表示拷贝
char charr[10]={"goodluck" };
for(auto&ch:charr)
        cout<<ch;


for(auto ch2:charr)
        cout<<ch2;

for(auto& a:A){
    cout<<a<<endl;
}