#include <iostream>
#include <string>
using namespace std;

/**
 * C++模板
 *     函数模板与普通函数的区别以及调用规则
 *     函数模板的局限性:解决方案：运算符重载 ; 具体化函数模板的自定义数据类型
 *     函数模板的两次编译机制
 *        1、在声明的地方对模板代码本身进行编译；（对其进行词法、语法、句法的分析）
 *        2、在调用的地方对参数替换后的代码进行编译。（生成具体的函数（或类））
 *     类模板
 *         类模板做函数的参数(three ways)
 *         类模板的继承
 *         类模板的类外实现成员函数
 *         类模板的分文件编写 :  类模板不要份文件编写，使用类内声明，类外实现的方式
 *         友元碰到类模板
 *
 *     基于模板的MyArray封装
 *
 *
 */

template <class T>// //告诉编译器下面的这个函数、类、变量的声明中，T为一个通用类型
void myswap(T& x,T& y){
    T temp=x;
    x=y;
    y=temp;
}
//T a; //不能再使用前面声明的类型参数T了

template <typename Y>
void myswap2(){
}

void test(){
    int a=1;
    int b=2;
    myswap(a,b);
    cout<<a<<" "<<b<<endl;

    double x=1.2;
    double y=1.3;
    myswap(x,y);
    cout<<x<<" "<<y<<endl;

//    myswap2();// error //必须要推测出Y的具体类型才可以使用，此时编译器无法推测出Y的具体类型
    myswap2<double>();//可以显示指定类型
}

template <class T>
void mysort(T arr[],int len){
    for (int i = 0; i <len ; ++i) {
        int max=i;
        for (int j = i+1; j < len; ++j) {
            if(arr[max]<arr[j]){
                max=j;
            }
        }
        if(max!=i){
            myswap(arr[i],arr[max]);
        }
    }
}
template  <class T>
void print_arr(T arr[],int len){
    for (int i = 0; i <len ; ++i) {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}
void test2(){
    int arr[]={3,345,234,-34,-4};
    mysort(arr, sizeof(arr)/ sizeof(int));
    print_arr(arr,sizeof(arr)/ sizeof(int));

    char arr2[]="abcd";
    mysort(arr2, sizeof(arr2)/ sizeof(char)-1);
    print_arr(arr2,sizeof(arr2)/ sizeof(char)-1);
    char arr3[]={'a','b','3','d'};
    mysort(arr3, sizeof(arr3)/ sizeof(char));
    print_arr(arr3,sizeof(arr3)/ sizeof(char));
}

//函数模板与普通函数的区别以及调用规则
template <class T>
T myadd(T a,T b){
    return a+b;
}
int myadd2(int a,int b){
    return a+b;
}
void test3(){
    int a=10;
    char b='c';
    myadd2(a,b);// 普通函数可以进行隐式类型转换
//    myadd(a,b);// error 函数模板不可以进行隐式类型转换
}
template <class T>
void myprint(T a,T b){
    cout<<"template method"<<endl;
}
template <class T>
void myprint(T a,T b,T c){ //函数模板可以发生重载
    cout<<"template method"<<endl;
}
void myprint(int a,int b){
    cout<<"commom method"<<endl;
}
void test4(){
    int a=10;
    int b=10;
    myprint(a,b); //1、如果出现重载优先使用 普通函数调用，如果没有实现，出现错误
    myprint<>(a,b);//2、如果想强制调用模板，那么可以使用空参数列表
}

// 函数模板的局限性
class Person{
    public:
        string name;
        int age;
        Person(string name,int age):name(name),age(age){
        }
        Person();
//        bool operator==(Person& p){
//            if(this->name==p.name&&this->age==p.age){
//                return true;
//            }
//            return false;
//        }
    };
class Student:public Person{
    Student(){
    }
};
template <class T>
bool  my_cmp(T& a,T& b){
    return a==b;
}
template <> bool my_cmp<Person>(Person& p1,Person& p2 ){// 当模板方法 my_cmp调用时的实参为Person类型，则调用该模板方法
    cout<<"person cmp template function call"<<endl;
}

void test5(){
    Person p1("abj",12);
    Person p2("abj",13);
    my_cmp(p1,p2);
}

//类模板
template <class U,class T=string>// 类模板可以有默类型
class Person2{
    public:
        U name;
        T age;
        Person2(U name, T age){
            this->name=name;
            this->age=age;

        }
    Person2(U name){
        name.Hello(); //由于该类是模板类，因此编译器此时只是做简单的语法检查，
        this->Hello();// 并不关心this有无Hellow方法，也不关心U类型的name有无Hello方法
        this->name=name; //由于后面在使用该模板类时没有用到该方法，因此不会对该方法使用具体的类型进行重新编译，所以不会去检查this有没有Hello这个方法，也不会检查name变量有没有Hello这个方法
    }
        void showinfo(){
            cout<<this->name<<this->age<<endl;
        }
    };
void test6(){
    Person2<string,int> p("aaab",123);  //类模板使用时，必须显示指定类型
//    Person2<string,int> p2("aaab");
    p.showinfo();
}

//类模板做函数的参数
void doWork(Person2<string ,int>& p){//1.指定类模板的传入类型, 参数类型限制最高
    p.showinfo();
}
template <class T1,class T2>
void doWork2(Person2<T1,T2>&p){// 2 参数模板化 (doWork2是个函数模板)
    cout<<typeid(T2).name()<<endl;
    p.showinfo();
}
template <class T>
void doWork3(T& p){// 整体参数化 ,参数类型限制最低
    cout<<typeid(p).name()<<endl;
    p.showinfo();
}
void test7(){
    Person2<string ,int> p("aa",123);
    doWork(p);

    Person2<string,string> p3("aaa","bbb");
    doWork2(p3);
//    doWork(p3);// type mismatch ,require <string ,int>

    doWork3(p);
    doWork3(p3);
}

//类模板的继承
template <class T>
class Base{
public:
    T a;
    Base(T a):a(a){}
    Base(){
        cout<<"base cons"<<endl;
    };
};

class Child:public Base<string>{//child继承与base告诉base中的T的类型(Base此时为具体类)

};
template <class T1,class T2>
class Child2:public Base<T2>{//Base此时仍为模板类
public :
    T1 b;
    Child2(T1 b,T2 a):b(b),Base<T2>(a){} // 初始化列表中:初始化本类的成员，同时调用模板父类的有参构造函数
    Child2(T1 b);
    void show();
};
//类模板类外实现成员函数
template <class U,class V> // 此处的模板类型参数可以不用T1,T2
Child2<U,V>::Child2(U b): b(b),Base<int>(123){}
template <class T1,class T2>
void Child2<T1,T2>::show() {
    cout<<this->a<<"  "<<this->b<<endl;
}

void test8(){
    Child2<string,int> c("a55a",12343);
    cout<<c.Base::a<<"  "<<c.b<<endl;
    cout<<c.a<<"  "<<c.b<<endl;
}


//类模板的分文件编写
//由于类模板的二次编译机制，导致在include 头文件的时候不会创建类模板中函数的实现，而在调用类模板中函数的时候找不到其实现，因此会报连接错误
//类模板不要分文件编写，将类模板的声明和实现写在一个文件中.使用类内声明，类外实现的方式
#include "Person5.hpp"
void test9(){
    Person5<string,string> p("a","b");
    p.show();
}

//友元碰到类模板
template <class T1,class T2>
class Person6;// 友元函数类外实现
template <class T1,class T2>
void show2(Person6<T1,T2>& p);// 友元函数类外实现


template <class T1,class T2>
class Person6{
    friend void show(Person6<T1,T2>& p){//友元函数类内实现
        cout<<p.a<<"  "<<p.b<<endl;
    }
    friend void show2<>(Person6<T1,T2>& p);// 友元函数类外实现

public:
    Person6(T1 a,T2 b):a(a),b(b){};
    Person6(){}
    void print(){
        cout<<this->a<<"  "<<this->b<<endl;
    }
private :
    T1 a;
    T2 b;
};
template <class T1,class T2>
void show2(Person6<T1,T2>& p){ // // 友元函数类外实现
    cout<<p.a<<",,,"<<p.b<<endl;

}

void test10(){
    Person6<string ,int> p("a",123);
    show(p);
    show2(p);
}

#include "MyArray.hpp"
void test11(){
//    MyArray<int> arr(100);
////    MyArray<int> arr2=100;  //use explicit to avoid this
//
//    for (int i = 0; i < 10; ++i) {
//        arr.insertLast(i);
//    }
//    for (int j = 0; j <arr.getSize() ; ++j) {
//        cout<<arr[j]<<endl;
//    }
//
//    for (int i = 0; i < 10; ++i) {
//        arr[i]=arr[i]+100;
//    }
//    for (int j = 0; j <arr.getSize() ; ++j) {
//        cout<<arr[j]<<endl;
//    }

//    MyArray<Person6<string,string>*> arr(100);
//
//    for(int i = 0; i < 10; ++i) {
//        arr.insertLast(new Person6<string,string>("a","b"));
//    }
//    for (int j = 0; j <arr.getSize() ; ++j) {
//        arr[j]->print();
//    }

    MyArray<Person6<string,string>> arr(100);  // need default constructor of class Person6
    for(int i = 0; i < 10; ++i) {
        arr.insertLast(Person6<string,string>("a","b"));
    }
    for (int j = 0; j <arr.getSize() ; ++j) {
        arr[j].print();
    }
}

int main(){
//    test();
//    test2();
//    test4();
//    test5();
//    test6();
//    test7();
//    test8();
//    test9();
//    test10();
//    test11();

    return EXIT_SUCCESS;

}

