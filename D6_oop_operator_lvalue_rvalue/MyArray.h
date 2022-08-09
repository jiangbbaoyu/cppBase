//
// Created by aaab on 11/8/20.
//

#ifndef CPPBASIC_MYARRAY_H
#define CPPBASIC_MYARRAY_H
#endif //CPPBASIC_MYARRAY_H


#include <iostream>
using namespace std;
class MyArray{
public:
    MyArray();
    MyArray(int capacity);
    MyArray(const MyArray& array);
    ~MyArray();

    //inset last
    void insertLast(int ele);
    int get(int index);
    void set(int index,int val);
    int size();
    int capacity();
    int& operator[](int index);

private:
    int * pAddress;
    int m_size;
    int m_capacity;
};
