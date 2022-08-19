//
// Created by aaab on 8/19/22.
//

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <forward_list>

void test1() {

    std::string s = "abc";
    const char *cchar = s.c_str();
    std::string str3 = cchar;

    std::cout << str3 << std::endl;


    std::forward_list<const char *> articals2 = {"a", "b", "c"};
    std::vector<std::string> strs(articals2.begin(), articals2.end());
    for (auto str:strs) {
        std::cout << str << std::flush;
    }

//    std::list<const char*> strs3(strs.begin(),strs.end()); // error, string can not convert to const char*

}

void test2() {
    std::string s = "abc";
    std::string s2 = "abcc";

    s.swap(s2);
    std::cout << s << std::endl;
    std::cout << s2 << std::endl;
    std::cout << s.max_size() << std::endl;
}

void test3() {
    std::vector<std::string *> strs;
    std::string str = "abc";
    strs.push_back(&str);
    str = "a";
    std::cout << str << std::endl;
    for (auto s:strs) {
        std::cout << *s << std::endl;
    }

}


class CExample {
private:
    int a;
public:
    CExample(int b) {
        a = b;
        printf("constructor is called\n");
    }

    //拷贝构造函数
    CExample(const CExample &c) {
        a = c.a;
        printf("copy constructor is called\n");
    }

    //析构函数
    ~CExample() {
        std::cout << "destructor is called\n";
    }

    void Show() {
        std::cout << a << std::endl;
    }
};

void test4() {
    std::list<CExample> list;
    list.push_back(CExample(2)); // construct and copy
    list.emplace_back(1); // construct ,no copy
}

void test5() {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6};

    // 删除偶数，复制奇数
    for(auto b=nums.begin(),e=nums.end();b!=e;e=nums.end()){ // end 迭代器要每次都获取最新的

        if(*b%2){
            b= nums.insert(b,*b);
            b+=2;
        }else{
            b = nums.erase(b);
        }
    }

    for (auto n:nums) {
        std::cout << n << std::flush;
    }
}

void test6(){
    std::string numbers("0123456789");
    std::string str("j239084kj2h3");
//    std::string::size_type pos = 0;
//    while((pos=str.find_first_of(numbers,pos))
//        !=std::string::npos){
//
//        std::cout<< pos<<std::endl;
//        ++pos;
//    }
    std::string::size_type pos = str.size()-1;
    while((pos=str.find_last_of(numbers,pos))
        !=std::string::npos){

        std::cout<< pos<<std::endl;
        --pos;
    }
}

#include <stack>
#include <queue>
void test7(){
    std::stack<int,std::vector<int>> stack;
    stack.push(12);
    int a=1;
    stack.push(a);


    std::priority_queue<int,std::deque<int>> pq;
    pq.push(12);
    pq.push(2);
    pq.push(312);
    pq.push(123);

    while(!pq.empty()){
        std::cout<<pq.top()<<std::endl;
        pq.pop();
    }



}


int main() {
//    test1();

//    test2();
//    test3();

//    test4();
//    test5();

//    test6();
    test7();
}
