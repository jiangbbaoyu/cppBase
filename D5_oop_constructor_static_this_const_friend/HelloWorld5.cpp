//
// Created by aaab on 11/5/20.
//

#include <iostream>
#include <string>
#include <string.h>
using namespace std;

/**
 *
 * //C语言封装属性和行为分开处理了, 类型检测不够完善
 * // in c++ ,struct和class是一个意思，唯一的不同 默认权限 ，struct是public, 但是class默认权限是private
 *
 * 构造函数 ,析构函数
 *   构造函数调用顺序 (父类构造函数-> 成员变量构造函数-> 本类构造函数-----本类析构函数-> 成员变量析构函数->父类析构函数)
 *  //按照参数进行分类 无参构造函数(默认构造函数) 有参构造函数
 *  //按照类型进行分类 普通构造函数拷贝构造函数
 * 拷贝构造函数调用时机, 构造函数的调用规则
 * 深拷贝和浅拷贝
 * 初始化列表
 * 类对象作为类成员时候，构造顺序:先将类对象构造(按照成员变量的声明顺序)，然后构造自己， 析构的顺序是相反的
 * explicit关键字修饰构造函数，防止隐式类型转换
 *
 * 在运行时动态分配堆区内存 (new):
 *  它带有内置的长度计算、类型转换和安全检查
 *  call the corresponding constructor
 *  需要相应的delete 来释放堆内存
 *
 *  静态成员变量 ,静态成员函数
 *
 *  singleton
 *  字节对齐
 *  this pointer : this指针指向调用成员函数的对象的地址 (this指针是指针常量，指针指向的地址不能改变，指向的地址的值可以改变)
 *  空指针访问成员函数
 *  常函数与常对象
 *  友元函数: 全局函数做友元函数,成员函数做友元函数, 友元类
 *
 *
 */

class Person{

public:

    Person(int a){// constructor 与类名相同，没有返回值.不写void,可以发生重载(可以有参数)
        this->age=a;
        cout<<"constructor"<<a<<endl;
    }
    Person(){
        cout<<"constructor"<<endl;
    }

    Person(const Person &p){ // 拷贝构造函数
        cout<<"copy constructor  "<<endl;
        this->age=p.age;
    }

    ~Person(){////析构函数写法,与类名相同类名前面加一一个符号“~”,也没有返回值，不写void， 不可以有参数(不能发生重载)
        cout<<"person destructor"<<endl;
    }
    int age;
};
void test1(){
//    Person p; //默认构造函数不要加() Person p3(); //编译器认为这行是函数的声明
//    Person p1(32);
//    Person p2(p1);

//    Person p=Person(32);
//    Person p2=Person(p);
//    Person(100);//匿名对象,如果编译器发现了对象是匿名的，那么在这行代码结束后就释放这个对象
//    Person(p1); //不能用 copy构造函数初始化匿名对象
    //隐式类型转换
//    Person p7=123; //相当于调用了Person p7 = Person(123)
//    Person p8=p7;//Person p8=Person(p7);

}

void doWork(Person p1){ // Person p1=Person(p)
}
//static Person p;
Person doWork2(){
//    return Person(12);
//    return p;
}
Person& doWork3(){
//    return p;
}
// 拷贝构造函数调用时机
void test2(){
    Person p;
    Person p2(p);//1、用已经创建好的对象来初始化新的对象 same like Person p5=p;
    doWork(p);//2.以值传递的方式给函数参数传值
    Person p3=doWork2();//3,以值方式(create a new Person obj) (可能会有编译器优化，不会调用copy constructor)
    Person& p4=doWork3();// non new Person obj created



}
//构造函数的调用规则
void test3(){
//    Person p;  // 1,当我们提供了有参构造函数，那么系统就不会提供默认构造函数
//    Person p2(p);  // 2, 但是系统还会提供默认拷贝构造函数,对类中非静态成员属性简单值拷贝 ;
                    //    3. 当我们提供了拷贝构造，系统就不会提供其他构造函数
}

class Person2{
public:
    char* name;
    int age;
    Person2(char* name,int age){
        this->name=(char *)malloc(strlen(name)+1);
        strcpy(this->name,name);
    }
    Person2(int age):age(age){//初始化列表 this->age=age; 如果成员变量是引用类型，该类型需要提供带有相应类型参数的构造函数
    }
    /**
     * 系统默认提供的拷贝构造会 进行简单的值拷贝。
     * 如果属性里有指向堆区空间的数据( char* ),那么简单的浅拷贝会复制内存地址，在释放内存的时候导致重复释放内存的异常
     */
    Person2(const Person2& p){ //deep copy
        this->age=p.age;
        this->name= (char *)malloc(strlen(p.name)+1);// 对于引用类型的字段，重新分配堆内存空间，然后再对新的堆内存空间赋值
        strcpy(this->name,p.name);

    }

    ~Person2(){
        if(name!=NULL){
            free(name);
            name=NULL;
        }
        cout<<"destructor"<<endl;

    }

};

void test4(){
    Person2 p1("zs",12);
    Person2 p2(p1);
}
//初始化列表
void test5(){
    Person2 p1(1);
    cout<<p1.age<<endl;
}

class Phone{
public:
    string name;
    Phone(){
        cout<<"phone cons"<<endl;
    }
    Phone(string name):name(name){
        cout<<"phone cons"<<endl;
    }
    ~Phone(){
        cout<<"phone des"<<endl;
    }
};

class Student{
public :
    Student(){
        cout<<"student cons"<<endl;
    }
    Student(string name,string m_name):name(name),phone(m_name){ // phone(m_name) 调用Phone的带有string 参数的构造函数
        cout<<"student cons"<<endl;
    }
    ~Student(){
        cout<<"student des"<<endl;
    }
    Phone phone;
    string name;
    void display(){
        cout<<name<<" "<<phone.name<<endl;
    }

};
// 类对象作为类成员时候，构造顺序:先将类对象构造(按照成员变量的声明顺序)，然后构造自己， 析构的顺序是相反的
void test6(){
    Student s("aaab","iphone");
    s.display();
}

class Test{
public:
    explicit Test(int a){ // explicit关键字，防止隐式类型转换
    }
};
void test7(){
//    Test t=0;
    Test t2(34);
}

//new operator
void test8(){

//    Person p1;//栈区开辟
//    cout<<new Person<<endl; // return heap address
//    Person* p2=new Person; // in heap
//    p2->age=123;
//    cout<<p2->age<<endl;
//    delete p2; // call destructor

//    Person* p3=new Person(123);
//    cout<<p3->age<<endl;
//    delete p3;

//    void* p4=new Person;
//    delete p4;//当用void*接受new出来的指针，会出现释放的问题,无法释放p

    Person* persons=new Person[10]; // call Person default constructor 10 times
    Person parr2[2]={Person(123),Person(456)};// //在栈.上开辟数组，可以指定有参构造 , 在方法调用完成后自动释放
    delete[] persons;//如果在new表达式中使用[]必须在相应的delete表达式中也使用[]
    cout<<"before end test8 call "<<endl;
}

//static
class Person3{
public :
    static int class_id;// /静态成员变量，在类内声明，类外进行初始化
    int print_private(){
        cout<<private_id<<endl;
    }
    static int static_print_private(){ // //静态成员函数 不可以访问普通成员变量
        cout<<private_id<<endl;
    }
private:
    static int private_id;

};
int Person3::class_id=0;// 类外进行初始化
int Person3::private_id=9;
void test9(){
    Person3 p;
    p.class_id=123;
    Person3::class_id=1234;
    Person3 p2;
    cout<<p2.class_id<<endl;
    p2.print_private();
    Person3::static_print_private();
}
//singleton
class Chairman{
private:
    Chairman(string name){
        this->name=name;
    }
    Chairman(const Chairman& c);//拷贝构造私有化
    static Chairman* instance;
    string name;
public :
    static Chairman* getInstance(){
        return instance;
    }
    void print_name(){
        cout<<name<<endl;
    }

};
Chairman*  Chairman::instance=new Chairman("xjp");
void test10(){
    Chairman* c=Chairman::getInstance();
    cout<<c->getInstance()<<endl;
    cout<<c->getInstance()<<endl;
    cout<<c->getInstance()<<endl;
    c->getInstance()->print_name();
//    Chairman* c2=new Chairman(*c);
//    cout<<c2<<endl;
}

//成员变量和成员属性分开存储,only 非静态成员变量属于对象 ( sizeof(Class),sizeof(object) )
// //空类的大小为1,由于没有成员变量的class也能创建对象，对于创建的每个实例对象 都需要一个独一无二的地址，因此空类内部需要一个一字节的字段来表示每个对象的地址；
#pragma pack(1) // 防止字节对齐
class Person4{
public:
    int m_age;
    double price; //m_age 不够8Byte,因此凑够8Byte后再加上 double的8Byte
    static int age2;
    void test_fun(){
        cout<<"test"<<endl;
    }
    void print_age(){
        if(this==NULL){
            return;
        }
        cout<<m_age<<endl;
    }

    Person4& addAge(int age){ //注意此时函数的返回类型为Person4类型对象的引用，如果没有&则为值拷贝（调用拷贝构造函数），会新建一个对象
        cout<<"add"<<endl;
        this->m_age+=age;
        return *this; // 通过this指针实现链式调用
    }

};
void test11(){
    cout<< sizeof(Person4)<<endl;
    Person4 p1;
    cout<< sizeof(p1)<<endl;
}
//this
void test12(){
    Person4 p1;
    p1.m_age=10;
    p1.addAge(10).addAge(20).addAge(30);
    cout<<p1.m_age<<endl;
}
//空指针访问成员函数
void test13(){
    Person4* p=NULL;
    p->test_fun(); //如果成员函数没有用到this,那么空指针可以直接访问。 NullPointerException in java
    p->print_age();//如果成员函数中用到this指针，就要注意，可以加if判断 this is NULL or not
    Person4& p2= *(p);
    p2.test_fun();
}

// 常函数 与 常对象
class Person5{
public:
    int m_a;
    mutable int m_b; //就算是常函数我还是执意要修改
    Person5(){
        this->m_a=0;
        this->m_b=0;
    }
    //this指针是指针常量，指针指向的地址不能改变，指向的地址的值可以改变
    //在常函数中,不允许修改this指针指向的地址中对象的值 : const Person5* const this_pointer;
    void showInfo() const{
//        this->m_a=123; //error
    this->m_b=123;
    }
    void show(){
        cout<<"show"<<endl;
    }

};
void test14(){
    Person5 p1;
    p1.m_a=1234;
    const Person5 p2;//常对象不允许修改属性,除了 mutable成员变量
//    p2.m_a=567;//error
//    p2.show();//常对象不可以调用普通成员函数
    p2.showInfo();//常对象可以调用常函数

}

//友元函数 (注意两个类的声明和类中方法实现的顺序 （依赖关系）)
class Building;
class GoodGay{
public :
    GoodGay(Building* building){
        this->building=building;
    }
    void visit();
    void visit2();
private:
    Building* building;
};
class Building{
    friend void GoodGay::visit2();// 成员函数做友元函数
    friend void goodGay(Building* building);// 全局函数做友元函数,使得友元函数中可以访问类中的私有成员变量和成员函数
//    friend class GoodGay; // 友元类(GoodGay中所有的方法都可以访问Building的私有成员变量和成员函数),友元类是单向，不可传递的。
public:
    string sitting_room;
    Building(){
        this->bed_room="bed";
        this->sitting_room="sitting";
    }

private:
    string bed_room;
    void print(){
        cout<<"private print"<<endl;
    }

};
void GoodGay::visit() {
    cout<<building->sitting_room<<endl;
//    cout<<building->bed_room<<endl;
//    building->print();

}
void GoodGay::visit2() {
    cout<<building->sitting_room<<endl;
    cout<<building->bed_room<<endl;
    building->print();
}
void goodGay(Building* building){
    cout<<building->sitting_room<<endl;
    // 友元函数中可以访问类中的私有成员变量和成员函数
    cout<<building->bed_room<<endl;
    building->print();

}
void test15(){
    Building* b=new Building;
//    goodGay(b);
    GoodGay* gg=new GoodGay(b);
    gg->visit();
    gg->visit2();


}



int main(){
//    test1();
    test2();
//    cout<<"end call"<<endl;
//    test3();
//    test4();
//    test5();
//    test6();
//    test7();
//    test8();
//    cout<<"end test8 "<<endl;
//    test9();
//    test10();
//    test11();
//    test12();
//    test13();
//    test14();
//    test15();



    return EXIT_SUCCESS;

}
