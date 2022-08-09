//
// Created by aaab on 11/9/20.
//
#include "mystring.h"
#include "string.h"

ostream& operator<<(ostream& cout,const MyString& str){
    cout<<str.p_str;
    return cout;
}
istream& operator>>(istream& cin, MyString& str){
    if(str.p_str!=NULL){
        delete[] str.p_str;
        str.p_str=NULL;
    }
    char buf[1024];
    cin>>buf;
    str.p_str=new char[strlen(buf)+1];
    strcpy(str.p_str,buf);
    str.size=strlen(buf);
}

MyString::MyString() {
    this->p_str=NULL;
    this->size=0;
}

MyString::MyString(const char *str) {
//    cout<<"cons"<<endl;
    this->p_str=new char[strlen(str)+1];
    strcpy(this->p_str,str);
    this->size=strlen(str);
}
MyString::MyString(const MyString &str) {
//    cout<<"copy cons"<<endl;
    this->p_str=new char[strlen(str.p_str)+1];
    strcpy(this->p_str,str.p_str);
    this->size=str.size;
}
MyString::~MyString() {
//    cout<<"destructor"<<endl;
    if(this->p_str!=NULL){
        delete[] this->p_str;
        this->p_str=NULL;
    }
}


MyString& MyString::operator=(const char *str) {
    if(this->p_str!=NULL){
        delete[] this->p_str;
        this->p_str=NULL;
    }
    this->p_str=new char[strlen(str)+1];
    strcpy(this->p_str,str);
    this->size=strlen(str);
    return *this;
}
int MyString::getSize() {
    return this->size;
}

MyString& MyString::operator=(const MyString &str) {
    if(this->p_str!=NULL){
        delete[] this->p_str;
        this->p_str=NULL;
    }
    this->p_str=new char[strlen(str.p_str)+1];
    strcpy(this->p_str,str.p_str);
    this->size=strlen(str.p_str);
    return *this;

}
char& MyString::operator[](int index) {
    return this->p_str[index];
}
MyString MyString::operator+(const char *str) {
    int newSize=this->size+strlen(str);
    MyString res;
    res.p_str=new char[newSize+1];
    res.size=newSize;
    strcat(res.p_str,this->p_str);
    strcat(res.p_str,str);
    return res;

}
MyString MyString::operator+(MyString &str) {
    int newSize=this->size+strlen(str.p_str);
    MyString res;
    res.p_str=new char[newSize+1];
    res.size=newSize;
    strcat(res.p_str,this->p_str);
    strcat(res.p_str,str.p_str);
    return res;
}
bool MyString::operator==(const char *str) {
    if(strcmp(this->p_str,str)==0&&this->size==strlen(str)){
        return true;
    }
    return false;
}

bool MyString::operator==(const MyString &str) {
    if(strcmp(this->p_str,str.p_str)==0&&this->size==str.size){
        return true;
    }
    return false;
}

