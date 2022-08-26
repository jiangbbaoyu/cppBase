//
// Created by aaab on 8/10/22.
//


#include <iostream>

void test1() {

    int a;
    std::string str;
    std::cout << a << std::endl;
    std::cout << str << std::endl;

    int b;
    for (int b = 0; a < 10; ++a) {

    }
}


int i = 0;
int j = 1;

void test2() {
    constexpr int *p = &j;// same to int* const p = &j;  指针常量的含义
//    p = &i; // error
    *p = 11;
}

void test3() {

    typedef char *cp;
    char a = 'a';
    char b = 'b';

    const cp ccp = &a; // ccp这个char* 类型变量的值不能改变（即指针的指向不能改变）， same to  char* const ccp = &a;
//    ccp = &b; // error , 指针的指向不能改变
    *ccp = b;

}

void test4() {
    int i = 1;
    const int j = i;
    auto k = &j; // k is type of  const int *  ,取地址后， k的类型中需要保留j的底层const属性

    if (typeid(k)==typeid(const int*  )){
        std::cout<<"yes"<<std::endl;
    }

    auto &l =j; // 如果是推断引用变量的类型，保留顶层const
    if (typeid(l)==typeid(const int  )){
        std::cout<<"yes"<<std::endl;
    }

}

const int& func(int a){
    std::cout<<a<< std::endl;
    int b= a+1;
    return b;
}
int* func2(int a){
    std::cout<<a<< std::endl;
    int b= a+1;
    return &b;
}
void test5(){
    decltype(func(2)) a=1 ; // reference must be initialize when defining it

    int num=1;
    decltype(func2(2)) a2;
}


int main() {
//    test1();
//    test4();
    test5();


    return 0;

}
