//
// Created by aaab on 11/11/20.
//

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
/**
 *  STL(StanBard Template Library;标准模板库)
 *  STL从广义上分为:容器(container) 算法(algorithm) 迭代器(iterator ,可以看做指针)
 *      当我们给容器中插入元素的时候，容器内部实施了拷贝动作，将我们要插入的元素再另行拷贝一份放入到容器中，而不是将原数据元素直接放进容器中。
 *      也就是说我们提供的元素必须能够被拷贝。
 *
 *      vector:单端数组，动态扩容,头插效率极差 (vector扩容时，也会调用元素的拷贝构造函数)
 *      string: 管理char*所分配的内存.每一次 string的复制,取值都由string类负责维护不用担心复制越界和取值越界等
 *      deque:双向循环链表
 *      sort:
 *      stack:
 *      queue
 *      list:双向链表: 插入操作和删除操作都不会造成原有list迭代器的失效。这在vector是不成立的
 *      set: 关联式的容器(key ==value ),元素根据键值排序，且不允许有重复的key , only const_iterator,
 *      multiset:关联式的容器,允许有重复的key
 *      map: key is unique and sorted ,
 *
 *      foreach ,transform,
 *      find ,find_if
 *      sort , random_shuffle, merge ,
 *      copy ,replace,replace_if,swap,
 *      accumulate ,fill
 *
 *      set_intersection,set_union, set_difference;
 *
 * example : speech contest
 *
 */

// 使用指针对数据进行遍历
void test1(){
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

#include <vector>
#include <algorithm>

void print(int v){
    cout<<v<<endl;
}
class Person{
public:
    string name;
    int age;
    Person(string name,int age):name(name),age(age){
        cout<<"person cons with ages"<<endl;
    }
    Person(){
        cout<<"person cons"<<endl;
    }
    Person(const Person& p){
        cout<<"person copy cons"<<endl;
        this->age=p.age;
        this->name=p.name;

    }
    bool operator<(const Person& p) const{ // 自定义了 operator< 常函数后，将Person类放到set中时可以不用指定仿函数了
        if(this->name==p.name&&this->age==p.age){
            return false;
        }else{
            if(this->age>=p.age){
                return false;
            }
            return true;
        }
    }
    bool operator==(const Person& p){
        if(this->name==p.name&&this->age==p.age){
            return true;
        }
        return false;
    }
    ~Person(){
        cout<<"person destructor"<<endl;
    }
};
void test2(){
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(11);
    v1.push_back(12);
    v1.push_back(13);

//    vector<int>::const_iterator it2=v1.begin();//read-only
//    vector<int>::iterator itBegin=v1.begin();// point to the first ele
//    vector<int>::iterator itEnd=v1.end();// point to the next position of last ele
//    while (itBegin!=itEnd){
//        cout<<*itBegin<<endl;
//        itBegin++;
//    }

//    for(vector<int>::iterator it=v1.begin();it!=v1.end();it++){
//        cout<<*it<<endl;
//    }

//    for_each(v1.begin(),v1.end(),print);
    // lambda
//    for_each(v1.begin(),v1.end(),[](int v){cout<<v<<endl;});


    Person p1("aab1",2);
    Person p2("aab2",122);
    Person p3("aab3",2);
    Person p4("aab4",1);
    vector<Person> v2;
    v2.reserve(5);//push_back前四个元素时，防止vector扩容, vector扩容时，也会调用元素的拷贝构造函数
    v2.push_back(p1);
    v2.push_back(p2);
    v2.push_back(p3);
    v2.push_back(p4);

    vector<Person>::iterator it=find(v2.begin(),v2.end(),p2); // Person override operator==
    cout<<it->name<<"  "<<it->age<<endl;

//    for(vector<Person>::iterator it=v2.begin();it!=v2.end();it++){
//        cout<<it->name<<" , "<<it->age<<endl;
//    }




}

//string
void test3(){
//    string str();
//    string str1("123abv");
//    string str2=str1;
//    string str3(str2);
//    string str4(10,'b');
////    cout<<str4<<endl;
//    str4.assign("abcc");
//    str4.assign("abcdefg",1,3);// //将s从star t开始n个字符赋值给字符串
////    cout<<str4<<endl;


    // api
//    string str5("abc");
//    for(string::iterator it=str5.begin();it!=str5.end();it++){
//        cout<<*it<<endl;
//    }

//    cout<<str5[90]<<endl;
//    try{
//        cout<<str5.at(9)<<endl; //throw exception
//    }catch (std::out_of_range& e){
//        cout<<"error:"<<e.what()<<endl;
//    }

//    str5+="def";
////    cout<<str5<<endl;
//    str5.append("ghi");
//    int pos=str5.find("bf",0);
////    cout<<pos<<endl;
//
//    str5.rfind("fg");// right ->left
//    str5.replace(0,2,"AB");
//    cout<<str5<<endl;

//    string str6("abc");
//    string str7("abz");
//    cout<<str6.compare(str7)<<endl;

//    string str8("abcdd");
//    string str9=str8.substr(3,1);
//    cout<<str9<<endl;

//    string str10("abcdef");
//    str10.insert(0,"Aaaa");
//    cout<<str10<<endl;
//    str10.erase(0,4);
//    cout<<str10<<endl;

//    string str11("abcdef");
//    const char* p=str11.c_str();
//    cout<<p<<endl;

//    string str12("aABERsdfSDcde345");
//    string::iterator it=str12.begin();
//    cout<<it[3]<<endl;


//    for(string::iterator it=str12.begin();it!=str12.end();it++){
//        *it=toupper(*it);
////        *it=tolower(*it);
//    }
//    cout<<str12<<endl;


}
void printvector(vector<int>& v){
    for(vector<int>::const_iterator it=v.begin();v.end()!=it;it++){
        cout<<*it<<" ";
    }
    cout<<endl;
    cout<<v.capacity()<<endl;
    cout<<v.size()<<endl;
}
void reverseprint(vector<int>& v){
    for(vector<int>::const_reverse_iterator it=v.rbegin();v.rend()!=it;it++){
        cout<<*it<<" ";
    }
    cout<<endl;
}
class firstEqual{
public:
    int target;
    firstEqual(int target):target(target){}
    bool operator()(int& val){  // 一元谓词
        cout<<"predicate call"<<endl;
        if(val==target){
            return true;
        }
        return false;
    }



};
void test4(){

    int arr[]={1,2,3,4,5};
//    cout<<(arr+4)[0]<<endl;
    vector<int > v(arr,arr+ sizeof(arr)/ sizeof(int)); //使用数组的起止地址来初始化vector
    vector<int> v2(v.begin(),v.end());

//    for(vector<int>::iterator it=v.begin();v.end()!=it;it++){
//        cout<<*it<<endl;
//    }
    vector<int> v3(v2);

    vector<int> v4;
    v4.assign(v3.begin(),v3.end());
    vector<int> v5(10,100);
//    printvector(v5);
    v5.swap(v3); // 交换两个容器中的元素
//    printvector(v5);
//    printvector(v3);
//    cout<<v3.size()<<endl;

    v5.resize(100,-9);

//    cout<<v5.capacity()<<endl;
//    cout<<v5.size()<<endl;
    v5.resize(10);
//    cout<<v5.capacity()<<endl;
//    cout<<v5.size()<<endl; // 此时v5的capacity大小仍未100,空间并没有真正释放掉

//    vector<int> v6(v5);
//    cout<<v6.capacity()<<endl;// 10 v6的capacity是按照v5的size来开辟内存空间的
//    cout<<v6.size()<<endl;// 10
//    v6.swap(v5);

    //resize后， 利用swap和匿名对象来回收vector内存空间
    vector<int>(v5).swap(v5);


//    printvector(v5);
//    cout<<v5.capacity()<<endl;
//    cout<<v5.size()<<endl;

//    cout<<v5.front()<<endl;//do not remove
//    cout<<v5.back()<<endl;// do not remove


//    v5.insert(v5.begin(),10,3);
//    cout<<v5.capacity()<<endl;
//    cout<<v5.size()<<endl;
//    printvector(v5);

//    v5.pop_back();
//    printvector(v5);

//    v5.erase(v5.begin());
//    printvector(v5);

    vector<int>::iterator it=find_if(v5.begin(),v5.end(),firstEqual(5));
    if(it!=v5.end()){
        cout<<"find equal "<<*it<<endl;
    }

    reverseprint(v5);


}
// vector ,reserve() ,  如果知道了大致的数据量，可以使用reserve预留出空间,避免vector内部多次进行扩容
void test5(){

    vector<Person> v;
    Person *p=NULL;
    int num=0;
    v.reserve(5);// 如果知道了大致的数据量，可以使用reserve预留出空间,避免vector内部多次进行扩容
    for (int i = 0; i <4 ; ++i) {

        if(p!=&v[0]){
            p=&v[0];
            num++;  // 统计vector内部扩容的次数
        }
        v.push_back(Person("a",1));
    }
    cout<<num<<endl;
}

// deque
#include <deque>
void test6(){
    deque<int >d;
    d.push_back(1);
    d.push_front(2);

    deque<int> d2;
    d2.swap(d);

    d2.pop_back();
    d2.pop_front();
    d2.insert(d2.begin(),d.begin(),d.end());

}

bool _comp(int a,int b){
    return a>b;
}
//sort
void test7(){
    deque<int> d;
    d.push_front(23);
    d.push_front(2343);
    d.push_front(3);
    d.push_front(-23);
//    sort(d.begin(),d.end());
    sort(d.begin(),d.end(),_comp); // bigger->smaller
    sort(d.begin(),d.end(),greater<int>()); // use functional object system provided
    for(deque<int>::const_iterator it=d.begin();it!=d.end();it++) {
        cout << *it << endl;
    }
}
//stack
#include <stack>
void test8(){
    stack<int > s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    while (s.size()!=0){
        cout<<s.top()<<endl;
        s.pop();
    }
}

#include <queue>
void test9(){

    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    while(!q.empty()){
        cout<<q.front()<<endl;
        q.pop();
    }
}
//list
#include <list>
void printlist(list<int>& l){
    for(list<int>::const_iterator it=l.begin();it!=l.end();it++){
        cout<<*it<<endl;
    }
}

bool _cmp_person(Person& p1,Person& p2){
    if(p1.age>p2.age){
        return true;
    }
    return false;
}
void test10(){

    list<int> l(10,10);
    list<int>* l2=new list<int>(l.begin(),l.end());
//    printlist(*l2);
//    delete l2;

//    l2->push_back(12);
//    l2->push_front(9);
//    printlist(*l2);
//    l2->pop_front();
//    l2->pop_back();

//    l2->insert(l2->begin(),10,1);
//    printlist(*l2);

//    l2->remove(10);
//    cout<<l2->size()<<endl;

    l2->push_back(99);
    l2->push_back(9);
//    l2->reverse();
//    printlist(*l2);

//    sort(l.begin(),l.end());////所有不支持随机访问的迭代器不可以角系统提供的算法,如果不支持用系统提供算法，那么这个类内部会提供
//    l2->sort(_comp);
//    printlist(*l2);


    list<Person> persons; //  Managing the pointer isthe user's responsibility.如果list中存放的指针，list不负责指针对应的内存空间的释放
    Person p1("a",2);
    Person p2("a",1);
    Person p3("a",5);
    Person p4("a",9);
    persons.push_back(p1);
    persons.push_back(p2);
    persons.push_back(p3);
    persons.push_back(p4);
    persons.sort(_cmp_person);

    persons.remove((p2)); // need override operator==

    for(list<Person>::const_iterator it=persons.begin();it!=persons.end();it++){
        cout<<"age:"<<(*it).age<<"  name:"<<(*it).name<<endl;
    }
}

//set multiset
#include <set>

class _cmp{
public:
    bool operator()(int v1,int v2){
        return v1>v2;
    }
};
/**
 * set容器在判定已有元素a和新插入元素b是否相等时，是这么做的：
 *    1）将a作为左操作数，b作为右操作数，调用比较函数，并返回比较值
 *    2）将b作为左操作数，a作为右操作数，再调用一次比较函数，并返回比较值
 *    如果1,2两步的返回值都是false，则认为a、b是相等的，则b不会被插入set容器中;否则根据a,b的大小关系继续寻找新插入元素b的插入位置
 *
 */
class cmp_person{
public:
    bool operator()(const Person& p1,const Person& p2){

        if(p1.name==p2.name&&p1.age==p2.age){//
            return false;
        }else{
            if(p1.age>=p2.age){
                return true;
            }
            return false;
        }
    }
};
void test11(){

//    set<int> s1; // elements is distinct and sorted

//    set<int,_cmp> s1;// 通过仿函数指定排序规则
//
//    s1.insert(1);
//    s1.insert(1);
//    s1.insert(4);
//    s1.insert(5);
//    s1.insert(5);
//    s1.insert(10);
//    s1.insert(3);
//    s1.insert(3);

//    s1.erase(s1.begin());
//    s1.erase(10);
//    set<int>::const_iterator it=s1.find(11);
//    if(it==s1.end()){
//        cout<<"not found"<<endl;
//    }
//    cout<<s1.count(3)<<endl;  // 0 or 1

//    set<int>::const_iterator it=s1.lower_bound(2);//lower_ bound(keyElem) ;//返回第一个key>=keyElem元素的迭代器。
//    if(it!=s1.end()){
//        cout<<"first ele >= 2 "<<(*it)<<endl;
//    }else{
//        cout<<"not found"<<endl;
//    }

//    set<int>::const_iterator it2=s1.upper_bound(4);//返回第一个key>keyElem元素的迭代器。
//    if(it2!=s1.end()){
//        cout<<"first ele >= 4 "<<(*it2)<<endl;
//    }else{
//        cout<<"not found"<<endl;
//    }
//    pair<set<int>::const_iterator,set<int>::const_iterator> res= s1.equal_range(2);
//    if(res.first!=s1.end()){
//        cout<<*res.first<<endl;
//    }
//    if(res.second!=s1.end()){
//        cout<<*res.second<<endl;
//    }

//    for(set<int>::const_iterator it=s1.begin();it!=s1.end();it++){
//        cout<<*it<<" ";
//    }
//    cout<<endl;

//    set<Person,cmp_person> s2; // 必须指定排序规则 ,传入仿函数，或重写 operator< 常函数
//    set<Person> s2; // 必须指定排序规则,传入仿函数，或重写 operator< 常函数
//    Person p1("a1",12);
//    Person p2("a2",145);
//    Person p3("a3",4);
//    Person p4("a3",1);
//    Person p5("a3",1);
//    s2.insert(p1);
//    s2.insert(p2);
//    s2.insert(p3);
//    s2.insert(p4);
//    s2.insert(p5);
//    for(set<Person>::const_iterator it=s2.begin();it!=s2.end();it++){
//        cout<<(*it).name<<", "<<(*it).age<<endl;
//    }

    multiset<Person> s2; //
    Person p1("a1",12);
    Person p2("a2",145);
    Person p3("a3",4);
    Person p4("a3",1);
    Person p5("a3",1);
    s2.insert(p3);
    s2.insert(p4);
    s2.insert(p1);
    s2.insert(p2);
    s2.insert(p5);
    for(set<Person>::const_iterator it=s2.begin();it!=s2.end();it++){
        cout<<(*it).name<<", "<<(*it).age<<endl;
    }
}
//map
#import <map>
void test12(){

//    map<int ,int> m;
////    map<int ,int,_cmp> m; // 自定义排序规则
//    m.insert(pair<int,int>(1,10));
//    m.insert(make_pair(2,20));
//    m.insert(map<int,int>::value_type(9,30));
//    m[4]=40;
//    cout<<m[1]<<endl;
//    cout<<m[6]<<endl;// 如果使用[]方式访问数据，要确定key是否存在，否则会向map中放入pair(key，0)的数据

//    m.erase(2);
//    cout<<m.size()<<endl;


//    map<int,int>::const_iterator it= m.find(9);
//    if(it==m.end()){
//        cout<<"can not found"<<endl;
//    }else{
//        cout<<"value is "<<it->second<<endl;
//    }

//    cout<<m.count(9)<<endl;


//    for(map<int,int>::iterator it=m.begin();it!=m.end();it++){
//        cout<<it->first<<"   "<<it->second<<endl;
//    }

    map<Person, Person> persons;//由于 Person重写了 operator< const 方法，因此，map中的元素也是按key排好序的
    Person p1("a1",12);
    Person p2("a2",145);
    Person p3("a3",4);
    Person p4("a3",1);
    Person p5("a3",1);
    persons.insert(make_pair(p1,p1));
    persons.insert(make_pair(p2,p2));
    persons.insert(make_pair(p3,p3));
    persons.insert(make_pair(p4,p4));
    persons.insert(make_pair(p5,p5));
    int count=0;
//    for(map<Person,Person>::const_iterator it=persons.begin();it!=persons.end(),count<2;it++){
    for(map<Person,Person>::const_iterator it=persons.begin();it!=persons.end();it++){
        cout<<it->first.name <<",, "<<it->first.age<<endl;
        count++;
    }

}
//内建函数对象使用
#include <functional>
void test13(){


//    negate<int> n;
//    cout<<n(12)<<endl;

    plus<int> p;
    cout<<p(1,2)<<endl;  //需要重载 operator+ ，对于自定义函数
}

// traverse algorithm
struct addTen{
    int count=0;
    void operator()(int& v){
        v=v+10;
        count++;
    }
};
struct MyPrint{
    void operator()(int& v){  // default is public
       cout<<v<<endl;
    }
};
class TransForm_op{
public:
    int operator()(const int& v){
        return v+100;
    }
};
class TransForm_op2{
public:
    int operator()(int v,int v2){
        return v+v2;
    }
};
//foreach ,transform
void test14(){
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(11);
    v1.push_back(12);
    v1.push_back(13);
//    addTen res=for_each(v1.begin(),v1.end(),addTen()); // foreach has a return value
//    cout<<res.count<<endl;
//    for_each(v1.begin(),v1.end(),MyPrint());

    vector<int> v2;
    v2.push_back(10);
    v2.push_back(11);
    v2.push_back(12);
    v2.push_back(13);
//    v2.resize(v1.size());  //size=4; capacity=4
////    v2.reserve(v1.size()); //size=0; capacity=4
////    cout<<v2.size()<<endl;
////    cout<<v2.capacity()<<endl;
    transform(v1.begin(),v1.end(),v2.begin(),TransForm_op()); // 必须事先使用resize将target容器分配好资源
    for_each(v2.begin(),v2.end(),[](int v){cout<<v<<endl;});

    vector<int> v3;
    v3.resize(v1.size());
    transform(v1.begin(),v1.end(),v2.begin(),v3.begin(),TransForm_op2());
    for_each(v3.begin(),v3.end(),[](int v){cout<<v<<endl;});

}
//find ,find_if
void  test15(){

    Person p1("aab1",2);
    Person p2("aab2",122);
    Person p3("aab3",2);
    Person p4("aab4",1);
    Person p5("aab4",1);
    vector<Person> v2;
    v2.reserve(5);//push_back前四个元素时，防止vector扩容, vector扩容时，也会调用元素的拷贝构造函数
    v2.push_back(p1);
    v2.push_back(p2);
    v2.push_back(p3);
    v2.push_back(p4);
    v2.push_back(p5);

//    sort(v2.begin(),v2.end());
//    cout<<"find or not :"<<binary_search(v2.begin(),v2.end(),p3)<<endl;

//    vector<Person>::iterator it=find(v2.begin(),v2.end(),p2); // Person override operator==
//    cout<<it->name<<"  "<<it->age<<endl;

//    vector<Person>::iterator it=adjacent_find(v2.begin(),v2.end());// 查找相邻重复元素

    cout<<"count:"<<count(v2.begin(),v2.end(),p5)<<endl; // count()  need override `operator==` , 底层调用count_if

}

//merge, 容器元素合并，并存储到另一容器中这 两个容器必须也是有序的
//random_shuffle:
void test16(){

    int arr[]={1,2,3,4,5};
    int arr2[]={5,6,8,9,88};
    vector<int > v1(arr,arr+ sizeof(arr)/ sizeof(int));
    vector<int > v2(arr2,arr2+ sizeof(arr2)/ sizeof(int));
    vector<int> target;
    target.resize(v1.size()+v2.size());
    merge(v1.begin(),v1.end(),v2.begin(),v2.end(),target.begin());
    for_each(target.begin(),target.end(),[](int v){cout<<v<<endl;});

    random_shuffle(target.begin(),target.end());//将容器元素随机打乱
    for_each(target.begin(),target.end(),[](int v){cout<<v<<endl;});
}

class greaterThan{
public:
    int val;
    greaterThan(int val):val(val){}
    bool operator()(int& val){
        return val>this->val;
    }
};
//copy replace,replace_if ,swap
void test17(){

    int arr[]={1,2,3,4,5};
    int arr2[]={5,6,8,9,88};
    vector<int > v1(arr,arr+ sizeof(arr)/ sizeof(int));
    vector<int > v2(arr2,arr2+ sizeof(arr2)/ sizeof(int));

    vector<int> target;
    target.resize(v1.size());
    copy(v1.begin(),v1.end(),target.begin());
//    for_each(target.begin(),target.end(),[](int v){cout<<v<<endl;});

//    replace(v1.begin(),v1.end(),3,300);
//    replace_if(v1.begin(),v1.end(),greaterThan(3),10);
//    for_each(v1.begin(),v1.end(),[](int v){cout<<v<<endl;});

    swap(v1,v2);
    for_each(v1.begin(),v1.end(),[](int v){cout<<v<<endl;});
}

//accumulate ,fill
#include <numeric>
void test18(){

    int arr[]={1,2,3,4,5};
    int arr2[]={5,6,8,9,88};
    vector<int > v1(arr,arr+ sizeof(arr)/ sizeof(int));
    vector<int > v2(arr2,arr2+ sizeof(arr2)/ sizeof(int));

//    fill(v2.begin(),v2.end(),100);
//    for_each(v2.begin(),v2.end(),[](int v){cout<<v<<endl;});

//    cout<<"sum:"<<accumulate(v1.begin(),v1.end(),0)<<endl;
}

//set_intersection,set_union, set_difference;
void test19(){

    int arr[]={1,2,3,4,5,6};
    int arr2[]={4,5,6,88};
    vector<int > v1(arr,arr+ sizeof(arr)/ sizeof(int));
    vector<int > v2(arr2,arr2+ sizeof(arr2)/ sizeof(int));

    vector<int> target;
//    target.resize(min(v1.size(),v2.size()));
//    vector<int>::iterator end=set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),target.begin()); // two sorted vector
//    for_each(target.begin(),target.end(),[](int v){cout<<v<<endl;});// target.end() is inaccurate
//    for_each(target.begin(),end,[](int v){cout<<v<<endl;});// target.end() is inaccurate

//    target.reserve(v1.size()+v2.size());
//    vector<int>::iterator end=set_union(v1.begin(),v1.end(),v2.begin(),v2.end(),target.begin());
//    for_each(target.begin(),end,[](int v){cout<<v<<endl;});

//    target.reserve(v1.size());
//    vector<int>::iterator end=set_difference(v1.begin(),v1.end(),v2.begin(),v2.end(),target.begin());
//    for_each(target.begin(),end,[](int v){cout<<v<<endl;});

    target.reserve(v2.size());
    vector<int>::iterator end=set_difference(v2.begin(),v2.end(),v1.begin(),v1.end(),target.begin());
    for_each(target.begin(),end,[](int v){cout<<v<<endl;});
}

//speech contest;
void test20(){



}






int main(){


//    test1();
//    test2();
//    test3();
//    test4();
//    test5();
//    test7();
//    test8();
//    test9();
//    test10();
//    test11();
    test12();
//    test13();
//    test14();
//    test15();
//    test16();
//    test17();
//    test18();
//    test19();

}