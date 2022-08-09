//
// Created by aaab on 11/10/20.
//
#include <iostream>
#include <string>
#include <string.h>
#include <stdexcept>
using namespace std;

/**
 * 类型转换
 *    静态类型转换(static_cast) : 父与子类型转换,没有父子关系的类型不能转换 ,指针，引用类型都可以进行 静态类型转换
 *    动态类型转换(dynamic_cast):dynamic_ cast非常严格，失去精度或者不安全都不可以转换;如果发生了多态，那么dymamic_ _cast 可以让基类转为派生类，向下转换
 *    常量转换(const_ cast):
 *
 * 异常(Exception)
 *     自定义异常
 *     栈解旋:从try开始到throw 抛出异常之前所有栈上的对象都会被释放这个过程称为栈解旋
 *     异常接口声明: 如果让方法想抛出特定的类型异常，可以利用异常的接口声明
 *     异常变量生命周期:
 *     异常的多态使用
 *     C++标准异常库 :基于多态
 *
 *  IO
 *     standard io , file io ,
 */

class Base{
public:
//    virtual void show();
    virtual void show()=0;
};
class C:public Base{
public:
    virtual void show(){

    }
};
void test1(){
    char a='a';
    double d= static_cast<double>(a);
    cout<<d<<endl;
    Base* b=NULL;
    C* c=NULL;
    Base* bb= static_cast<Base*>(c);
    C* cc=static_cast<C*>(b);
}
void test2(){
//    char a='a';
//    double d= dynamic_cast<double>(a);// dynamic_ cast非常严格，失去精度或者不安全都不可以转换
    Base* b=NULL;
    C* c=NULL;
    Base* bb=dynamic_cast<Base*>(c);
    C* cc=dynamic_cast<C*>(b); //error

    Base* b2=new C;
    C* c3= dynamic_cast<C*>(b2);// 如果发生了多态，那么dymamic_ _cast 可以让基类转为派生类，向下转换
}
void test3(){
    const int* p=NULL;
    int* p2=const_cast<int*>(p);
    const int* p3=const_cast<int*>(p2);
   //不能对非指针或非引用的变量进行转换
//    const int a=123;
//    int b=const_cast<int>(a);
}

class MyException{
public:
    string msg;
    MyException(string msg):msg(msg){
        cout<<"my execption constructor"<<endl;
    }
    MyException(const MyException& e){
        cout<<"my execption copy constructor"<<endl;
    }
    ~MyException(){
        cout<<"my execption destructor"<<endl;
    }
    virtual void print(){
        cout<<"my exception:"<<this->msg<<endl;
    }
};
class MySubException:public MyException{
public:
    MySubException(string msg):MyException(msg){
        cout<<"my sub exception constructor"<<endl;
    }
    ~MySubException(){
        cout<<"my sub execption destructor"<<endl;
    }
    virtual  void print(){
        cout<<"my sub exception:"<<this->msg<<endl;
    }
};
int divide(int a,int b) throw(MyException,int, MyException*){// 异常接口声明,此时只能抛出MyException ,int类型的异常
    if(b==0){
//        throw -1; // 抛出int类型的异常
//        throw -1.01; // 抛出double类型的异常
//        throw MyException("by zero");//抛出匿名异常对象
//        throw new MyException("by zero");//抛出匿名异常对象, 匿名对象创建在堆区
    throw MySubException("by zero");
        //此处的代码不可达
    }

    return a/b;
}
void test4(){
    try {
        divide(10,0);
    }catch (int){
        cout<<"int exception"<<endl;
    }catch (double& d){
        cout<<"double exception:"<<d<<endl;
        throw;//如臬不想处理这个异常，可以继续向上抛出
    }
    catch (MyException& e){//抛出匿名异常对象不会通过值拷贝，创建异常对象e
//    }catch (MyException e){// 抛出匿名异常对象不会通过值拷贝，创建异常对象e
        e.print();
    }
//    catch (MyException* e){ // for : new MyException();
//        e->print();
//        delete e; // clean up manually
//    }
    catch (...){
        cout<<"others exception"<<endl;
    }
}

//C++标准异常库
class MySystemException:public exception{
public:
    string msg;
    MySystemException(string msg):msg(msg){
        cout<<"MySystemException constructor "<<this->msg<<endl;
    }
    ~MySystemException(){
        cout<<"MySystemException destructor "<<endl;
    }
    virtual const char* what() const noexcept { // 常函数
        return this->msg.c_str();
    }
};

void dowork2(){
    throw MySystemException("system error");
}
void test6(){
    try {
        dowork2();
    }catch (MySystemException& e){
        cout<<"what:"<<e.what()<<endl;
    }
}
void test7(){
//    char buff[1024];
//    cin.get(buff,1024); //不会把换行符拿走，遗留在缓冲区中
//    char c=cin.get();
//    if(c=="\n"){
//
//    }

//    char buff[1024];
//    cin.getline(buff,1024);//会读取换行符

//    cin.ignore();//没有参数。忽略第一个字符
//    char c=cin.get();

//    char c=cin.peek();// 查看一个char，但是不从缓冲区取出

//    char c=cin.get();
//    cin.putback(c); // 缓冲区头部放入一个字符
//    cin.putback(c);
//    char buff[1024];
//    cin.getline(buff,1024);
//    cout<<buff<<endl;
}
void test8(){
    cout<<"please enter :"<<endl;
    char c=cin.peek();
    if(c>='0'&&c<='9'){ //judge  if c is a number
        int num;
        cin>>num;
        cout<<"number is:"<<num<<endl;
    }else{
        char buf[1024];
        cin>>buf;
        cout<<"str is:"<<buf<<endl;
    }
}
//file io
#include <fstream>
void test10(){

    ofstream ofs("./test.txt",ios::out);
    if(!ofs.is_open()){
        cout<<"open ofs failed"<<endl;
        return;
    }
    ofs<<"abc"<<endl;
    ofs<<"def"<<endl;
//    ofs.close();

}
void test11(){
    ifstream ifs;
    ifs.open("./test.txt",ios::in);
    if(!ifs.is_open()){
        cout<<"open ifs failed"<<endl;
    }
    //read data
//    char buf[1024];
//    while(ifs>>buf){
//        cout<<buf<<endl;
//    }

//    char buf2[1024];
//    while(!ifs.eof()){
//        ifs.getline(buf2,sizeof(buf2));
//        cout<<buf2<<endl;
//    }

//    char c;
//    while((c=ifs.get())!=EOF){
//        cout<<c;
//    }




}



int main(){
//    test1();
//    test2();
//    test3();

//    try {
//        test4();
//    }catch(double){
//        cout<<"catch double in main"<<endl;
//    }

//    test5();
//    test6();
//    test7();
//    test8();
//    test9();
//    test10();
    test11();

    return EXIT_SUCCESS;
}

