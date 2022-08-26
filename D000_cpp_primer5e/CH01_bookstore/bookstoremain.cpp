//
// Created by aaab on 8/9/22.
//
#include <iostream>

#include "Sales_item.h"
/**
 * p21
 * 读取销售记录，生成每本书的销售报告
 * @return
 */
int main(){

    Sales_item total;

    if(std::cin >> total){
        Sales_item curr;
        while(std::cin>>curr){
            if(total.isbn()==curr.isbn()){
                total += curr;
            }else{
                std::cout<< total<<std::endl;
                total = curr;
            }
        }

        std::cout<< total<<std::endl;

    }else{
        std::cout<< "input error !" << std::endl;
        return -1;
    }

    return 0;

}

