#include "func.h"
#include <iostream>
using namespace std;
int main(){
    int a = 9, b = 3;
    cout<<"do add_:" << add_(a, b) << endl;
    cout<<"do minus_:" << minus_(a, b) << endl;
    cout<<"do times_:" << times_(a, b) << endl;
    cout<<"do divide_:" << divide_(a, b) << endl;
    return 0;
}
