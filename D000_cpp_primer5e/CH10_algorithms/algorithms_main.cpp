//
// Created by aaab on 8/19/22.
//

#include <algorithm>
#include <iostream>


void test1(){
    int arr[]={1,2,3,4,5,6};

    auto it = std::find(std::begin(arr),std::begin(arr)+3,4);

    if(it!=std::begin(arr)+3){
        std::cout<<"find it!, "<<*it<<std::endl;
    }else{
        std::cout<<"not find !"<<std::endl;
    }
}

#include <iterator>
#include <vector>
void test2(){

    int arr[]={1,2,3,4};
    int arr2[sizeof(arr)/ sizeof(arr[0])];

    std::copy(std::begin(arr),std::end(arr),std::begin(arr2));


//    for(auto n:arr){
//        std::cout<<n<<std::endl;
//    }
//    for(auto n:arr2){
//        std::cout<<n<<std::endl;
//    }


    std::vector<int> nums;
    std::replace_copy(std::begin(arr),std::end(arr),std::back_inserter(nums),2,22);
    for(auto n:arr){
        std::cout<<n<<std::endl;
    }
    for(auto n:nums){
        std::cout<<n<<std::endl;
    }
}

void test3(){

    int arr[]={1,2,3,4};
    int pivot=3;
    auto it = std::find_if(std::begin(arr),std::end(arr),
            [&pivot](const int& num){

//        pivot++; // 会对外部的值有影响
        return num>=pivot;
    });

    std::cout<<*it<<std::endl;
    std::cout<<pivot<<std::endl;

}

#include <functional>
bool check_size(const std::string& str,std::string::size_type size){
    return str.size()>size;
}
auto  get_size = [](const std::string& str){
    return str.size();
};

using namespace std::placeholders;
void test4(){
    std::vector<std::string> strs {"abc","af","sfdfd","sdfff"};

    auto it = std::find_if(strs.begin(),strs.end(),
            std::bind(check_size,_1,3));
    std::cout<<*it<<std::endl;


//    auto size = std::bind(get_size,"abc");
//    std::cout<<size()<<std::endl;

}

#include <list>
void test5(){

    std::list<int> lst1 ={1,2,3};;
    std::list<int> lst2, lst3;

    auto inserter= std::inserter(lst2,std::begin(lst2));
    std::copy(std::begin(lst1),std::end(lst1),inserter);
    for(auto n:lst2){
        std::cout<<n<<std::endl;
    }
}

void test6(){
    std::list<int> lst1 ={1,2,3};
    // 将 lst1中的数据拷贝cout中
    std::copy(lst1.begin(),lst1.end(),std::ostream_iterator<int>(std::cout,"\n"));

}


int main(){

//    test1();
//    test2();

//    test3();
//    test4();
    test5();

}

