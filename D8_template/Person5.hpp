//
// Created by aaab on 11/10/20.
//

#ifndef CPPBASIC_PERSON5_HPP
#define CPPBASIC_PERSON5_HPP

#include <iostream>
using namespace std;
template <class T1,class T2>
class Person5{
public:
    Person5(T1 a,T2 b);
    void show();
    T1 a;
    T2 b;
};

template <class T1,class T2>
Person5<T1,T2>::Person5(T1 a, T2 b):a(a),b(b) {}
template <class T1,class T2>
void Person5<T1,T2>::show() {
    cout<<this->a<<"  "<<this->b<<endl;
}


#endif //CPPBASIC_PERSON5_HPP
