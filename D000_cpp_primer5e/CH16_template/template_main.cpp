//
// Created by aaab on 8/24/22.
//


#include <utility>

template  <typename F,typename T1, typename T2>
void filp(F f, T1&& t1, T2&& t2){
    f(std::forward<T1>(t1), std::forward<T2>(t2));
}

void func(const int& i,int&& j){

}


void test1(){
    int a=0;
    filp(func,1,2);

    int i=3;
    int j=4;
    filp(func,i,2);
}



int main(){

}
