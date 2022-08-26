//
// Created by aaab on 8/21/22.
//


#include <iostream>
#include <memory>

class Sales_data {
public:
    Sales_data() {
        std::cout << "default cons call!" << std::endl;
    }

    Sales_data(const Sales_data &other) {
        this->isbn = other.isbn;
        std::cout << "copy cons call!" << std::endl;
    }

    Sales_data(int a) {
        std::cout << "params cons call!" << std::endl;
        this->isbn = std::to_string(a);
    }

    ~Sales_data() {
        std::cout << "destructor call!" << std::endl;
    }


    std::string isbn;
    long double num;
};

bool compareIsbn(const Sales_data &sd1, const Sales_data &sd2) {
    return sd1.isbn < sd2.isbn;
}


// 此处不能返回 std::shared_ptr<Sales_data>& ， 因为返回引用的话，该方法结束后，p临时变量就会被销毁，而函数外就会有一个指向 非法内存的引用
// 同时只有当 shared_ptr 对象被拷贝时，才会增加引用对象的引用计数
std::shared_ptr<Sales_data> test1() {
    std::shared_ptr<Sales_data> p = std::make_shared<Sales_data>();

//    auto p2 =p;
//    std::cout<<p2.use_count()<<std::endl;
//    std::cout<<p.use_count()<<std::endl;
    return p;


}

#include "str_blob.h"

void test2() {

    str_blob sb = {"a", "b", "c"};
    str_blob sb2 = sb;
    std::cout << sb2.get_data().use_count() << std::endl;
    sb2.push_back("d");

    std::cout << sb2.get_data()->size() << std::endl;
}

void test3() {


    int *p = new int;
    int *p2 = new int();
    std::cout << p << std::endl;
    std::cout << *p << std::endl;
    std::cout << p2 << std::endl;
    std::cout << *p2 << std::endl;

}

void test4() {

    std::unique_ptr<std::string> up(new std::string("abc"));

//    std::unique_ptr<std::string> up2(up.release());
//    std::cout<<*up2.get()<<std::endl;
//    std::cout<<*up.get()<<std::endl;

    std::unique_ptr<std::string> up3(new std::string("def"));
    up3.reset(up.release());
//    std::cout<<*up.get()<<std::endl;//
    std::cout << *up3.get() << std::endl;
    up3.reset();
    std::cout << up3.get() << std::endl;
}

std::unique_ptr<int> test5() {
    std::unique_ptr<int> up(new int(4));
//    std::unique_ptr<int> up2=up;
    return up;
}


void test6() {

    std::unique_ptr<Sales_data[]> up(new Sales_data[10]);
//    for(int i=0;i<10;i++){
//        up[i] = Sales_data(i);
//    }

    up.release();
    std::cout << "release over" << std::endl;

}

void test61() {

    std::shared_ptr<Sales_data> sp(new Sales_data[10], [](Sales_data *sd) { delete[] sd; });
    for (size_t i = 0; i < 10; i++) {
        *(sp.get() + i) = Sales_data(i);
    }

    sp.reset();
    std::cout << "reset over" << std::endl;

}

void test7() {

    std::allocator<int> allocator;
    int *sdp = allocator.allocate(3);
    int *cursor = sdp;
    while (cursor != sdp + 3) {
        std::cout << cursor << std::endl;
        cursor++;
    }


}

void test71() {

    std::allocator<Sales_data> allocator;
    Sales_data *sdp = allocator.allocate(3);
    Sales_data *cursor = sdp;
    int i = 0;
    while (cursor != sdp + 3) {
        std::cout << cursor << std::endl;

        allocator.construct(cursor, i);
        cursor++;
        i++;
    }


    while (cursor != sdp) {
        allocator.destroy(--cursor);
    }


}

int main() {

//    const std::shared_ptr<Sales_data>& p=test1();
//    std::cout<<p.use_count()<<std::endl;
//    std::cout<<"test end"<<std::endl;

//    test2();
//    test3();

//    test4();

//    test6();
//    test61();
//    test7();
    test71();


}

