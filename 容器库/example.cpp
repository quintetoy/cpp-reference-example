#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>

/**********************array的使用******************************/

int main(){
    std::array<int,3>a1{{1,2,3}};
    std::array<int,3>a2={1,2,3};
    std::array<std::string,2>a3={std::string("a"),"b"};
    std::sort(array.begin(),array.end());
    std::reverse_copy(a2.begin(),a2.end(),std::ostream_iterator(std::cout," "));
    std::cout<<"\n";
    
    for(const auto& s:a3)
        std::cout<<s<<' ';
}


/**********************vector的使用******************************/
//修改器clear,insert,emplace,erase,push_back,emplace_back,pop_back,resize,swap

//emplace_back  push_back  以及访问其中的元素

#include <vector>
#include <string>
#include <iostream>

struct President{
    std::string name;
    std::string country;
    int year;
    
    President(std::string p_name,std::string p_country,int p_year):name(std::move(p_name)),country(std::move(p_country),year(p_year)){
        std::cout<<"I am being constructed! ";
    }
    //拷贝构造函数
    President(President&& other):name(std::move(other.name)),country(std::move(other.country)),year(other.year){
        std::cout<<"I am being moved! ";
    }
    
    President& operator=(const President& other) =default;
    
    
};


int main(){
    std::vector<President>elections;
    std::cout<<"emplace_back:\n";
    elections.emplace_back("Nelson Mandela","Sounth Afriaca",1994);//直接构造一个对象，传入构造函数的参数
    
    std::vector<President>reElections;
    std::cout<<"\npush_back:\n";
    reElections.push_back(President("Franklin Delano Roosevelt","the USA",1936));
    
    std::cout<<"\nContent:\n";
    for(President const& president:elections){
        std::cout<<president.name<<"was elected president of "<<president.country<<" in "<<president.year<<".\n";
    }
    
    for (President const& president: reElections) {
        std::cout << president.name << " was re-elected president of "
        << president.country << " in " << president.year << ".\n";
    }
}


//insert 在指定的位置插入相应的数值
#include <iostream>
#include <vector>

void print_vec(const std::vector<int>& vec){
    for(auto x:vec)
        std::cout<<" "<<x;
    std::cout<<"\n";
}



int main(){
    std::vector<int> vec(3,100);//插入3个100
    print_vec(vec);
    
    auto it=vec.begin();
    it=vec.insert(it,200);
    print_vec(vec);
    
    it=vec.begin();
    std::vector<int> vec2(2,400);
    vec.insert(it+2,vec2.begin(),vec2.end());
    print_vec(vec);
    
    int arr[] = { 501,502,503 };
    vec.insert(vec.begin(), arr, arr+3);
    print_vec(vec);
    
}



///pop_back 移除容器的最末元素
//vec.pop_back()

//resize
#include <iostream>
#include <vector>
int main()
{
    std::vector<int> c = {1, 2, 3};
    std::cout << "The vector holds: ";
    for(auto& el: c) std::cout << el << ' ';
    std::cout << '\n';
    c.resize(5);
    std::cout << "After resize up to 5: ";
    for(auto& el: c) std::cout << el << ' ';
    std::cout << '\n';
    c.resize(2);
    std::cout << "After resize down to 2: ";
    for(auto& el: c) std::cout << el << ' ';
    std::cout << '\n';
}


//erase
#include <vector>
#include <iostream>

int main( )
{
    std::vector<int> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';
    
    c.erase(c.begin());
    
    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';
    
    c.erase(c.begin()+2, c.begin()+5);
    
    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';
}



///容量 empty size max_size reserve capacity shrink_to_fit



/*******************************list***************************/

//修改器 clear  push_back/push_front  pop_back/pop_front  emplace_back/emplace_front  insert /erase resize swap emplace

//操作  merge/splice/remove/reverse/unique/sort




