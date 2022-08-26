//
// Created by aaab on 8/21/22.
//

#ifndef CPPBASIC_STR_BLOB_H
#define CPPBASIC_STR_BLOB_H

#include <vector>
#include <memory>
class str_blob{

public:
    using  size_type = std::vector<std::string>::size_type ;

    str_blob(std::initializer_list<std::string> il){
        data = std::make_shared<std::vector<std::string>>(il);
    }
    str_blob(){
        data = std::make_shared<std::vector<std::string>>();
    }

    std::string& front();
    std::string& back();

    void push_back(const::std::string& str) const {
        data->push_back(str);
    }
    size_type  size()const{
        return this->data->size();
    }

    bool empty() const{
        return data->empty();
    }


    const std::shared_ptr<std::vector<std::string>>& get_data() const{
        return data;
    }


private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string& msg);

};



#endif //CPPBASIC_STR_BLOB_H
