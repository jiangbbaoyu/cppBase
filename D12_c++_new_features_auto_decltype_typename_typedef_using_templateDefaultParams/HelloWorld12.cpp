//
// Created by aaab on 2020-11-24.
//
#include <iostream>
using namespace std;
/**
 *
 *  1. auto ： 使用了 auto 关键字以后，编译器会在编译期间自动推导出变量的类型
 *      auto的限制： 使用 auto 的时候必须对变量进行初始化；auto 不能在函数的参数中使用； auto 不能作用于类的非静态成员变量；auto 关键字不能定义数组;auto 不能作用于模板参数
 *
 *  2. decltype:从表达式的类型推断出定义的变量类型
 *      auto varname = value;
 *      decltype(exp) varname = value;
 *      decltype(exp) varname;// auto 要求变量必须初始化，而 decltype 不要求
 *      auto 根据=右边的初始值 value 推导出变量的类型，而 decltype 根据 exp 表达式推导出变量的类型，跟=右边的 value 没有关系
 *      保证 exp 的结果是有类型的，不能是 void
 *      与 auto的区别：
 *          1.auto忽略顶层const，decltype保留顶层const；
 *          2.对引用操作，auto推断出原有类型，decltype推断出引用；
 *          3.对解引用操作，auto推断出原有类型，decltype推断出引用；
 *          4.auto推断时会实际执行 = 右边的表达式，decltype不会执行类型表达式
 *
 * 3. typename: 当声明一个依赖模板参数、且带有域运算符:: 的类型的变量时（eg:  T::iterator it）需要使用typename 关键字告诉编译器T::iterator为一个类型而不是一个变量
 *
 * 4. typedef : 任何声明变量的语句前面加上typedef之后，原来是变量的都变成一种类型。不管这个声明中的标识符号出现在中间还是最后.
 *    左右法则
 *
 * 5. 返回类型后置: 将 decltype 和 auto 结合起来完成返回值类型的推导，
 *    返回值类型后置语法，是为了解决 函数返回值类型依赖于参数而导致难以确定返回值类型 的问题。有了这种语法以后，对返回值类型的推导就可以 通过参数做运算 来描述了
 *
 * 6. using
 *          1.用来重定义一个模板
 *          2.配合命名空间，对命名空间权限进行管理
 *              using namespace std;//释放整个命名空间到当前作用域
 *              using std::cout;    //释放某个变量到当前作用域
 *          3. 继承体系中，改变部分接口的继承权限
 *
 *
 *
 *
 *
 * 7. 函数模板的默认模板参数
 *
 *
 *
 *
 *
 */

//auto
void test11(){
    auto n = 10;
    auto f = 12.8;
    auto p = &n; // int*
    auto url = "http://c.biancheng.net/cplus/"; // PKC : pointer(P) const(K) char(c)  : const char *
//    cout<< typeid(url).name()<<endl;

    auto *p2=&n, num=123;   //连续定义多个变量 ,auto 代表int
//    auto *p22=&n, num2=123.3;   //连续定义多个变量时，推导的时候不能有二义性
//    auto i2; //auto 类型推导的变量必须马上初始化

}
//atuo + reference
void test12(){
    int  x = 0;
    auto *p1 = &x;   //p1 为 int *，auto 推导为 int
    auto  p2 = &x;   //p2 为 int*，auto 推导为 int*
    auto &r1  = x;   //r1 为 int&，auto 推导为 int
    auto r2 = r1;    //r2 为  int，auto 推导为 int :当=右边的表达式是一个引用类型时，auto 会把引用抛弃，直接推导出它的原始类型。

//    cout<< typeid(p1).name()<<endl;
//    cout<< typeid(p2).name()<<endl;
//    *p2=123;
//    cout<<x<<endl;//123

//    r1=1234;
//    cout<<r2<<endl;//0
//    cout<<x<<endl;//1234
}
//auto 和 const
//当类型不为引用时，auto 的推导结果将不保留表达式的 const 属性；
//当类型为`常引用`时，auto 的推导结果将保留表达式的 const 属性， 不保留&属性
void test13(){
    int  x = 0;
    const  auto n = x;  //n 为 const int ，auto 被推导为 int
    auto f = n;      //n 为 const int，auto 被推导为 int（const 属性被抛弃）f的类型为int
    const auto &r1 = x;  //r1 为 const int& 类型，auto 被推导为 int
    auto &r2 = r1;  //r1 为 const int& 类型，auto 被推导为 const int 类型
//    n=123;
    f=123;// f is not const
//    r2=1233;// r2 is const

//    int arr[3];
//    auto arr2[3]={1,2,3};
//    A<auto> C2 = C1;  //错误
}

//auto的使用场景
#include <vector>
class A{
public:
    static int get(void){
        return 100;
    }
};
class B{
public:
    static const char* get(void){
        return "http://c.biancheng.net/cplus/";
    }
};
template <typename T>
void func(void){
    auto val = T::get(); //此时get()方法返回的数据类型未定,可以使用auto来接收
    int val2 = T::get(); //如果func<B>()在后面有被调用，则val2会报错
    cout << val << endl;
}
template <typename T1, typename T2>  //不使用auto解决上面的问题：额外增加一个模板参数 T2
void func2(void){
    T2 val = T1::get();
    cout << val << endl;
}
void test14(){
//    vector< vector<int> > v;
//    auto i=v.begin();

    func<A>();
//    func<B>();

    func2<A,int>();
    func2<B,const char*>();//调用时手动给模板参数赋值
}

//decltype
//decltype 能够根据变量、字面量、带有运算符的表达式推导出变量的类型
int getSize(){
    cout<<"get size"<<endl;
}
void test21(){
    int a = 0;
    decltype(a) b = 1;  //b 被推导成了 int
    decltype(10.8) x = 5.5;  //x 被推导成了 double
    decltype(x + 100) y;  //y 被推导成了 double
//    cout<< typeid(y).name()<<endl;//
    decltype(getSize()) type; //编译器分析表达式并得到它的类型，却不实际计算表达式的值
    type =123;
//    cout<< typeid(type).name()<<endl;//

    decltype(A::get()) int3=456;

}
//decltype 与const结合
void test22(){

    double tempA = 3.0;
    const double ctempA = 5.0;
    const double ctempB = 6.0;

//    const double * cptrTempA = &ctempA;
//    *cptrTempA=123.4;// 常量指针，指针可以指向其他地址，但是指针指向地址的内容不能改变

    decltype(ctempA) dclTempA=3.3;//dclTempA推断为const double（保留顶层const，此处与auto不同)
//    dclTempA = 5;

    const double *const cptrTempC = &ctempA;//常量指针常量
    decltype(cptrTempC) declTempC=&tempA;//常量指针常量 :指针所指向的内存地址不可修改同时内存地址所对应的值也不可修改
//    declTempC=&tempA;
//    *declTempC=12.3;

}

//decltype 与引用结合
void test23(){

    // 普通引用
    int tempA = 0, &refTempA = tempA;
    decltype(refTempA) dclTempA = tempA;//dclTempA为引用，绑定到tempA
    dclTempA=123;
//    cout<<tempA<<endl;//123;
//    decltype(refTempA) dclTempB = 0;// dclTempB初始化时必须绑定到变量

    decltype((tempA)) dclTempD = tempA; // 双层括号表示引用，dclTempD为引用，绑定到tempA
    dclTempD=345;
    cout<<tempA<<endl;//345

    //常引用
    const int ctempA = 1, &crefTempA = ctempA;

    decltype(crefTempA) dclTempE = tempA; // dclTempE为常量引用，可以绑定到普通变量,常量，且必须初始化
    decltype(crefTempA) dclTempF = ctempA;

//    decltype((ctempA)) dclTempG;//双层括号表示引用,dclTemp为常量引用 必须初始化

}

//decltype 与指针
void test24(){
    int tempA = 2;
    int *ptrTempA = &tempA;
    decltype(ptrTempA) dclTempA;// int*
    decltype(*ptrTempA) dclTempB=tempA; //(*ptrTempA)为解引用操作，dclTempB为一个引用，引用必须初始化
    dclTempB=99;
    cout<<tempA<<endl;//99
}

//decltype的应用
//decltype 用于推导类的非静态成员变量的类型
template <typename T>
class Base {
public:
    void func(T& container) {
        m_it = container.begin();
    }
private:
//    typename T::iterator m_it;  //如果当传入的container为一个const容器时，此时只等得到该容器的const_iterator,会报错
    typename T::const_iterator m_it; // m_it为依赖于模板参数T的限定类型变量，因此需要使用typedef
    decltype(T().begin()) m_it2;// 先创建T类型的对象，然后根据begin()方法的返回值决定 m_it2的类型
};

void test25(){
    vector<int> v;
    Base<vector<int>> b;
    b.func(v);

    const vector<int> v2;
    Base<const vector<int>> b2;
    b2.func(v2);
}

//typename 的使用
/**
 * 1). qualified name 例如:std::cout, std::endl;这样含有作用域符号(::)的就是限定名
 * 2). dependent name :是依赖于模板参数的类型
 */

template <typename T>
class Y{
    typename T::iterator *iter;
    typedef typename T::iterator it;// 声明一个类型it ,  该类型与T中的iterator类型一致
//    T::iterator *iter; //error ,当我们使用 `qualified dependent name` 的时候，需要用typename来指出 T::iterator是一个类型，而不是一个变量；如果T::iterator为一个变量则会在编译期报错
};
class cType{
    static int iterator;//如果此时上面class Y中的T类型实例化为cType, 则 类Y中T::iterator为一个变量 ， 那么T::iterator *iter会被解释为两数相乘

};
void test31(){
//    Y<cType> y;// error ,T::iterator must be a Type
    Y<vector<int>> y2;
}

//typedef
typedef int P(); //定义 没有参数，返回值为int的函数类型
typedef int Q();
class X{
public:
    P pp; // int pp();
    static Q qq; // static intqq();
    P(ppp);// int ppp();


};
int X::pp(){
    cout<<"pp call"<<endl;
}
int X::ppp(){
    cout<<"ppp call"<<endl;
}
int X::qq(){
    cout<<"qq call"<<endl;
}

typedef struct{int a;} STRTCT;
typedef int* p;
typedef int ARR10[2]; // 定义一个名为ARR10的ints数组的类型
void test41(){
//    X x;
//    x.pp();
//    x.ppp();
//    x.qq();

//    STRTCT s;
//    s.a=123;

//    ARR10 arr={1,2};
}

int (*pArr) [10]; //定义一个指向 包含10个整型数数组 的指针 (数组指针)
int (*pfunc) (int); // 定义一个指向函数的指针，被指向的函数有一个整型参数并返回整型值
int (*arr[10]) (int);//定义一个包含10个指针的数组，其中包含的指针指向函数，这些函数有一个整型参数并返回整型值
/**
 * eg:如上例，找到变量名arr，先往右是[]运算符，说明arr是一个数组；
 * 再往左是一个*号，说明arr数组的元素是指针（注意：这里的*修饰的不是arr，而是arr[10]。原因是[]运算符的优先级比*要高，arr先与[]结合。）；
 * 跳出圆括号，先往右又遇到圆括号，说明arr数组的元素是指向函数的指针，它指向的函数有一个int类型的参数，返回值类型是int
 *
 */
void test42(){
    int (*pfunc) (int);
    int (*arr[10]) (int);
    arr[0] = pfunc;
}

/**
 * 右左法则
 *       从变量名看起，先往右，再往左，碰到圆括号就调转阅读的方向；括号内分析完就跳出括号，还是先右后左的顺序。如此循环，直到分析完整个定义
 */
//用typedef简化复杂的声明和定义
void test43(){
    //fp1是一个指向函数的指针，该函数接受一个整型参数并返回一个指向含有10个void指针数组的指针。
    void * (* (*fp1) (int)) [10];
    //fp2是一个指向函数的指针，该函数接受三个参数(int, int和float)，且返回一个指向函数的指针，该函数接受一个整型参数并返回一个float。
    float (*(*fp2)(int,int,float))(int);
    //fp3是一个指向函数的指针，该函数无参数，且返回一个含有10个指向函数指针的数组的指针，这些函数不接受参数且返回double值
    double (*(*(*fp3)())[10])();
    //fp4不是变量定义，而是一个函数声明；fp4是一个返回指针的函数，该指针指向含有10个函数指针的数组，这些函数不接受参数且返回整型值
    int (*(* fp4())[10])();

    typedef int (*(* fp5())[10])();
    fp5 f;// fp5代表上述的函数类型， f为上述类型的一个函数
}

//返回类型后置

template <typename R, typename T, typename U>
R add(T t, U u){
    return t+u;//函数返回值类型依赖于函数参数，而导致难以确定函数返回值类型
}

void test51(){
    float a=12.3;
    int b=12;
    //我们并不关心 a+b 的类型是什么，因此，只需要通过 decltype(a+b) 直接得到返回值类型即可;
    // 此时在add函数外部需要知道参数之间应该如何运算(eg: a+b)才能通过decltype指明add的返回值类型，十分不方便

    auto res=add<decltype(a+b)>(a,b);// decltype(a+b)--> R; a-->T; b-->U ,所有的模板参数都有具体的类型了
    cout<<res<<endl;
}

//返回类型后置语法
template <typename T, typename U>
auto add2(T t, U u) -> decltype(t + u){// 返回类型后置:此时可以根据函数的参数在函数定义时得出函数的返回值类型
    return t + u;
}
void test52(){
    float a=12.3;
    int b=12;
    auto res=add2(a,b);
    cout<<res<<endl;
}


//using
#include <map>
// 使用 typedef 重定义类型是很方便的，但它也有一些限制，比如，无法重定义一个模板
typedef std::map<std::string,int> map_int_t;
typedef std::map<std::string,string> map_str_t;
// 如果要固定以 std::string 为 key 的 map，它可以映射到 int 或string,或其他类型。然而这个简单的需求仅通过 typedef 却很难办到
// 可以如下实现
template <typename Val>
struct str_map{
    typedef std::map<std::string, Val> type;
};
void test61(){
    str_map<int>::type map1;
    str_map<std::vector<int>>::type map2;
}


template <typename  Val>
using str_map_t= std::map<string,Val> ;//使用using别名语法 重定义一个模板类型

template <class T>
class XX{
public:
    using func_t = void (*)(T,T);
    // C++11 的 using 写法只是 typedef 的等价物。
    // 虽然 using 重定义的 func_t 是一个模板，但 func_t<int> 定义的 func 并不是一个由类模板实例化后的类，而是 void(*)(int, int) 的别名
//    void foo(func_t<float> func);
    void foo(void(*func)(float,float)); // 两个foo函数无法实现重载，

};

void test62(){
    str_map_t<int> map1;
    str_map_t<std::vector<int>> map2;


}
//using 别名语法与typedef的对比
void test63(){
    typedef unsigned int uint_t;
    using uint_t = unsigned int;

    typedef void (*func_t)(int, int);
    using func_t=void (*)(int,int);

    typedef int (*(* fp5())[10])();
    using fp5 =int (*(*())[10])();// 相比于typedef,把变量名提前了
}

//using : 改变部分接口的 '继承权限'
//eg: 私有继承一个基类，然后又想将基类中的某些public接口在子类对象实例化后对外开放直接使用
class Base2{
public:
    void dis1(){
        cout<<"dis1"<<endl;
    }
    void dis2(){
        cout<<"dis2"<<endl;
    }
private:
    void dis3(){
        cout<<"dis3"<<endl;
    }
};
class Sub2:private Base2{// 私有继承
public:
    using Base2::dis1;//需要在Sub2的public下释放才能对外使用，此时Sub2的对象可以直接使用dis1方法
//    using Base2::dis3; // 不能使用基类的private 函数， 基类中的private成员无论如何都不能在子类中使用
    void dis2show(){
        this->dis2();
//        this->dis3();
    }

};
void test64(){
    Sub2 s;
    s.dis1();
    s.dis2show();
}




//类模板可以有默认的模板参数
template <typename T, typename U = int, U N = 0>
struct Foo{

};

//函数模板的默认模板参数
void test71(){



}




int main(){
//    test11();
//    test12();
//    test13();
//    test14();
//    test21();
//    test22();
//    test23();
//    test24();
//    test25();
//    test41();
//    test42();
//    test51();
//    test52();
//    test61();
//    test62();
//    test63();
    test64();

//    cout << __cplusplus << endl;
    return EXIT_SUCCESS;
}

