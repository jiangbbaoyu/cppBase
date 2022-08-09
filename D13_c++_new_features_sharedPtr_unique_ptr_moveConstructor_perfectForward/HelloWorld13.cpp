//
// Created by aaab on 2020-11-26.
//
#include <iostream>
using namespace std;

/**
 * 1. nullptr
 *    nullptr 可以被隐式转换成任意的指针类型 ,nullptr是c++关键字，不是一个宏定义 （#define NULL 0）
 *
 * 2. 智能指针： 使用智能指针可以很好地避免“忘记释放内存而导致内存泄漏”问题出现；C++ 智能指针底层是采用引用计数的方式实现的。简单的理解，智能指针在申请堆内存空间的同时，会为其配备一个整形值
 *    shared_ptr :shared 智能指针是以模板类的形式提供的，shared_ptr<T>（T 为指针所指数据的类型）
 *    unique_ptr: unique_ptr 智能指针是以模板类的形式提供的，unique_ptr<T>（T 为指针所指数据的类型）
 *    智能指针对象做类成员变量
 *
 * 3. rvalue, lvalue, 右值引用,移动构造函数 ,std::move(), 完美转发
 *      lvalue 是“loactor value”的缩写，可意为存储在内存中、有明确存储地址（可寻址）的数据，
 *      而 rvalue 译为 "read value"，指的是那些可以提供数据值的数据（不一定可以寻址，例如存储于寄存器中的数据）
 *      右值引用
 *      移动语义，指的就是以移动而`非深拷贝`的方式初始化含有指针成员的类对象， 就是将其他对象（通常是临时对象）拥有的内存资源“移为已用”
 *      std::move()  : 将左值强制转换为右值
 *      完美转发: 函数模板可以将自己的参数“完美”地转发给内部调用的其它函数。不仅能准确地转发参数的值，还能保证被转发参数的左、右值属性不变
 *
 */
void test11(){
    char* p=nullptr;
    double * a3 = nullptr;
}

// shared_ptr
// 多个 shared_ptr 智能指针可以共同使用同一块堆内存
void test21(){

    std::shared_ptr<int> sp1;// 空智能指针 ,其初始引用计数为 0 ；
    std::shared_ptr<int> sp2(nullptr);//空智能指针, 其初始引用计数为 0

    std::shared_ptr<int> sp3(new int(10));//指向一块存有 10 这个 int 类型数据的堆内存空间 ,
    std::shared_ptr<int> sp4=std::make_shared<int>(12);  // new int(12)

    std::shared_ptr<int> sp5(sp3);// 拷贝构造,如果 sp3 为空智能指针，则 sp5 也为空智能指针，其引用计数初始值为 0；反之，则表明 sp5 和 sp3 指向同一块堆内存，同时该堆空间的引用计数会加 1。
    std::shared_ptr<int> sp6(std::move(sp3)); // 移动构造,  sp6 拥有了 sp3的堆内存，而 sp3 则变成了空智能指针
    std::shared_ptr<int> sp7 = std::move(sp3);

}
//同一个普通指针不能同时为多个 shared_ptr 对象赋值
void test22(){
    int* ptr = new int;
    std::shared_ptr<int> p1(ptr);
//    std::shared_ptr<int> p2(ptr);//错误
}

//在初始化 shared_ptr 智能指针时，还可以自定义所指堆内存的释放规则，
// 这样当堆内存的引用计数为 0 时，会优先调用我们自定义的释放规则
void deleteInt(int*p) {
    delete []p;
}
void test23(){
    //p7内部维护一个int*指针， 指针指向的具体类型为int  ; (new int[10]的返回值类型为int* )
    std::shared_ptr<int> p7(new int[10], deleteInt);//初始化智能指针，并自定义释放规则
    //    std::shared_ptr<int> sp1(new int[10],[](int* p){delete[] p;});
}
/**
 * shared_ptr<T>模板类提供的成员方法
 *  operator=()	重载赋值号，使得同一类型的 shared_ptr 智能指针可以相互赋值。
    operator*()	重载 * 号，获取当前 shared_ptr 智能指针对象指向的数据。
    operator->()	重载 -> 号，当智能指针指向的数据类型为自定义的结构体时，通过 -> 运算符可以获取其内部的指定成员。
    swap()	交换 2 个相同类型 shared_ptr 智能指针的内容。
    reset()	当函数没有实参时，该函数会使当前 shared_ptr 所指堆内存的引用计数减 1，同时将当前对象重置为一个空指针；当为函数传递一个新申请的堆内存时，则调用该函数的 shared_ptr 对象会获得该存储空间的所有权，并且引用计数的初始值为 1。
    get()	获得 shared_ptr 对象内部包含的普通指针。
    use_count()	返回同当前 shared_ptr 对象（包括它）指向相同的所有 shared_ptr 对象的数量。
    unique()	判断当前 shared_ptr 对象指向的堆内存，是否不再有其它 shared_ptr 对象再指向它。
    operator bool()	unique_ptr 指针可直接作为 if 语句的判断条件，以判断该指针是否为空，如果为空，则为 false；反之为 true
 */
void  test24(){
    std::shared_ptr<int> p1(new int(10));
    std::shared_ptr<int> p2(p1);
//    cout<<p2<<endl;
//    cout<<*p2<<endl;
//    cout<<p2.use_count()<<endl;//2
     cout<<p2.unique()<<endl; //0

    p1.reset();//引用计数减 1,p1为空指针
    if(p1){//false
        cout<<p1<<endl;
    }
//    cout<<p2.use_count()<<endl;//1


//    int* pp=p2.get();
//    cout<<*pp<<endl;

    cout<<p2.unique()<<endl;//1

}

//unique_ptr 指针指向的堆内存无法同其它 unique_ptr 共享
struct myDel{
    void operator()(int *p) {
        delete p;
    }
};
void test31(){
    std::unique_ptr<int> p1;
//    std::unique_ptr<int> p2(nullptr);
    std::unique_ptr<int> p2=nullptr;
    std::unique_ptr<int> p3(new int);
    std::unique_ptr<int> p4=std::make_unique<int>(); //0
    std::unique_ptr<int> p41=std::make_unique<int>(123); //0  new int(123)
//    cout<<p41<<endl;
//    cout<<*p41<<endl;

    //基于 unique_ptr 类型指针不共享各自拥有的堆内存，因此 C++11 标准中的 unique_ptr 模板类没有提供拷贝构造函数，只提供了移动构造函数
//    std::unique_ptr<int> p5(p4);
    std::unique_ptr<int> p5(std::move(p4));


    // 为 unique_ptr 自定义释放规则，只能采用函数对象的方式
//    std::unique_ptr<int> p6(1234,[](int* p){delete p;}); //error
    std::unique_ptr<int,myDel> p6(new int(123),myDel());
}

/**
 * unique_ptr<T>模板类提供的成员方法
 *      operator*()	获取当前 unique_ptr 指针指向的数据
 *      operator->()	重载 -> 号，当智能指针指向的数据类型为自定义的结构体时，通过 -> 运算符可以获取其内部的指定成员
 *      operator =()	重载了 = 赋值号，从而可以将 nullptr 或者一个右值 unique_ptr 指针直接赋值给当前同类型的 unique_ptr 指针
 *      operator []()	重载了 [] 运算符，当 unique_ptr 指针指向一个数组时，可以直接通过 [] 获取指定下标位置处的数据。
 *      operator []()	重载了 [] 运算符，当 unique_ptr 指针指向一个数组时，可以直接通过 [] 获取指定下标位置处的数据。
 *      get_deleter()	获取当前 unique_ptr 指针释放堆内存空间所用的规则
 *      operator bool()	unique_ptr 指针可直接作为 if 语句的判断条件，以判断该指针是否为空，如果为空，则为 false；反之为 true
 *      release()	释放当前 unique_ptr 指针对所指堆内存的所有权，但该存储空间并不会被销毁
 *      reset(p)	其中 p 表示一个普通指针，如果 p 为 nullptr，则当前 unique_ptr 也变成空指针；反之，则该函数会释放当前 unique_ptr 指针指向的堆内存（如果有），然后获取 p 所指堆内存的所有权
 *      swap(x)	交换当前 unique_ptr 指针和同类型的 x 指针。
 */
void test32(){
    std::unique_ptr<int> p5(new int(1));
//    cout<<*p5<<endl;
    *p5 = 10;
//    cout<<*p5<<endl;

// p 接收 p5 释放的堆内存
    int * p = p5.release();
//    cout << *p << endl;

//判断 p5 是否为空指针
    if (p5) {
        cout << "p5 is not nullptr" << endl;
    }
    std::unique_ptr<int> p6;
    //p6 获取 p 的所有权
    p6.reset(p);
    cout << *p6 << endl;
}


//智能指针对象做成员变量
class Device {
public:
    Device(){
        cout<<"device cons"<<endl;
    }
    ~Device(){
        cout<<"device des"<<endl;
    }
    void test(){}
};

class Settings {
    std::unique_ptr<Device> device; // 系统会自动释放智能指针类型和string类型的成员变量的内存空间
public:
    Settings(std::unique_ptr<Device> d) {
//        device=d; // unique_ptr do not have copy constructor
        device = std::move(d);
    }
//    Settings():device(){ // 此时device仍为空
    Settings():device(std::make_unique<Device>()){ // 初始化列表初始中： 创建Device对象，并给device智能指针赋值
//        cout<<device.get()<<endl;
        cout<<"setting cons"<<endl;
    }
    Device& getDevice() {
//        cout<<typeid(device.get()).name()<<endl; // Pointer of Device
//        cout<<typeid(*device).name()<<endl;   // Device
        return *device;
    }
    ~Settings(){
        cout<<"setting des"<<endl;
    }
};

void test33(){
    std::unique_ptr<Device> dp;//dp is NULL
    std::unique_ptr<Device> dp2=std::make_unique<Device>(); // 会调用Device的默认构造函数 ,make_unique的函数参数会作为构造函数的参数
}
void test34() {
    std::unique_ptr<Settings> sp=std::make_unique<Settings>();
//    std::unique_ptr<Settings> sp;
}
void test35() {
    std::unique_ptr<Device> device(new Device());
    Settings settings(std::move(device));
//    Settings settings(device); // std::unique_ptr do not have copy constructor
    Device& myDevice = settings.getDevice();
    myDevice.test();
}


//read value, locator value ,右值引用
void test41(){
//    int b = 10; // b 是一个左值
//    a = b; // a、b 都是左值，只不过将 b 可以当做右值使用

//    const int num = 10;
    int num = 10;
    int &b = num; //正确
//    int &c = 10; //错误
    const int &c = 10; //常量左值引用既可以操作左值，也可以操作右值;  如果需要对右值进行修改，显然常量左值引用的方式是行不通的
}
//和声明左值引用一样，右值引用也必须立即进行初始化操作，且只能使用右值进行初始化
void test42(){

    int num = 10;
//    int && a = num;  //右值引用不能初始化为左值
    int && a = 10;
    a=123; // 和常量左值引用不同的是，右值引用还可以对右值进行修改

    const int&& a2 = 10; // a2 为常量右值引用 ，并无实际用处
//    a2=123; // 不能修改
}


//拷贝构造函数的问题及解决方案--移动构造函数
class demo{
public:
    demo():num(new int(0)){
        cout<<"construct!"<<endl;
    }
    demo(const demo &d):num(new int(*d.num)){//拷贝构造函数
        cout<<"copy construct!"<<endl;
    }
    /**
     * 对于程序执行过程中产生的临时对象(通常是右值)，往往只用于传递数据，并且会很快会被销毁
     * 在使用临时对象初始化新对象时，我们可以将其包含的`指针成员`指向的内存资源直接移给新对象，无需再新拷贝一份，这大大提高了初始化的执行效率
     *     以前面程序中的 demo 类为例，该类的成员都包含一个整形的指针成员，其默认指向的是容纳一个整形变量的堆空间
     *     当使用 get_demo() 函数返回的临时对象初始化 a 时，我们只需要将临时对象的 num 指针直接`浅拷贝`给 a.num，
     *     然后修改该临时对象中 num 指针的指向（通常另其指向 NULL，避免堆内存空间的二次释放），这样就完成了 a.num 的初始化
     *
     * 当类中同时包含拷贝构造函数和移动构造函数时，如果使用临时对象（右值）初始化当前类的对象，编译器会优先调用移动构造函数来完成此操作。
     * 只有当类中没有合适的移动构造函数时，编译器才会退而求其次，调用拷贝构造函数
     *
     * 左值初始化同类对象只能通过拷贝构造函数完成，如果想调用移动构造函数，则必须使用右值进行初始化。C++11使用std::move()将左值强制转换成对应的右值，由此便可以使用移动构造函数
     */
     demo(demo&& d):num(d.num){// 移动构造函数,num 指针变量采用的是浅拷贝的方式来初始化，注意参数为 `非const右值引用`
         d.num= nullptr; // 避免堆内存空间的二次释放
        cout<<"move construct!"<<endl;
     }

    ~demo(){
        cout<<"class destruct!"<<endl;
    }
public:
    int *num;
};
demo get_demo(){
    return demo();
}
void test51(){
    /**
     * 如果编译器没有优化：其整个初始化的流程包含以下几个阶段 （有两次拷贝构造函数的调用）
     *    1. 执行 get_demo() 函数内部的 demo() 语句，即调用 demo 类的默认构造函数生成一个匿名对象；
     *    2. 执行 return demo() 语句，会 '调用拷贝构造函数' 复制一份之前生成的匿名对象，并将其作为 get_demo() 函数的返回值（函数体执行完毕之前，匿名对象会被析构销毁）；
     *    3. 执行 a = get_demo() 语句，`再调用一次拷贝构造函数`，将之前拷贝得到的临时对象复制给 a（此行代码执行完毕，get_demo() 函数返回的对象会被析构）
     *    4. 程序执行结束前，会自行调用 demo 类的析构函数销毁 a
     * 问题：临时对象中的指针成员申请了大量的堆空间，那么 2 次深拷贝操作势必会影响a对象初始化的执行效率
     *
     */
    demo a = get_demo();
    cout<<a.num<<endl;
    demo a2=std::move(a); // 得到demo对象的右值形式，然后调用移动构造函数
    cout<<a.num<<endl;//此时 a.num为 nullptr （在移动构造函数中对其进行的修改）

    demo&& a3=std::move(a2);//a3为对象a2的右值引用
    a3.num=new int(123);
    cout<<*a2.num<<endl; //123
}

// example  std::move()  : 将左值强制转换为右值
class first {
public:
    first() :num(new int(0)) {
        cout << "construct!" << endl;
    }
    //移动构造函数
    first(first &&d) :num(d.num) {
        d.num = NULL;
        cout << "first move construct!" << endl;
    }
public:
    int *num;
};
class second {
public:
    second() :fir() {}
    second(second && sec) :fir(move(sec.fir)) { //用 first 类的移动构造函数初始化 fir
        cout << "second move construct" << endl;
    }

public:    //这里也应该是 private，使用 public 是为了更方便说明问题
    first fir;
};
void test52(){
    second s1;
    second s2=std::move(s1);
}


//完美转发 ：函数模板可以将自己的参数“完美”地转发给内部调用的其它函数。不仅能准确地转发参数的值，还能保证被转发参数的左、右值属性不变
void inner_func(int& t){
    cout<<"lvalue call"<<endl;
}
void inner_func(int&& t){
    cout<<"rvalue call"<<endl;
}
template <typename T>
void func(T&& t){//通常情况下右值引用形式的参数只能接收右值，不能接收左值;但对于函数模板中使用右值引用语法定义的参数来说，既可以接收右值，也可以接收左值 ; 此时的右值引用又被称为“万能引用”
    inner_func(std::forward<T>(t)); //std:forward<T>()：  将函数func内部的变量t的值和其类型（左右值信息）传递给inner_func函数
}

void test61(){
    int x=456;
    func(x);// lvalue call , 此时func中T被实例化为int
    int& l=x;
    func(l);// lvalue call, 此时func中T被实例化为int& , 则T&& 为int& &&, 折叠为int&

    func(123);// rvalue call
    func(std::move(x));// rvalue call ,此时func中T被实例化为int&& , 则T&& 为int&& &&, 折叠为int&&
    func(std::move(l));// rvalue call
}

int main(){
//    test21();
//    test22();
//    test23();
//    test24();
//    test31();
//    test32();
//    test33();
//    test34();
//    test35();
//    test41();
//    test42();
//    test51();
//    test52();
    test61();

    return EXIT_SUCCESS;
}

