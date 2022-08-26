//
// Created by aaab on 8/22/22.
//
#include "str_vec.h"

std::allocator<std::string> str_vec::alloc =std::allocator<std::string>(); // 初始化静态变量

void str_vec::chk_and_reallocate() {
    if(first_free==cap){
        reallocate();
    }
}
//void str_vec::reallocate() {
//    auto new_cap = size()? 2*size():4;
//    std::string* new_elements = alloc.allocate(new_cap);
//
//    auto cursor_old= elements, cursor_new = new_elements;
//    for(;elements!=first_free;++cursor_old,++cursor_new){
//        alloc.construct(cursor_new,std::move(*cursor_old));
//    }
//
//    free();
//
//    elements = new_elements;
//    first_free= cursor_new;
//    cap= new_elements+new_cap;
//}


void str_vec::reallocate() {
    auto new_cap = size()? 2*size():4;
    std::string* new_elements = alloc.allocate(new_cap);

    auto  cursor_new = new_elements;
    auto new_first_free = std::uninitialized_copy(std::make_move_iterator(elements),std::make_move_iterator(first_free),cursor_new);

    free();

    elements = new_elements;
    first_free= new_first_free;
    cap= new_elements+new_cap;
}

void str_vec::free() {
    if(elements){
        for(auto cursor= first_free-1;cursor!=elements;--cursor){
            alloc.destroy(cursor);
        }
        alloc.deallocate(elements,capacity());
    }
}

std::pair<std::string*,std::string*> str_vec::allocate_and_copy(const std::string *begin, const std::string *end) {
    auto new_elements = alloc.allocate(end - begin);

    //    auto cursor_new = new_elements;
//    for(auto cursor_old =begin; cursor_old!=end; ++cursor_old,++cursor_new){
//        allocator.construct(cursor_new,*cursor_old);
//    }
//    return {new_elements,cursor_new};

    return {new_elements, std::uninitialized_copy(begin, end, new_elements)};
}

str_vec::str_vec(const str_vec &other) {
    // other 为一个const 引用，因此只能调用 str_vec的 const 成员函数，因此需要将 begin, end 函数声明为常量成员函数
    auto pair = allocate_and_copy(other.begin(),other.end());

    this->elements = pair.first;
    this->first_free = pair.second;
    this->cap = pair.second;
}

str_vec& str_vec::operator=(const str_vec &other) {
    // other 为一个const 引用，因此只能调用 str_vec的 const 成员函数，因此需要将 begin, end 函数声明为常量成员函数
    auto pair = allocate_and_copy(other.begin(),other.end());

    free();

    this->elements = pair.first;
    this->first_free = pair.second;
    this->cap = pair.second;

    return *this;
}

str_vec::str_vec(str_vec &&other) noexcept: elements(other.elements),first_free(other.first_free),cap(other.cap) {
    other.elements = other.first_free = other.cap = nullptr; // 重置 移动源对象的指针状态，防止对移动源对象调用析构函数时，影响到现在的对象
}
str_vec& str_vec::operator=(str_vec &&other) {

    if(this!= &other){
        this->elements= other.elements;
        this->first_free = other.first_free;
        this->cap = other.cap;
    }

    return *this;
}
str_vec& str_vec::operator=(std::initializer_list<std::string> il) {
    auto pair = allocate_and_copy(il.begin(),il.end());
    free();

    elements= pair.first;
    first_free = cap = pair.second;

    return *this;
}

std::string& str_vec::operator[](std::size_t n){
    return elements[n];
}
const std::string& str_vec::operator[](std::size_t n) const{
    return elements[n];
}

str_vec::~str_vec() {
    free();
}


size_t str_vec::size() {
    return first_free-elements;
}
size_t str_vec::capacity() {
    return cap-elements;
}
std::string* str_vec::begin() const{
    return elements;
}
std::string* str_vec::end() const{
    return first_free;
}

void str_vec::push_back(const std::string &ele) {
    chk_and_reallocate();
    alloc.construct(first_free++,ele);
}