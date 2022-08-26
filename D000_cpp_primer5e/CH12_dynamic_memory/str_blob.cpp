//
// Created by aaab on 8/21/22.
//
#include "str_blob.h"
#include <string>

void str_blob::check(str_blob::size_type i, const std::string &msg) {
    if(i>=data->size()){
        throw std::out_of_range(msg);
    }
}

std::string& str_blob::front() {
    check(0,"front check");
//    return (*data)[0];
    return data->front();
}

std::string& str_blob::back() {
    check(data->size(),"back check");
    return data->back();
}
