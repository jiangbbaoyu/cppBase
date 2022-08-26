//
// Created by aaab on 8/24/22.
//

#ifndef CPPBASIC_BLOB_H
#define CPPBASIC_BLOB_H



#include <vector>
#include <memory>
template <typename T>class blob{

public:
    typedef T value_type;
    using  size_type = typename std::vector<T>::size_type ;

    blob(std::initializer_list<T> il){
        data = std::make_shared<std::vector<std::string>>(il);
    }
    blob();

    T& front();
    T& back();

    void push_back(const T& str) const {
        data->push_back(str);
    }
    size_type  size()const{
        return this->data->size();
    }

    bool empty() const{
        return data->empty();
    }


    const std::shared_ptr<std::vector<T>>& get_data() const{
        return data;
    }


private:
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i, const T& msg);

};

template <typename T>
blob<T>::blob(){
    data = std::make_shared<std::vector<T>>();
}

#endif //CPPBASIC_BLOB_H
