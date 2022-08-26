//
// Created by aaab on 8/20/22.
//

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class Sales_data{
public:
    Sales_data(){
        std::cout<<"default cons call!"<<std::endl;
    }
    Sales_data(const Sales_data& other){
        this->isbn= other.isbn;
        std::cout<<"copy cons call!"<<std::endl;
    }
    Sales_data(int a){
        std::cout<<"params cons call!"<<std::endl;
        this->isbn= std::to_string(a);
    }


    std::string isbn;
};
bool compareIsbn(const Sales_data& sd1,const Sales_data& sd2){
    return sd1.isbn<sd2.isbn;
}

void test1(){
    std::map<std::string,size_t > word_count;
    std::vector<std::string> words={"a","b","a","c"};

    for(auto word : words){
        if(word_count.find(word)==word_count.end()){
            word_count.insert({word,1});
        }else{
            ++word_count[word];
        }
    }

    for(std::map<std::string,size_t >::value_type pair:word_count){
        std::cout<<pair.first<<":"<<pair.second<<std::endl;
    }

}

void test2(){
    std::multiset<Sales_data, decltype(compareIsbn)* > dates(compareIsbn);
}

void test3(){

    std::map<std::string,Sales_data> word_count;

    word_count.insert({"a",Sales_data()}); // 一次构造，两次拷贝
    word_count.emplace("b",3); //只调用一次构造函数，高效
    std::cout<<word_count.size()<<std::endl;
}

void test4(){
    std::map<std::string,Sales_data> m1;
    std::cout<<m1.size()<<std::endl;
    m1["a"]=Sales_data(); // 调用两次构造函数
    m1["b"];
    std::cout<<m1.size()<<std::endl; // size ==2
}


size_t  hasher(const Sales_data& sd){
    return std::hash<std::string>()(sd.isbn);
}

bool equal_op(const Sales_data& sd1,const Sales_data& sd2){
    return sd1.isbn==sd2.isbn;
}

void test5(){

    using my_unordered_map = std::unordered_map<Sales_data,Sales_data, decltype(hasher)*, decltype(equal_op)* >;

    my_unordered_map  m2(10,hasher,equal_op);
    Sales_data d1(1);
    Sales_data d2(2);
    Sales_data d3(2);
    m2[d1]=d1;
    m2[d2]=d2;
    m2[d3]=d3;

    std::cout<<m2.size()<<std::endl; // 2
}

int main(int argc,char** argv){

//    test1();
//    test3();
//    test4();
    test5();

}

