//
// Created by aaab on 8/22/22.
//

#ifndef CPPBASIC_STR_VEC_H
#define CPPBASIC_STR_VEC_H

#include <string>
#include <memory>


class str_vec{
private:
    static std::allocator<std::string> alloc;
    std::string* elements;
    std::string* first_free;
    std::string* cap;

    void chk_and_reallocate();
    std::pair<std::string*,std::string*> allocate_and_copy(const std::string* begin,const std::string* end);
    void free();
    void reallocate();

public:

    str_vec():elements(nullptr),first_free(nullptr),cap(nullptr){}
    str_vec(const str_vec& other);
    str_vec(str_vec&& other) noexcept;
    str_vec& operator=(const str_vec& other);
    str_vec& operator=(str_vec&& other);
    str_vec& operator=(std::initializer_list<std::string> il);

    std::string& operator[](std::size_t n);
    const std::string& operator[](std::size_t n) const;

    ~str_vec();

    void push_back(const std::string& ele);
    size_t size();
    size_t capacity();
    std::string* begin() const;
    std::string* end() const;
};


#endif //CPPBASIC_STR_VEC_H
