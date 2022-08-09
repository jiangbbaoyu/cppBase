//
// Created by aaab on 11/10/20.
//

#ifndef CPPBASIC_MYARRAY_HPP
#define CPPBASIC_MYARRAY_HPP

#include <clocale>

template <class T>
class MyArray{
public:
    explicit MyArray(int capacity):capacity(capacity),size(0){
        this->pAddress=new T[this->capacity];
        cout<<"myarray cons"<<endl;
    }

    MyArray(MyArray& other){
        this->capacity=other.capacity;
        this->size=other.size;
        this->pAddress=new T[other.capacity];
        for (int i = 0; i <size ; ++i) {
            this->pAddress[i]=other.pAddress[i];
        }
    }
    ~MyArray(){
        if(this->pAddress){
            delete[] this->pAddress;
            this->pAddress=NULL;
        }
        cout<<"destructor myarray"<<endl;
    }
    MyArray& operator=(MyArray& other){
        if(this->pAddress!=NULL){
            delete[] this->pAddress;
            this->pAddress=NULL;
        }
        this->capacity=other.capacity;
        this->size=other.size;
        this->pAddress=new T[other.capacity];
        for (int i = 0; i <size ; ++i) {
            this->pAddress[i]=other.pAddress[i];
        }
        return *this;
    }
    T& operator[](int index){
        return this->pAddress[index];

    }
    void insertLast(const T& val){
        this->pAddress[this->size]=val;
        size++;
    }
    int getSize(){
        return this->size;
    }
    int getCapacity(){
        return this->capacity;
    }
private:
    T* pAddress;
    int capacity;
    int size;
};

#endif //CPPBASIC_MYARRAY_HPP
