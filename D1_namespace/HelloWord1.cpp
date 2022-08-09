#include <iostream>
#include "game1.h"
#include "game2.h"
using namespace std;
int atk =200;
/**
 *::  作用域运算符

 * c++ Namespace
//namespace命名空间主要用途用来解诀命名冲突的问题
//1、 命名空间下可以放函数、变量、结构体、类
//2、 命名空间必须定义在全局作用域下
//3、 命名空间可以嵌套命名
//4、 命名空间是开放的，可以随时往原先的命名空间添加内容
//5. 当写了无名命名空间，其内部的变量为static变量，只能在当前文件内使用
//6、 命名空间可以起别名

 Using 关键字 （声明，编译指令 两个作用）

 */
namespace A{
    int m=123;
    struct  Person{

    };
    class Animai{};
    namespace  B{
        int m=1234;
    }
}
namespace A{
    int m2=1234;
}

namespace {
    int m3=123; // m3, m4 is static variable   ,only use in this file
    int m4=56;
}
namespace  longlongname{
    int m7=10;
}
void test2(){
    namespace shortname=longlongname; //namespace alias
    cout<<shortname::m7<<endl;
}

void test01(){
    int atk=100;
    cout<<atk<<endl;
    cout<<::atk<<endl; //200  ::  全局作用域
    cout<< A::B::m<<endl;
}


//using keyword

namespace  king{
    int s=10;
}
void test3(){
    int s=20;
    // error //using声明注意避免二义性,写了using声明后下 面这行代码说明以后看到的s是用king ns下的,但是编译器又有 就近原则,导致了s变量的二义性
//     using king::s;
    cout<<s<<endl;
}

namespace  LOL{
    int s=99;
}

void test4(){
    int s=11;
    using namespace king; // 如果前面没有s变量，则使用king中的，如果有则使用前面定义的 （不会有二义性）
    cout<<s<<endl;
}
void test5(){
    using namespace king;
    using namespace LOL;
    cout<<LOL::s<<endl;// using specific ns
}


int main(){
//    cout<<"hello world 1"<<endl;
//    test01();
//    test2();
//    test3();
    test4();
    ns1::goAtk();
    ns2::goAtk();

    return EXIT_SUCCESS;
}

