//
// Created by aaab on 11/9/20.
//

#ifndef CPPBASIC_MYSTRING_H
#define CPPBASIC_MYSTRING_H

#endif //CPPBASIC_MYSTRING_H

#include <iostream>]
using namespace std;

class MyString{
    friend ostream& operator<<(ostream& cout,const MyString& str);
    friend istream& operator>>(istream& cin, MyString& str);
public:
    MyString();
    MyString(const char* str);
    MyString(const MyString& str);
    ~MyString();

    int getSize();


    MyString&  operator=(const char* str);
    MyString&  operator=(const MyString& str);
    char&  operator[](int index);
    MyString operator+(MyString& str);
    MyString operator+(const char* str);
    bool operator==(const char* str);
    bool operator==(const MyString& str);




private:
    char* p_str;
    int size;
};
