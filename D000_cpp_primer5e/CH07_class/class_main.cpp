//
// Created by aaab on 8/17/22.
//

#include <iostream>


struct Sales_data{

    friend void read(std::istream& in,Sales_data& data);
public:
    Sales_data()= default;
    Sales_data(std::istream& in);
    Sales_data(std::string& str);
//    explicit Sales_data(std::string& str);


    std::string isbn() const{
//        (*this).bookNo=123; // not allowd
        this->bookNo;
        return bookNo;
    }
    Sales_data& combine (const Sales_data& data);
    double avg_price() const;

private:

    std::string bookNo ="abc";
    unsigned units_sold=0;
    double revenue=0.0;
    mutable int count =0; // 可变成员，即使在 const方法中也可以修改

};

void read(std::istream& in,Sales_data& data){
    double price=0.0;
    in>>data.bookNo>>data.units_sold>> price;
    data.revenue = data.units_sold * price;
}

Sales_data::Sales_data(std::istream& in) {
    read(in,*this);
}

Sales_data::Sales_data(std::string &str) :bookNo(str){}



Sales_data& Sales_data::combine (const Sales_data &data){
    this->revenue +=data.revenue;
    this->units_sold+=units_sold;
    return *this;
}

double Sales_data::avg_price() const {

    this->count+=1;
//    this->bookNo+=1;


    if(units_sold){
        return revenue/units_sold;
    }
    return 0.0;
}

void test1(){

    Sales_data data;
//    data.bookNo="001";
    std::cout<<data.isbn()<<std::endl;

}

#include "window_mgr.h"
void test2(){
    Window_mgr mgr;
    Screen sc1;
    Screen sc2;
    mgr.screens.push_back(sc1);
    mgr.screens.push_back(sc2);


    mgr.clear();

    for(auto sc:mgr.screens){
        std::cout<<sc.getWidth()<<std::endl;
        std::cout<<sc.getHigh()<<std::endl;

    }

}

class NoDefaultCons{
public:
    NoDefaultCons(const std::string& str,int num);
    NoDefaultCons(std::string& str):NoDefaultCons(str,0){}
//    NoDefaultCons():NoDefaultCons("",0){};

};
class Test3{
private:
    NoDefaultCons member;
};

void test3(){
//    Test3 t; // member no default constructor
}



void test4(){
    Sales_data item;
    std::string str("abc");

    Sales_data item2 = str; // convert str to a Sales_data via `Sales_data(std::string& str)`

    item.combine(str);  // convert str to a Sales_data via `Sales_data(std::string& str)`, and  then call combine
}

class Test5{
public:
    int a;

};
void test5(){


    Test5 test;
    std::cout<<test.a<<std::endl;
}


int main(int argc,char* argv[]){
//    test1();

//    test2();

    test5();
}

