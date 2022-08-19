//
// Created by aaab on 8/16/22.
//
#include <iostream>



//void reset0(int a){// 重复定义
//    std::cout<<a<<std::endl;
//}
void reset0(const int a){
    std::cout<<a<<std::endl;
}


// 引用类型不存在重复定义
void reset(int& a){
    std::cout<<a<<std::endl;
}
void reset(const int& a){
    std::cout<<a<<std::endl;
}



void printArr(int* arr){}

// 重复定义
void printArr(const int* arr){}
//void printArr(const int arr[]){}
//void printArr(const int arr[10]){}



// 不存在重复定义
void test2(int (*arr)[3]){}
void test2(int (*arr)[34]){}
void test2(const int (*arr)[34]){}

#include <initializer_list>
void test3(const std::initializer_list<int>& list){
    for(auto &item :list){
//        item ="abc"; // can not modify items
        std::cout<<item<<std::endl;
    }
}

std::string& test4(){
    std::string str("abc");
    std::cout<<str<<std::endl;
    return str; // 不能返回局部变量的引用
}

#include <vector>
//const std::vector<int>& test5(){ // 不能返回局部变量的引用
std::vector<int> test5(){

    return {1,23};
}

using arrT = int[10];
typedef int (&arrT2)[10];

#include <iterator>
const arrT2 test6(arrT2 arr,size_t size){
    for(size_t i =0;i<size;++i){
        arr[i] +=10;
    }
    return arr;
}

// 返回数组引用，不使用类型别名
const int (&test61(arrT2 arr,size_t size))[10]{
    for(size_t i =0;i<size;++i){
        arr[i] +=10;
    }
    return arr;
}

// 尾置返回
auto test62(arrT2 arr,size_t size) -> int (&)[10]{
    for(size_t i =0;i<size;++i){
        arr[i] +=10;
    }
    return arr;
}


void test7(int a,std::string str){};
void test7(std::string str,int a){};


int a=13;
void test8(int num=a){
    std::cout<<a<<std::endl;
}


constexpr size_t test9(size_t num){
    return 10+num;
}
//int arr[test9(1)];
int num2=1;
//int arr[test9(num2)]; // test9(num2) 不是一个常量

size_t (*pf)(size_t);
void test10(){
    pf = test9;
    pf(10);
    (*pf)(10);

}


void ff(int*);
void ff2(int*);
void ff(unsigned int);

void(*pf2)(int*);
void(*pf3)(unsigned int);






int main(int argc,char* argv[]){
//    int a=0;
//    reset0(a);
//    int arr1[3]={1,2,3};
//    printArr(arr1);


//    int arr2[2][3] ={{1,2,3},{4,5,6}};
//    test2(arr2);

//    test3({1,2,3});


//    auto str=test4();
//    std::cout<<str<<std::endl;

//    auto nums = test5();
//    std::cout<<nums.size()<<std::endl;
//    for(auto b =nums.begin(),e=nums.end();b!=e;++b){
//        std::cout<<*b<<std::endl;
//    }

//    int arr[10]={1,2,3};
//    auto arr2 =test61(arr,3);
//    auto arr2 =test6(arr,3);
//    for(size_t i =0;i<3;++i){
//        std::cout<<arr2[i]<<std::endl;
//    }


    test10();



}
