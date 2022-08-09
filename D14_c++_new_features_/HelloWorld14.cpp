//
// Created by aaab on 2020-12-05.
//

#include <iostream>
using namespace std;

/**
 *   初始化列表：
 *
 *   可变模板参数： 它能表示0到任意个数、任意类型的参数； 声明可变参数模板时需要在typename或class后面带上省略号“...”
 *                我们无法直接获取参数包args中的每个参数的，只能通过展开参数包的方式来获取参数包中的每个参数
 *
 *
 */


struct B{
    int i;
    int j;
};
struct A{
    int x;
    B b;
};
void f(A a){
    cout<<a.x<<" "<<a.b.i<<" "<<a.b.j<<endl;
}


void test11(){
//    int i_arr[3] = { 1, 2, 3 };  //普通数组
    // POD类型
    f({1,{2,3}});
//    A a={1,{3,4}};
    A a2{1,{3,4}};//在 C++11 中，可以直接在变量名后面跟上初始化列表，来进行对象的初始化
    f(a2);
}
// 通过初始化列表初始化对象
class Foo
{
public:
    Foo(int) {}
    Foo func(void)
    {
        return { 123}; // return Foo(123)
    }
private:
    Foo(const Foo &);
};
void test12(){
    Foo a1(123);
//    Foo a2 = 123;  //error: 'Foo::Foo(const Foo &)' is private
    Foo a3 = { 123 };
    Foo a4 { 123 };//在 C++11 中，可以直接在变量名后面跟上初始化列表，来进行对象的初始化
    int a5 = { 3 };
    int a6 { 3 };

    int* a = new int { 123 };
    double b = double { 12.12 };
    int* arr = new int[3] { 1, 2, 3 };
}


template <class... T>
void f(T... args)//T可以看做一个参数包，参数包中可以包含0到任意个模板参数；
{
    cout << sizeof...(args) << endl; //打印变参的个数
}
void test21(){
    f(1,2);
    f();
}

#include <algorithm>
template<class F, class... Args>void expand(const F& f, Args&&...args){
//    cout<< sizeof...(args)<<endl;
//    initializer_list<int> a{(f(std::forward< Args>(args)),99)...};
    initializer_list<int> a2{(f(std::forward< Args>(args)))...}; // ...表示解参数包
    for_each(a2.begin(),a2.end(),[](int i){cout<<i<<endl;});


}
void test22(){
//    expand([](int i){cout<<i<<endl;}, 1,2,3);
    expand([](int i){return i*2;}, 1,2,3);
}

class Test{
public:
    int a;
    Test(){
        cout<<"test cons"<<endl;
    }
};
Test t;

int main(){
//    cout<<t.a<<endl;
//    test11();

//    test21();
    test22();




}

