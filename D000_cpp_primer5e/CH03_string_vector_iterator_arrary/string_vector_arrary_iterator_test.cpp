//
// Created by aaab on 8/12/22.
//
#include <string>
#include <iostream>


void test1(){
    std::string str("abc");
    auto len = str.size();

    std::cout<< typeid(len).name()<<std::endl;


    int n=-1;
    if(len>n){
        std::cout<<"yes"<<std::endl;
    }

}

void test2(){
    std::string str("abc");

    auto str2 = 'a'+str;
    auto str3 = str+"a";
//    auto str4 = "a"+"a"+str; // error


}

#include <cctype>
void test3(){
    std::string str("abc");

    std::cout<<str<<std::endl;
    decltype(str.size()) len =0; // 方法内部变量，要初始化
    for(auto& c:str){
        len++;
        c = toupper(c);
    }

    std::cout<<str<<std::endl;
    std::cout<<"len :"<<len<<std::endl;

}

void test4(){
    //    const std::string str2("abcd");
    std::string str2("abcd");
//    std::cout<<str2[-4]<<std::endl; // known behaviour

//    char  &c =str2[1];// error if str is a constant
//    c ='z';
    std::cout<<str2<<std::endl;

    for(std::string::size_type i=0;i<str2.size();i++){
        str2[i] = toupper(str2[i]);
    }

    std::cout<<str2<<std::endl;
}


#include <vector>

void test5(){

    std::vector<std::string> v0 {10} ; //compiler optimize , std::vector<std::string> v0 (10);

    std::vector<int> v1(3); // 0 0 0
    for(auto &i :v1){
        i=i+100;
//        v1.push_back(123); // 错误使用

    }
    std::cout<<v1.size()<<std::endl;
    for(auto i :v1){
        std::cout<<i<<std::endl;
    }

//    v1[6]=123; // 地址非法访问
}

void test6(){

    std::string str("abc");
    for(auto b =str.begin(),e=str.end();b!=e;b++){
//        *b = toupper(*b);
    }
    std::cout<<str<<std::endl;

    std::vector<std::string> strs{"a","b"};
    for(auto b=strs.begin(),e=strs.end();b!=e;b++){
        b->empty();
        (*b)>(*b)?1:2;
    }

}

// 二分查找
void test7(){

    std::vector<int> nums{1,2,3,6,8,99};
    int target =8;

    auto left = nums.begin();
    auto right =nums.end();

    while(left<=right){
        auto mid = left + (right-left)/2;
        if (*mid==target){
            std::cout<<"find target"<<std::endl;
            return ;
        }else if (*mid>target){
            right = mid-1;
        }else if(*mid<target){
            left = mid+1;
        }
    }

    std::cout<<"not find target"<<std::endl;

}

constexpr int a=12;
int arr[a];
void test8(){
    arr[2]=99;
    std::cout<<arr[2]<<std::endl;


    int (*parr)[12] =&arr; // 指向数组的指针，（）不能省略
    std::cout<<(*parr)[2]<<std::endl;


    for(auto &i : arr){
        i = 10;
    }
    for(auto i : arr){
        std::cout<<i<<std::endl;
    }

    int* ptr = arr;

    arr[0]=11;
    auto arr2 = arr;
    std::cout<<arr2[1]<<std::endl;


}

void test9(){
    int a=5;
    int arr3[a];

    for(size_t i=0;i<a;i++){
        arr3[i]=8;
    }

    for(int*b =arr3,*e=arr3+a;b!=e;b++){ // 基于指针对数组进行遍历
        std::cout<<*b<<std::endl;
    }

    std::vector<int> v2(arr3+1,arr3+3);
}

void test10(){

    int arr[3][3]={{1,1,1},{2,2,2},{3,3,3}};
    int (&ca) [3] =arr[0];
    int (*pa) [3] =&arr[0];

    for(auto num: *pa){
        std::cout<<num<<std::endl;
    }


//    for(auto &row:arr){
//        for(auto col:row){
//            std::cout<<col<<std::endl;
//        }
//    }

    for(auto &row:arr){ // auto的类型推断为 数组引用
        for(auto &col:row){
            col +=1;
        }
    }

    for(int (&row) [3]:arr){ // auto的类型推断为 数组引用
        for(auto col:row){
            std::cout<<col<<std::endl;
        }
    }

}

void test11(){

    int arr[3][3]={{1,1,1},{2,2,2},{3,3,3}};

    // 基于指针的二维数组遍历
    for(auto prow=arr;prow!=arr+3;prow++){
        for(auto pcol = *prow;pcol!=*prow+3;pcol++){
            std::cout<<*pcol;
        }
        std::cout<<std::endl;
    }

    for(int (* prow)[3] = arr;prow!=arr+3;prow++){
        for(int* pcol = *prow;pcol!=*prow+3;pcol++){
            std::cout<<*pcol;
        }
        std::cout<<std::endl;

    }

}

void test12() {

    std::string str("abc");
    auto len = str.size();

    // 打印各个字符的地址
    for (decltype(str.size()) i = 0; i < str.size(); i++) {
        std::cout << static_cast<void *>(&str[i]) << std::endl;
    }

    for (char &c :str) { // 没有对str中的字符进行拷贝
        std::cout << static_cast<void *>(&c) << std::endl;
    }

    for (char c :str) {
        // 有对str中的字符进行拷贝
        // 申请一个临时的字符，每次将str中的一个字符拷贝给该临时字符，该循环中c的地址是该临时变量的地址
        std::cout << static_cast<void *>(&c) << std::endl;
    }

}


//int main(){
////    test1();
////    test3();
////    test4();
//
////    test5();
////    test6();
////    test7();
////    test8();
////    test9();
////    test10();
////    test11();
//}
