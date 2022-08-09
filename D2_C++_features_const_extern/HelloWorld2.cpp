#include <iostream>
using  namespace std;
/**
 * c++ 新特性 ,const details
//1.全局变量检测增强
//2、函数检测增强,参数类型，个数,返回值
//3、 类型转换检测增强 （malloc返回void*，C中可以不用强转，C++必须强转）
//4. struct增强，可以加函数
//5、bool类型增强 C语言中没有bool类型，//boo1类型非0，非false的值转为1， 0就转为0
//6、 三目运算符增强 （c 返回值，c++返回变量）
//7、const增强
    C语言中，const修饰的变量，是伪常量，编译器是会分配内存的
    C++中，如果用常量对const变量赋值，则不会分配内存，而是将const 变量名和变量值放到一个符号表中，当访问const变量时，直接从符号表中取出
    如果用变量（b）对const变量赋值,相当于 使用一个temp变量保存b的值（temp变量会开辟空间），然后b2又指向了temp变量的地址
    （即：int temp=b, int* b2=(int *）&temp)

     //C++中的const默认内部链接，extern提高作用域 (声明extern关键字的全局变量和函数可以使得它们能够跨文件被访问)

     const 变量内存分配
        //1. 对const变量取地址会分配临时内存
        //2、extern 下的const变量会给const变量分配内存
        //3、用普通变量初始化 const的变量
        //4、 自定义数据类型加const也会分配内存
        只要是分配内存的变量都可以修改变量的值

     尽量以const替换#define.
        1, 在旧版本C中,如果想建立一个常量，必须使用预处理器，
        #define MAX 1024; 我们定义的宏MAX从未被编译器看到过，因为在预处理阶段，所有的MAX已被替换为了1024，于是MAX并没有将其加入到符号表中。
        我们使用这个常量会获得编译错误信息
        2, const有类型，可进行 编译器类型安全检查。#define 无类型，不可进行类型检查.
        3. const有作用域,而#define不重视作用域.默认定义处到文件结尾 (#undef A 提前卸載宏常量)
 *
 * @return
 */

struct Person{
    int age;
    void addAge(){
        age++;
    }
};
void test(){
    Person p;
    struct  Person p2;
    p.age=12;
    p.addAge();
    cout<<p.age<<endl;
}

bool flag=2;
void test2(){
    flag=34;
    cout<<flag<<endl;
    cout<< sizeof(flag)<<endl;
}

void test3(){
    int a=10;
    int b=20;
    a>b?a:b=100; // b=100    C++中返回的是变量  //*(a>b?&a:&b)=100; // in c
    cout<<a<<endl;
    cout<<b<<endl;
}

const int a=10;
void test4(){
    /**
     * //7、const增强
        C语言中，const修饰的变量，是伪常量，编译器是会分配内存的
        C++中，const修饰的变量不会分配内存，而是将const 变量名和变量值放到一个符号表中，当访问const变量时，直接从符号表中取出
        int* b2= (int *)&b;相当于 使用一个tem变量保存b的值（temp变量会开辟空间），然后b2又指向了temp变量的地址
        （即：int temp=b, int* b2=(int *）&temp)
     */
    const int b=20; // c++中为真正的常量，c中为伪常量
    int* b2= (int *)&b;
    *b2=200;
    cout<<b<<endl;
    cout<<*b2<<endl;  // b=10,b2=100 ,b also is 200 in C
    int arr[b];
}

void test5(){
    const int a=10;
    int* p=(int*)&a; // /会分配临时内存


    int aa=10;
    const int b=aa;//会分配内存
    int* p2=(int *)&b;
    *p2=100;
    cout<<b<<endl; //100

}


void test6(){
//    extern const int e1;  // 无法从外部文件找到e1这个变量
    extern const int e2;  //可以从外部文件找到e1这个变量
    cout<<e2<<endl;
}

#include <string>
struct Person2{
    string name;
    int age;
};
void test7(){
    const Person2 p1{}; // allocate memory
//    p1.age=10; // can not modify
    Person2* p= (Person2*)&p1;
    (*p).name="aaab";//指向Person的指针使用 -> 运算符
    (*p).age=123;
    cout<<p1.name<<"  "<<p1.age<<endl;
    p->name="qqqz";//Person类型的对象 使用 . 运算符
    cout<<p1.name<<endl;
}


int main(){
//    test();
//    test2();
//    test3();
//    test4();
//    test5();
//    test6();
//    test7();
    return EXIT_SUCCESS;
}

