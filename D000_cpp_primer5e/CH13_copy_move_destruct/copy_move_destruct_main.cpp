//
// Created by aaab on 8/21/22.
//

#include <iostream>
#include <string>



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

    ~Sales_data(){
        std::cout<<"destructor call!"<<std::endl;
    }

    Sales_data&operator=(const Sales_data& sd){
        this->isbn = sd.isbn;
        std::cout<<"assign operator call!"<<std::endl;
        return *this;
    }

    void test()= delete;


    std::string isbn;
    long double num;
};
bool compareIsbn(const Sales_data& sd1,const Sales_data& sd2){
    return sd1.isbn<sd2.isbn;
}


Sales_data test0(Sales_data sd){
    Sales_data s;
    Sales_data s2;
    s2=s;
    return s2;
}


class HasPtr{
public:
    HasPtr()= default;
    HasPtr(const HasPtr& other):strp(new std::string(*other.strp)),i(other.i){}
    ~HasPtr(){delete this->strp;}

    HasPtr& operator=(const HasPtr& other){
        auto strp_tmp = new std::string(*other.strp);
        delete this->strp;

        this->strp = strp_tmp;
        this->i= other.i;
        return *this;
    }
private :
    std::string* strp;
    int i;
};

class HasPtr2{
public:
    HasPtr2(const std::string& str=std::string())
    :i(0),strp(new std::string(str)),count(new int(1)){
    }

    HasPtr2(const HasPtr2& other):i(other.i),strp(other.strp){
        ++count;
    }
    ~HasPtr2(){
        if(--count == 0){
            delete strp;
            delete count;
        }
    }

    HasPtr2& operator=(const HasPtr2& other){

        (*other.count)++; // 自赋值问题
        if(--count==0){
            delete strp;
            delete count;
        }

        this->i = other.i;
        this->strp = other.strp;
        this->count= other.count;

        return *this;
    }



private:
    int i;
    std::string *strp;
    int *count;

};


void test3(){
    int&& rf = 3;

    int i = rf;
    int& lf = rf;
//    const int& lf = rf;

//    lf =4;
    i=9;
    std::cout<< rf<<std::endl;

}


class Student {
public:
    std::string getName() { return name; }

    static int total;//静态成员变量
private:
    std::string name;
};
int Student::total=0;


int main(){
//    Sales_data sd;
//    test0(sd);


    test3();



}
