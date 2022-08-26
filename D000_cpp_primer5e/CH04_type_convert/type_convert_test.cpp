//
// Created by aaab on 8/14/22.
//
#include <iostream>
using std::cout;
using std::endl;

void ConstTest1(){
    const int a = 1;
    int *p;
    p = const_cast<int*>(&a);
    (*p)++;
    cout<<a<<endl;
    cout<<*p<<endl;

}
void ConstTest2(){
    int i=3;
    const int a = i;
    int &r = const_cast<int &>(a);
    r++;
    cout<<a<<endl;
}

void ConstTest3(){
    int i=10;
    const int* const a = &i;
    int* r = const_cast<int*>(a);
    (*r)++;

    int j=99;
    r=&j;// 顶层的const 语义 也可以消除掉 ？？？

    cout<<*r<<endl;
}



int main(){
//    ConstTest1();
//    ConstTest2();


    ConstTest3();
}