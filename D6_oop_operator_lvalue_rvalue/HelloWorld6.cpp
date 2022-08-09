#include <iostream>
#include "MyArray.h"
#include <string.h>
#include <string>
using namespace std;

/**
 * 数组类封装 :MyArray ,[]运算符重载
 * 加号运算符重载, 左移运算符重载, 前置后置递增运算符重载, 指针运算符重载(智能指针),赋值运算符重载,关系运算符重载,函数调用运算符重载
 * 不要重载与和或运算符 (重载会失去短路特性)
 *
 *c++的左右值问题
 *   一个对象被用作右值时，使用的是它的内容(值)，被当作左值时，使用的是它的地址。
 *   在C++11中可以取地址的、有名字的是左值
 *   常见的右值: `非引用返回` 的函数返回值、表达式,例如函数int func()的返回值，表达式a+b；不跟对象关联的字面量值，例如true，2，”C”等
 *c++ 左值引用、右值引用
 *    左值引用是具名变量值的别名，而右值引用则是不具名（匿名）变量的别名
 *    int a=10 ; int& aa=a; // aa是变量a所指向的值的别名  ;a是左值，因此aa是左值引用
 *    int&& aaa=a+1;  // 没有变量指向a+1这个表达式的计算结果；a+1是一个表达式，是右值，因此aaa是右值引用
 *    int& a=10; // 左值引用通常也不能绑定到右值
 *    //常量左值引用是个“万能”的引用类型。它可以接受 '非常量左值','常量左值','右值' 对其进行初始化。不过常量左值所引用的右值在它的“余生”中只能是只读的.eg:
 *    int b = 2;        # 非常量左值
 *    const int &c = b; # 常量左值引用绑定到非常量左值，编译通过
 *    const int d = 2;  # 常量左值
 *    const int &e = d; # 常量左值引用绑定到常量左值，编译通过
 *    const int &b =2;  # 常量左值引用绑定到右值，编程通过
 *    // 右值值引用通常不能绑定到任何的左值，要想绑定一个左值到右值引用，通常需要std::move()将左值强制转换为右值
 *    int a;
 *    int &&r1 = c;             # 编译失败
 *    int &&r2 = std::move(a);  # 编译通过
 *
 *    字符串封装 : << >> ,=,[], + == 运算符重载,
 *
 *
 */

void test1(){
    MyArray* arr=new MyArray(10);
    for (int i = 0; i <10 ; ++i) {
        arr->insertLast(i);
    }
    MyArray arr2=*arr; // call copy constructor ,create obj in stack
//    MyArray* arr3=new MyArray(*arr);// call copy constructor ,create obj in heap
//    MyArray* arr4=new MyArray(arr2);// call copy constructor ,create obj in heap

    cout<<arr2[9]<<endl;
    cout<<arr2.get(9)<<endl;
    arr2[9]=99;
    cout<<arr2[9]<<endl;

    delete arr;
}
void test1_1(){
    int* arr=new int[10];
    int& a=arr[9];
    a=19;
    cout<<arr[9];
}

// operator override
class Person{
    friend ostream& operator<<(ostream& cout,Person& p);//friend: 使得运算符重载时可以访问类中的私有数据
    friend Person operator+(int a,Person& p);
    friend Person operator+(Person& p1,Person& p2);
private:
    int a;
    int b;
public:
    Person(int a,int b):a(a),b(b){}
    Person operator+(Person& p){//成员函数重载+号运算符
        return Person(this->a+p.a,this->b+p.b);
    }

    Person operator+(int a){//成员函数重载+号运算符
        return Person(this->a+a,this->b);
    }
};

Person operator+(Person& p1,Person& p2){ //全局函数重载+号运算符
    return Person(p1.a+p2.a,p1.b+p2.b);
}

// Person p5=100+p1;要进行这样的调用，+号的左值是int，因此不能将该运算符重载函数放到Person类中
Person operator+(int a,Person& p){//全局函数重载+号运算符
    return Person(a+p.a,p.b);
}

ostream& operator<<(ostream& cout,Person& p){
    cout<<"a="<<p.a<<" b="<<p.b;
    return cout;
}

void test2(){
    Person p1(1,1);
//    Person p2(2,2);
//    Person p4=p1+100;

    Person p5=100+p1;

//    Person p6=100+Person(3,3);// error, Person(3,3)返回结果时右值，不能对右值取地址，因此Person& pp=Person(3,4);是错误的,
//    可以用常引用来接收: const Person& pp=Person(3,4); 也可以先将Person(3,3)赋值给一个变量，该变量时左值，可以对其取地址

//    Person p3=p1+p2;
//    cout<<p3.a<<"  "<<p3.b<<endl;
//    cout<<p4.a<<"  "<<p4.b<<endl;
//    cout<<p5.a<<"  "<<p5.b<<endl;

    cout<<p5<<endl;
}

class MyInt{
    friend ostream& operator<<(ostream& cout,const MyInt& myInt);
public:
    int a;
    MyInt(int a):a(a){}
    MyInt(const MyInt& myInt){
        cout<<"copy cons"<<endl;
        this->a=myInt.a;
    }
    MyInt& operator++(){ // 前置++ , 效率高，相比于后置少一次临时对象的创建
        this->a+=1;
        return *this; // 当前函数执行完成后，this指针指向的空间不会释放，因此可以返回this指向的对象的引用
    }

//    MyInt operator++(int){//
//        MyInt res=*this;//value copy
//        ++this->a;
//        return res;
//    }
    MyInt operator++(int){//后置++
        MyInt res=*this;//value copy

        ++this->a;
        return res;
    }

};

ostream& operator<<(ostream& cout, const MyInt& myInt){
    cout<<myInt.a;
    return cout;
}

void test3(){
    int t = 1;
    MyInt a(1);
    MyInt& a2=++a;
    MyInt& a3=++a;
    MyInt& a4=++a;

//    cout<<a<<endl; // a=a2=a3=a4=4
//    cout<<a2<<endl;
//    cout<<a3<<endl;
//    cout<<a4<<endl;
//    cout << ++a2 <<endl;

    MyInt b(1);
    MyInt b2=b++;
    cout <<b <<endl;
    cout <<b2 <<endl;
    cout<< b++ <<endl;
    cout<< b++ <<endl;
}

void fun(const int& num){}
void test3_1(){
    fun(123); // error 不能传递一个rvalue, 此时类似于 int& num=123,由于123是右值，没有内存地址，不能对其取引用; 可以将fun的形参加const修饰 ，此时相当于const int& num=123
    int a=123;// 也可以先将123 赋值给一个变量
    fun(a);
}
//左值引用、右值引用
void test3_2(){
    cout << "-------引用左值--------" << endl;
    int a = 5;
    int &add_a(a);// int &add_a =a;

    cout << "   a  =" << a <<"    "<<"    &a = "<<&a<< endl;
    cout << "add_a =" << add_a<<"    "<< "&add_a = " << &add_a << endl;
    a=10;
    cout << "   a  =" << a <<"    "<<"    &a = "<<&a<< endl;
    cout << "add_a =" << add_a<<"    "<< "&add_a = " << &add_a << endl;
    cout << "-----------------------" << endl;

    cout << "-------引用右值--------" << endl;
    int b = 10;
    int && add_b=b+1;
    cout << "   b  =" << b << "    " << "    &b = " << &b << endl;
    cout << "add_b =" << add_b << "    " << "&add_b = " << &add_b << endl;
    add_b++;
    cout <<"b="<<b<< "    add_b++ =" << add_b << "    " << "&add_b++ = " << &add_b << endl;
    cout << "-----------------------" << endl;
}

class Person2{
public:
    int age;
    char* name;
    Person2(char* name){
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
    }
    Person2(int age):age(age){}
    void showAge(){
        cout<<"age:"<<age<<endl;
    }
    ~Person2(){
        cout<<"destructor"<<endl;
        if(this->name!=NULL){
            delete[] this->name;
            this->name=NULL;
        }
    }
    //重载=赋值运算符 ,默认的operator=赋值运算符 进行 `简单的值传递`
    Person2& operator=(Person2& p){
        if(this->name!=NULL){
            delete[] this->name;
        }
        this->name=new char[strlen(p.name)+1];
        strcpy(this->name,p.name);
        return *this;
    }
};

class smartPointer{
public:
    smartPointer(Person2* p):p(p){}
    ~smartPointer(){// 智能指针类的对象开辟到了栈上，当智能指针对象释放时，顺带释放堆上的对象
        if(this->p!=NULL){
            delete this->p;
            this->p=NULL;
        }
    }

    Person2* operator->(){//重载->
        return this->p;
    }
    Person2& operator*(){ // 如果返回值为Person，该方法会创建一个新的Person对象
        return *(this->p);
    }

private:
    Person2* p;
};
///智能指针: 用来托管自定义类型的对象，让对象进行自动的释放
void test4(){
//    Person2* p=new Person2(1);
//    delete p;
    smartPointer sp(new Person2(123));//智能指针类的对象开辟到了栈上，当智能指针对象释放时，顺带释放堆上的对象
    sp->showAge(); // actually: sp->->showAge(); 编译器做的优化
    (*sp).showAge(); // override * operator
}
// 赋值运算符重载
void test5(){
    Person2 p1("aaab1");
    Person2 p2("aaab2");
    Person2 p3("aaab3");
    //一个类默认创建 默认构造、析构、拷贝构造, operator=赋值运算符 进行 `简单的值传递`
    p1=p2=p3;
    cout<<p1.name<<endl;
    cout<<p2.name<<endl;
    cout<<p3.name<<endl;
}

class Person3{
public:
    string name;
    int age;
    Person3(int age,string name):age(age),name(name){}

    bool operator==(Person3& p){
        if(this->name==p.name&&this->age==p.age){
            return true;
        }
        return false;
    }
    bool operator!=(Person3& p){
        if(this->name==p.name&&this->age==p.age){
            return false;
        }
        return true;
    }


};
void test6(){
    Person3 p1(1,"aab");
    Person3 p2(1,"aab2");
    if(p1==p2){
        cout<<"equals"<<endl;
    }
    if(p1!=p2){
        cout<<"unequals"<<endl;
    }
}
class Printer{
public:
    void operator()(string str){ //函数调用运算符重载
        cout<<"print:"<<str<<endl;
    }
};
void test7(){
    Printer printer;
    printer("hello");//仿函数
}
class myadd{
public:
    int operator()(int x,int y){
        return x+y;
    }
};
void test8(){
    myadd add;
    cout<<add(12,34)<<endl;
    cout<<myadd()(1,2)<<endl; //调用匿名对象的重载方法
}

#include "mystring.h"
void test9(){
    MyString str("abc");
//    cout<<str<<endl;
//    cout<<MyString("123")<<endl; // MyString("123") is a rvalue

//    cin>>str;
//    cout<<"new str:"<<str<<endl;

//    MyString str2("cde");
//    MyString str3="";
//
//    str3=str2;
//    cout<<str3<<endl;
//    str3="456678";
//    cout<<str3<<"  size is "<<str3.getSize()<<endl;


//    MyString str4("abd");
//    str4[2]='c';
//    cout<<str4[2]<<endl;
//    cout<<str4<<endl;

    MyString str5="123";
    MyString str6="123";
//    MyString str7=str5+str6+str;
//    cout<<str7<<endl;
//    cout<<str7.getSize()<<endl;
//
//    if(str5==str6){
//        cout<<"equals"<<endl;
//    }
//    if(str5=="1236"){
//        cout<<"equals"<<endl;
//    }







}

int main(){
//    test1();
//    test1_1();
//    test2();
//    test3();
//    test3_2();
//    test4();
//    test5();
//    test6();
//    test7();
//    test8();
    test9();






}
