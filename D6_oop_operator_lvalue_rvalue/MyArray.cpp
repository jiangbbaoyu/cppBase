//
// Created by aaab on 11/8/20.
//
#include "MyArray.h"
MyArray::MyArray() {
    this->m_capacity=100;
    this->m_size=0;
    this->pAddress=new int[this->m_capacity];
}
MyArray::MyArray(int capacity) {
    this->m_capacity=capacity;
    this->m_size=0;
    this->pAddress=new int[this->m_capacity];

}
MyArray::MyArray(const MyArray &array) {
    cout<<"copy cons"<<endl;
    this->pAddress=new int[array.m_capacity];
    this->m_size=array.m_size;
    this->m_capacity=array.m_capacity;
    for(int i=0;i<array.m_size;i++){
        this->pAddress[i]=array.pAddress[i];
    }
}
MyArray::~MyArray() {
    cout<<"destructor myarray"<<endl;
    if(this->pAddress!=NULL){
        delete[] this->pAddress;
        this->pAddress=NULL;
    }
}
void MyArray::insertLast(int ele) {
    if(this->m_size<this->m_capacity){
        this->pAddress[this->m_size]=ele;
        this->m_size++;
    }else{
        // 扩容，并插入
    }
}
int MyArray::get(int index) {
    return this->pAddress[index];
}
void MyArray::set(int index, int val) {
    if(index<this->m_size){
        this->pAddress[index]=val;
    }
}

int MyArray::size() {
    return this->m_size;
}
int MyArray::capacity() {
    return this->m_capacity;
}

int& MyArray::operator[](int index) {
    return this->pAddress[index];
}

