//
// Created by aaab on 8/23/22.
//

#include <iostream>
#include <string>
#include "Quote.h"

class Base{
protected:
    int pro_mem=2;
};

class Sneaky: public  Base{
    friend void clobber(const Sneaky& s);
    friend void clobber2(const Base& b);
};
void clobber(const Sneaky& s){
    std::cout<< s.pro_mem<< std::endl;

}
void clobber2(const Base& b){
//    std::cout<< b.pro_mem<< std::endl; // error  派生类的友元 不能通过父类来访问 继承自父类的受保护成员

}
void test1(){
    clobber2(Base());
}

class Base2{
public:
    void pub_mem(){};

protected:
    void pro_mem(){};

private:
    void pri_mem(){};
};

class pri_dev : private Base2{
    int f(){
        pub_mem();
        pro_mem();
//        pri_mem();

        Base2 b= *this;
    }
};

void test2(){
    pri_dev pd;
//    pd.pub_mem();// error
//    pd.pub_mem();// error
//    pd.pri_mem();// error

//    Base2 b= pd; // error
}

class pri_dev2: private Base2{
public:
    using Base2::pro_mem;
    using Base2::pub_mem;
//    using Base2::pri_mem; // error
};

void test3(){
    pri_dev2 pd;
    pd.pub_mem();
    pd.pub_mem();
}



void test4(){
    Bulk_quote bq;
    Quote* qp = &bq;
    Quote& qc = bq;

    Bulk_quote* bqp2 = static_cast<Bulk_quote*>(qp);

    Quote q2 =bq; // use Quote's copy constructor , sliced down Bulk_quote's part
}


struct Base5{
    int memfcn(){};
};

struct Derived5: Base5{
//    using Base5::memfcn; // 解决父类中memfcn函数的重载版本，在子类中不可见的问题
    int memfcn(int){};
};


void test5(){
    Derived5 d;
//    d.memfcn();
    d.memfcn(1);
    d.Base5::memfcn(); // 解决父类中memfcn函数的重载版本，在子类中不可见的问题

    Derived5* dp;

    Base5* bp = &d;
    bp->memfcn();


}

class Base6{
public:
    Base6(){
        std::cout<<"base cons call"<<std::endl;
        test();
    }
    ~Base6(){
        std::cout<<"base destructor call"<<std::endl;
    }
    virtual  void test();
    int num=1;
};
void Base6::test() {
    std::cout<<this->num<<std::endl; // 1, this指父类的对象，而非子类的（与java 不同 ）
}

class Child6:public Base6{
public:
    Child6(){
        std::cout<<"child cons call"<<std::endl;
        test();
    }
    ~Child6(){
        std::cout<<"child destructor call"<<std::endl;
    }
    void test();

    int num=2;

};

void Child6::test() {
    std::cout<<this->num<<std::endl;
}

void test6(){
    Child6 c;
    Base6* b=&c;
    std::cout<< b->num<<std::endl; // 属性不存在动态性 1
}

void test7(){




}


int main(){
//    test1();
    test6();
}
