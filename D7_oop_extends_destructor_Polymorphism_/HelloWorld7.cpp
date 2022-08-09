//
// Created by aaab on 11/9/20.
//
#include <iostream>
#include <string.h>
using namespace std;

/**
 * extends : 继承减少代码重复内容
 *      继承方式 : public,private,protected, 子类是不会继承父类的构造函数,折构函数, operater=运算符重载函数
 *      继承中的对象模型
 *      继承中的构造和析构顺序: 子类创建对象时，先调用父类的构造，然后调用自身构造,析构顺序与构造顺序相反
 *      继承中的同名成员处理: 子类调用父类的方法，访问父类的变量 ( Base:: )
 *      继承中的静态成员（变量/函数）处理
 *      多继承 ,菱形继承的解决方案利用虚继承
 *
 *
 * 多态 :父类的引用或指针指向子类对象|
 *     静态联编和动态联编
 *     抽象类和纯虚函数 : 带有纯虚函数的类为抽象类
 *
 *     (父类构造函数-> 成员变量构造函数-> 本类构造函数-----本类析构函数-> 成员变量析构函数->父类析构函数)
 *     析构函数：编译器先调用自定义析构函数（如果有的话），释放一些引用的堆内存，系统资源等等；然后，系统对类的一些'普通数据'所占用的内存进行释放(调用 成员变量析构函数以及 父类析构函数)
 *     虚析构: 解决通过父类指针指向子类对象,导致子类析构函数无法调用的问题
 *     纯虚析构函数: 需要声明还需要实现类内声明，类外实现;如果函数中出现了纯虚析构函数，那么这个类也算抽象类
 *
 *     向上类型转换和向下类型转换: (基类转派生类,不安全,派生类对象指针比基类对象指针操纵的内存空间更大了（派生类中有基类没有的成员变量）)
 *
 *
 *     多态案例
 *         头文件循环引用的问题 :使用#pragma once或#ifndef, 同时将所有头文件需要用到的自定义类都在定义前声明一下,保证头文件引用的次序不会影响编译结果
 *
 *     内存地址空间的重复释放会导致错误
 *
 */

class BasePage{
public:
    int a=1;
    void header(){
        cout<<"header"<<endl;
    }
    void tailer(){
        cout<<"tailer"<<endl;
    }
    int getC(){
        return c;
    }

protected:
    int b=2;
private:
    int c=3;
};
class News :public BasePage{
public:
    void getMember(){
//        cout<<b<<endl;//b is protected in News2
//        cout<<a<<endl;//a is public in News2
//        cout<<c<<endl;//error
        int c=getC(); // we can access private member `c` ,through public method in Parent class
        cout<<c<<endl;
    }
};

class News2 : protected BasePage{

    void getMember(){
        cout<<b<<endl;//b is protected in News2
        cout<<a<<endl;//a is protected in News2
//        cout<<c<<endl;//error
    }
};
class News3 : private BasePage{
    void getMember(){
        cout<<a<<endl;// a is private in News3
        cout<<b<<endl;// b is private in News3
//        cout<<c<<endl;//error
    }
};

class Game: public BasePage{
public:
    void content(){
        cout<<"gaming"<<endl;
    }
};

void test1(){
    News n1;
    n1.a;
    n1.getMember();
//    n1.b; //error
//    n1.c; //error

    News2 n2;
//    n2.a; // error
//    n2.b; //error
//    n2.c; //error
}
//继承中的对象模型
class Base{
public:
    int m_a;
    static int m_static_a;
    Base(){
        cout<<"base cons"<<endl;
    }
    Base(int a):m_a(a){

        cout<<"base cons with args"<<endl;
    }
    void fun(){
        cout<<"fun in Base class"<<endl;
    }
    void fun(int a){
        cout<<"fun (int a) in base class"<<endl;
    }
    static void fun_s(){
        cout<<"fun_s in Base class"<<endl;
    }
    static void fun_s(int a){
        cout<<"fun_s (int a) in base class"<<endl;
    }
    ~Base(){
        cout<<"base des"<<endl;
    }
protected:
    int m_b;
    static int m_static_b;
private:
    int m_c;
    static int m_static_c;
};
int Base::m_static_a=123;
int Base::m_static_b=123; // 相当与在类内赋值
int Base::m_static_c=123; // 相当与在类内赋值

class Base2{
public :
    int m_e;
    int m_f;
    int m_a;
};
class Son: public Base{
public :
    int m_d;
    static int m_static_a;
    int m_a=99;
    Son():Base(12){//利用初始化列表方式显示调用父类有参构造 ,(默认子类先调用父类的默认构造函数)
        Base::fun();// call function defined in Base class
        cout<<"son cons"<<endl;
    }
    Son(int d,int a):m_d(d),Base(a){//利用初始化列表方式,初始化成员变量,并显示调用父类有参构造
        cout<<"son cons with args"<<endl;
    }
    void fun(){
        cout<<"fun in son class"<<endl;
    }
    static void fun_s(){
        cout<<"fun_s in son class"<<endl;
    }

    ~Son(){
        cout<<"son des"<<endl;
    }
};
int Son::m_static_a=12345;
void test2(){
    // 子类会继承父类中所有的内容,包括了私有属性
    cout<< sizeof(Son)<<endl; //16  :子类中会继承父类的私有成员，只是被编译器给隐藏起来，访问不到私有成员
}
//继承中的构造和析构顺序 :  base cons->son cons->son des->base des
void test3(){
//    Son s1;
    Son s2(12,13);
    cout<<s2.m_a<<" " <<s2.m_d<<endl;
}
//继承中的同名成员处理
void test4(){
    Son s2(12,13);
    cout<<s2.m_a<<endl; // 如果子类中有与父类同名的变量，优先调用子类的
    cout<<s2.Base::m_a<<endl;// 通过 Base类的作用域的方式可以访问父类的变量
    s2.fun();
    s2.Base::fun();// 通过 Base类的作用域的方式可以调用父类的方法

//    s2.fun(12); ////如果子类与父类的成员函数名称相同，子类会把父类的所有的同名functions都隐藏掉
    s2.Base::fun(12);////想调用父类的方法，必须加作用域
}

//继承中的静态成员处理
void test5(){
    cout<<Base::m_static_a<<endl;
    cout<<Son::m_static_a<<endl;
//    cout<<Son::m_static_b<<endl; // can not access protected static member outside class
//    cout<<Son::m_static_c<<endl;// can not access private static member outside class

    Son::fun_s();
//    Son::fun_s(10);// error  ///如果子类与父类的成员函数名称相同，子类会把父类的所有的同名functions都隐藏掉 (包括静态方法)
    Son::Base::fun_s(10);
    Son::Base::fun_s();
}

//多继承
class Son2:public Base,public Base2{

};
void test6(){
    cout<< sizeof(Son2)<<endl;
    Son2 s2;
//    cout<<s2.m_a<<endl;//多继承中很容易引发二义性,通过指定特定父类的作用域来解决
    cout<<s2.Base::m_a<<endl;
    cout<<s2.Base2::m_a<<endl;
}
//菱形继承的解决方案利用虚继承
class Animal{
public:
    int age;
};
//class Sheep: public Animal{};
//class Tuo :public Animal{};
class Sheep: virtual  public Animal{};
class Tuo :virtual public Animal{};
class SheepTuo:public Sheep,public Tuo{

};
void test7(){
//    SheepTuo st;
////    st.age=123;// ambiguous
//    st.Sheep::age=123;
//    st.Tuo::age=456;
//    cout<<st.Sheep::age<<"  "<<st.Tuo::age<<endl; // SheepTuo的对象中会保存两个age变量，浪费空间

    //利用虚继承解决后
    SheepTuo st;
    st.age=123;// only exactly one variable of name age
    st.Sheep::age=123;
    st.Tuo::age=456;
    cout<<st.Sheep::age<<"  "<<st.Tuo::age<<endl; // 456,456 // SheepTuo的对象中此时只会保留一个age变量（通过 vbptr:（虚基类指针）的方式使得Sheep类和Tuo类共享一个age变量
}


//静态联编和动态联编
class Animal2{
public:
    virtual void doSpeak() {// 虚函数来实现动态编联 (基于 vfptr:virtual function pointer来实现)
        cout << "animal speak" << endl;
    }
};
class Cat :public Animal2{
public:
    void doSpeak(){
        cout<<"cat speak"<<endl;
    }
};
//调用Speak ，doSpeak函数的地址早就绑定好了， 早绑定，静态联编，编译阶段就确定好了地址
//如果想调用猫的speak,不能提前绑定好函数的地址了，所以需要在运行时候再去确定函数地址:动态联编
// 写法PoSpeak方法改为虚函数
void speak(Animal2& animal){
    animal.doSpeak();
}
void test8(){
//    cout<< sizeof(Animal2)<<endl; //8 : the size of vfpter is 8 Bits
//    Cat cat;
//    speak(cat);
//    //多态 :1父类的引用或指针指向子类对象|
//    Animal2* cat2=new Cat;
//    cat2->doSpeak();
//    Cat cat3;
//    Animal2& animal=cat3;
//    animal.doSpeak();
}

// 抽象类和纯虚函数
class Calculator{
public:
    virtual int getResult()=0; //纯虚函数: 如果父类中有了纯虚函数,子类继承父婆， 如果子类要实例化,就必须要实现纯虚函数, 带有纯虚函数的类为抽象类
    Calculator(int x,int y):x(x),y(y){}
protected:
    int x;
    int y;
};
class AddCalculator:public Calculator{
public:
    AddCalculator(int x,int y):Calculator(x,y){}
    virtual int getResult(){ //子类中virtual关键字可写可不写,建议写
        return this->x+this->y;
    }
};
class MultiplyCalculator:public Calculator{
public:
    MultiplyCalculator(int x,int y):Calculator(x,y){}
    virtual int getResult(){// 子类中virtual关键字可写可不写,建议写
        return this->x*this->y;
    }
};
void test9(){
    MultiplyCalculator calculator(11,11);
    cout<<calculator.getResult()<<endl;
}

//虚析构和纯虚析构函数
class Animal3{
public:
    virtual void doSpeak() {
        cout << "animal speak" << endl;
    }
    Animal3(){
        cout<<"animal constructor"<<endl;
    }
//    virtual ~Animal3(){ //在父类中声明虚析构函数
//        cout<<"animal destructor"<<endl;
//    }
    virtual  ~Animal3()=0;//纯虚析构函数: 需要声明还需要实现类内声明，类外实现;如果函数中出现了纯虚析构函数，那么这个类也算抽象类
};
Animal3::~Animal3() { //纯虚析构函数: 需要声明还需要实现类内声明，类外实现;
    cout<<"animal destructor"<<endl;
}
class Fish :public Animal3{
public:
    char* name;
    Fish(char* name){
        cout<<"fish constructor"<<endl;
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
    }
    void doSpeak(){
        cout<<"fish speak"<<endl;
    }
    ~Fish(){
        cout<<"fish destructor"<<endl;
        if(this->name!=NULL){
            delete[] this->name;
            this->name=NULL;
        }
    }
};
// 虚析构:
void test10(){
//    Fish f=Fish("aaab");// 先调用Animal的析构函数，再调用Fish的析构函数
////    Animal3 animal3=f;// 根据Fish对象又生成了一个Animal3对象，此时调用animal3的doSpeak为 ‘animal speak’ (Animal3为非抽象类的情况下)
//    Animal3& animal3=f;
//    animal3.doSpeak();// animal speak

//    Fish f=Fish("aaab");
//    Animal3& animal3 =f; //此时没有因为转型生成额外的animal对象
//    animal3.doSpeak();// fish speak

    Animal3* animal3=new Fish("aaab");
    animal3->doSpeak();// fish speak
    delete animal3; // 此时调用的是Animal3的析构函数，并没有调用Fish的析构函数，所以会导致子类中资源释放不干净的问题  (需要在父类中声明虚析构函数来解决)
}

//多态案例 pk game
#include "Hero.h"
#include "Weapon.h"
#include "Knife.h"
#include "DragonSword.h"
#include "Monster.h"
void test11(){

    Monster* monster=new Monster;
    Hero* hero=new Hero;
    cout<<"please choose"<<endl;
    cout<<"1,none"<<endl;
    cout<<"2. knife"<<endl;
    cout<<"3. dragonSword"<<endl;
    int oper=0;
    cin>>oper;
    switch(oper){
        case 1:
            break;
        case 2:
            hero->equipWeapon(new Knife);
            break;
        case 3:
            hero->equipWeapon(new DragonSword);
            break;
    }
    getchar();//输入缓冲区里有个回车，多获取一次值
    int count=1;
    while(true){
        getchar();
        cout<<"game round "<<count<<endl;
        if(hero->hp<=0){
            cout<<"hero is die, game over"<<endl;
            break;
        }
        hero->attack(monster);

        if(monster->hp<=0){
            cout<<"monster is die, game over"<<endl;
            break;
        }

        monster->attack(hero);
        cout<<"current: hero hp:"<<hero->hp<<"  monster hp:"<<monster->hp<<endl;
        count++;
    }

    delete monster;
    delete hero;
}

class Q{
public:
    int a;
    Q(){
        cout<<"cons Q"<<endl;
    }
    Q(int a):a(a){
        cout<<"cons a Q"<<endl;
    }
    ~Q(){
        cout<<"Des Q"<<endl;
    }
};
class TT{
public:
    TT(){
        cout<<"tt cons"<<endl;
    }
    virtual  ~TT(){
        cout<<"tt des"<<endl;
    }
};
class T: public TT{
public:
    int  a=1;
    Q q;

    T(){
        cout<<"cons T"<< endl;
    }
     ~T(){
        cout<<"des T"<< endl;
    }

};
// 内存地址空间的重复释放会导致错误
void test12(){
//    int* arr=new int[12];
//    int * arr2=arr;
//    delete arr;
//    delete arr2;

    // 父类构造函数-> 成员变量构造函数-> 本类构造函数-----本类析构函数-> 成员变量析构函数->父类析构函数
    TT* t= new T;
//    T* t= new T;
    delete t;
    cout<<" "<<endl;





}

int main(){
//    test1();
//    test2();
//    test3();
//    test4();
//    test5();
//    test6();
//    test7();
//    test8();
//    test9();
//    test10();
//    test11();
    test12();
}

