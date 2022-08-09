//
// Created by aaab on 11/2/20.
//

#include <iostream>
using namespace std;
/**
 * 引用 & (引用的本质在C+ +内部实现是一一个指针常量)
//  引用必须初始化,初始化后不可修改
//  数组引用 , 指针数组 和 数组指针

 注意事项
//1、 引用必须引一-块合法的内存空间
//2、不要返回局部变量的引用 ，此时方法返回的引用指向的对象已经销毁，如果把这个引用赋值给其他变量，会报错
//3, 如果函数的返回值是引用，那么这个函数调甪可以作为左值
 *
 * 利田指针引用开辟空间
 *
 常量引用 : //常量引用使用场景用来修饰形参

 常量指针、指针常量以及指向常量的指针常量 的区别

 箭头（->）：左边必须为指针；  点号（.）：左边必须为实体

 类的简单使用: 类是对对象的抽象化,对象是对类的实例化

 指针的步长
 *
 */

void test1(){
    int a=10;
    int& b=a; // alias 引用的本质在C+ +内部实现是一一个指针常量, (same to : int* const b=&a)
    b=100;  // same to: (*b)=100
    cout<<a<<endl;
    cout<<b<<endl;

    int aa=1100;
    int* const pp=&a;
//    pp=&aa; // assignment of read-only variable ‘pp’
//    指针常量 : 指针所指向的内存地址不可修改。但p所指向内存地址所对应的值是可以修改的 ( p指向的地址不能变)
    *pp=aa;
    cout<<*pp<<endl;
}

// 数组引用
void test02(){
//    int& b;
    int arr[10];
    for (int i = 0; i <10 ; ++i) {
        arr[i]=i;
    }
    int(& arr2)[10]=arr;  //alias of array, must initialize when declare
    for (int j = 0; j < 10; ++j) {
        cout<<arr2[j]<<endl;
    }

    typedef int(ARR)[10];
    ARR& arr3=arr; // array reference
    ARR* arr_p=&arr; // array pointer
    for (int j = 0; j < 10; ++j) {
        cout<<arr3[j]<<endl;
    }
}
//数组指针,指针数组
void test021(){
    int c[2][4] = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 } };
    int *a[2]; //指针数组
    int (*b)[4]; //数组指针
    b=c;
    cout<<b[1][1]<<endl;//6
    cout<<c[1][1]<<endl;//6
}

//使用指针对数据进行遍历
void test022(){
    int arr[]={1,2,3,4,5};
    // 数组名不是指针,大多数使用到数组名的地方，编译器都会把数组名隐式转换成一个指向数组首元素的指针来处理
    //两种情况下例外
    //1, sizeof(a) ,这将会得到整个数组所占的内存大小
    //2, &a ,运算结果是数组的地址。注意，`数组的地址`和 `数组首元素的地址`是不同的概念，尽管二者存储的值是相同的，但它们的跨度是不同的,
    //    eg:a+1,指针向后移动四个地址空间（int类型数组）；&a+1，指针向后移动元素个数*4 个地址空间
//    int (&arr2)[5]=arr;//数组引用
//    int (* arrP)[5];// 数组指针，不同长度，不同类型的数组的数组指针都不同
//    arrP=&arr2;

//    cout<< typeid(arr).name()<<endl; // A5_i
//    cout<< typeid(p).name()<<endl; // Pi
    for (int i = 0; i < sizeof(arr)/sizeof(int) ; ++i) {
        cout<<*(arr+i)<<endl;
    }
}

void swap(int *a,int *b){
    int temp =*a;
    *a=*b;
    *b=temp;
}

void swap2(int &a,int &b){
    int temp =a;
    a=b;
    b=temp;
}
void test03(){
   int a=100;
   int b=30;
   swap(&a,&b);
   cout<<a<<" "<<b<<endl;

}
void test04(){
    int a=100;
    int b=30;
    swap2(a,b);
    cout<<a<<" "<<b<<endl;
}

int& dowork(){ //不要返回局部变量的引用,此时方法返回的引用指向的对象已经销毁，如果把这个引用赋值给其他变量，会报错
//    int& a=10;
    int a=10;
    cout<<"working"<<endl;
    return a;
}
void test5(){
    dowork();
//    int res=dowork(); // wrong
//    cout<<res<<endl;
}

int& dowork2(){
    static int a=10; // `a` not destroyed when method return
    return a;
}
void test6(){
    int res=dowork2(); // right
    cout<<res<<endl;

    dowork2()=1000; // //如果函数的返回值是引用，那么这个函数调甪可以作为左值~
}

struct Person{
    int age;
};
void allocate(Person** pp){// **pp具体的Person对象  *pp 对象的指针    pp指针的指针
    cout<<sizeof(pp)<<endl;
    *pp=(Person*)malloc(sizeof(Person));
//    (**pp).age=100;
    (*pp)->age=1000;
    cout<<sizeof(**pp)<<endl;
    cout<<sizeof(*pp)<<endl; // point length :8

}
void test7(){
    Person* p=NULL;
    allocate(&p);
    cout<<p->age<<endl;
}

void allocate2(Person* &pp){//利田指针引用开辟空间
    pp=(Person*)malloc(sizeof(Person));
//    pp->age=1000;
    (*pp).age=1000;

}
void test8(){
    Person* p=NULL;
    allocate2(p);
    cout<<p->age<<endl;
}

void test9(){// 常量引用
//    int& ref=10;//error
    const int& ref=10;  // //加入const后，编译器处理方式为: int tmp = 10; const int &xref = tmp;( const int* const xref=&temp )
    int aa=99;
//    ref=aa// error
    int* p=(int*)&ref;
    *p=123;// 只要是分配内存的变量都可以修改变量的值
    cout<<*p<<endl;
}

void showValue(const int& val){//常量引用使用场景用来修饰形参
//    *(int*)&val=99; // can also modify
    cout<<val<<endl;
}
void test10(){
    int a=10;
    showValue(a);
    cout<<a<<endl;
}

void consttest(const char* p){
    // 常量指针: ：p所指向的内存地址所对应的值是const，因此不可修改,但指针所指向的内存地址是可以修改的 (p指向的地址的值不能变)
    p="1";//正确
//    *(p+1)="a";//错误
}
void testconst(char* const p){
    // 指针常量 : 指针所指向的内存地址是const，不可修改。但p所指向内存地址所对应的值是可以修改的 ( p指向的地址不能变)
    char *tmp="13213";
//    p="aaa";;//错误
//    p=tmp;;//错误
    p[1]='a';//正确
    *(p+1)='a';//正确
}

void consttestconst(const char *const p){
    // 指向常量的 指针常量  : 指针所指向的内存地址不可修改同时内存地址所对应的值也不可修改
//    p="aa";//错误
//    p[1]='a';//错误
}
const double pi=3.14;
class Circle{
public:
    int m_R;
    double caculateZC(){
        return 2*pi*m_R;
    }
    void setR(int r){
        cout<< sizeof(this)<<endl; // this  is a pointer ,when access  m_R  by `this` should use `->` operator
        this->m_R=r;
    }
};
void test11(){
    Circle c1;
    c1.m_R=10;
    c1.setR(100);
    cout<<c1.caculateZC()<<endl;
    /**
     * 箭头（->）：左边必须为指针；
        点号（.）：左边必须为实体。
     */
    Circle* c2=(Circle*)malloc(sizeof(Circle));
    c2->setR(11);
    cout<<c2->caculateZC()<<endl;
}

#include <string>
class Student{
public:
    string name;
    int id;
    void setName(string name){
        this->name=name;
    }

    void setId(int id){
        this->id=id;
    }

};

void test12(){
    Student s1;
    s1.setName("zs");
    s1.setId(1);
    cout<< s1.id<<" "<<s1.name<<endl;
}

//指针的步长
void test13(){
    double* arr=new double[10];
    for (int i = 0; i <10 ; ++i) {
        arr[i]=i;
    }
    int* arr2=(int *)arr; // 改变指针的步长 （double* 8--> int* 4）
    for (int j = 0; j <10 ; ++j) {
        cout<<arr2[0]<<endl;
        arr2++; // 指针指向的地址‘向前移动一个步长’
        cout<<arr2<<endl;

    }
}


void test14(){
    int a=123;

    int const  & b=a; //same as : const int  & b=a;
//    b=123;//can not assigned to `b` ,which is a const-qualified type
    cout<<a<<endl;
    cout<<b<<endl;
}


int main(){
//    test1();
//    test02();
//    test021();
//    test03();
//    test04();
//    test5();
//    test6();
//    test7();
//    test8();
//    test9();
//    test10();
//    test11();
//    test12();
    test14();

    return EXIT_SUCCESS;
}

