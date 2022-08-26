//
// Created by aaab on 8/23/22.
//

#include <iostream>

class Inner{
public:
    Inner()= default;

    Inner* operator->(){
        std::cout<<"inner's -> "<<std::endl;
        return this;
    }
    size_t  size(){
        return 3;
    }
};

class Outer{
public:
    Inner in;
//    Inner* operator->(){
    Inner& operator->(){
        return in;
    }
};

void test1(){
    Outer o;
    std::cout<<o->size()<<std::endl;
}


// 测试lambda的隐式捕获
class size_comp{
public:
    int& sz;
    size_comp(int& sz):sz(sz){}
};

void test2(){
    int sz=12;
    size_comp c(sz);
    sz=123;
    std::cout<<c.sz<<std::endl;
}

#include <map>
#include <functional>
int add(int a,int b){
    return a+b;
}
struct divide{
    int operator()(int a,int b){
        return a/b;
    }
};
void test3(){
    std::map<std::string,std::function<int(int,int)>> ops_map={
            {"+",add},
            {"-",std::minus<int>()},
            {"*",[](int a,int b){return a*b;}},
            {"/",divide()}
    };
}

struct B;
struct A{
    A()= default;
    A(const B&);

//    operator B() const;
};

struct B{
    B()= default;
    B(const A&);
};

void f (const B& b);
void test4(){
    A a;
    f(a);
}

int main(){
//    test1();

    test2();

}
