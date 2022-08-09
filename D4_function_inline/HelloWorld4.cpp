//
// Created by aaab on 11/2/20.
//
/**
 *宏函数 ： 把一些常用的函数调用封装，避免重复函数调用的开销
 *缺陷:在使用宏函数时容易出现错误, 宏函数没有作用域,没有类型制约
 *
 * 函数进行内联编译
 *      在C++中,预定义宏的概念是用内联函数来实现的,而内联函数本身也是一个真正的函数。内联函数具有普通函数的所有行为。
        唯一不同之处在于内联函数会在适当的地方像预定义宏一样展开,所以不需要函数调用的开销。因此应该不使用宏,使用内联函数

        内联函数的确占用空间,但是内联函数相对于普通函数的优势只是省去了函数调用时候的压栈，跳转,返回的开销。
        可以理解为内联函数是以空间换时间

    但是C++内联编译会有一些限制,以下情况编译器可能考虑不会将函数进行内联编译:
        不能存在任何形 式的循环语句
        不能存在过多的条件判断语句
        函数体不能过于庞大
        不能`对函数进行取址操作`
     函数指针是一个特殊的指针，它用于指向函数被加载到的内存首地址，可用于实现函数调用

     函数的默认参数 ,占位参数

     函数重载 (编译器为了实现函数重载,编译器会根据参数的类型和顺序来修改函数名)
        //必须在同一个作用域,函数名称相同,函数的参数个数不同,或者类型不同,或者顺序不同才叫函数重载
        // 返回值不作为函数重载的条件
        /当函数重载碰到了默认参数时候，要注意避免二义性问题
        //const也是可以作为重载的条件

     extern "C"
     //在C++中 函数是可以发生重载的，编译器会把这个函数名称偷偷改变
     //C++中想调用C语言方法

     函数对象(叫仿函数(functor))
        重载函数调用操作符 `()` 的类,使得类对象可以像函数那样调用,其对象常称为函数对象( function object ),即它们是行为类似函数的对象,也叫仿函数(functor)
 *
 *
 */

#include <iostream>
using  namespace std;

#define  my_add(x,y) x+y
#define  my_add2(x,y) (x+y)
#define  my_compare(x,y) x<y?x:y
void test1(){
    int ret=my_add(1,2);
    int ret2=my_add(1,2)*10;  // 1+ 2*20
    int ret3=(my_add(1,2))*10; // (1+2)*10
    int ret4=my_add2(1,2)*10;// (1+2)*10
    cout<< ret<<endl;
    cout<< ret2<<endl;
    cout<< ret3<<endl;
    cout<< ret4<<endl;
}
void test2(){
    int ret=my_compare(12,15)*10; // 12<15? 12:15*10
    cout<<ret<<endl; // 12
}

inline void func();
inline void func(){ // 如果函数实现时候，没有加inline关键字，那么这个函数依然不算内联函数

}
class Circle{
public:
    int m_R;
    double caculateZC(){  //类内部的成员函数默认前面会加inline关键字
        return 2*3.14*m_R;
    }
    void setR(int r){
        cout<< sizeof(this)<<endl; // this  is a pointer ,when access  m_R  by `this` should use `->` operator
        this->m_R=r;
    }
};

int add(int a,int b){
    cout<<"adding"<<endl;
    return a + b;
}
void test3(){// 函数指针是一个特殊的指针，它用于指向函数被加载到的内存首地址，可用于实现函数调用
    int (*func)(int a,int b);// 声明
    func=add;// 赋值
    int res=func(10,20); // 使用
    cout<<res<<endl;

    int (*func2)(int a,int b)=add;// 声明+赋值
    cout<<func2(1,2)<<endl;
}
//函数参数注意事项，
// 如果有一个位置有了默认参数，那么从这个位置开始，从左往后都必须有默认参数
// //如果函数声明里面有了默认参数，那么函数实规时候必须没有,函数声明和实现里只能有一个里有默认参数上
//void fun2(int a=1,int b=2);
void fun2(int a,int b);
void fun2(int a=10,int b=20){
    cout<<"a+b="<<a+b<<endl;
}
void test4(){
    fun2();
    fun2(1);
    fun2(1,2);
}

//占位参数 : 如果有了占位参数，函数调用时候必须要提供这个参数,但是用不到参数
//占位参数可以有默认值 ,同样需要注意默认参数的顺序问题
void fun3(int a ,int,int=1){ }
void test5(){
    fun3(1,2,3);
}

void func4(int& a){
    cout<<"int& a"<<endl;
}
void func4(const int& a){// //const也是可以作为重载的条件
    cout<<"const int& a"<<endl;
}
void test6(){
    int a=12;
    func4(a);
    func4(123);
}

//函数对象(叫仿函数(functor))
class MyPrint{
public:
    string name;
    int count=0;
    void operator()(int n){
        cout<<"print:"<<this->name<<" pirnt: "<<n<<endl;
        count++;
    }
    MyPrint(string name):name(name){}
};

void doPrint(MyPrint &p,int num){ // //函数对象作为参数
    p(num);

}
void test7(){

//    MyPrint("aaabde ")(123);
//
    MyPrint p("a");
//    p(11);
//    p(11);
//    p(11);
//    cout<<p.count<<endl;  //函数对象可以记录内部状态

//    doPrint(p,12345);

};

int main(){
//    test1();
//    test2();
//    test3();
//    test4();
//    test5();
//    test6();
    test7();

    return EXIT_SUCCESS;
}
