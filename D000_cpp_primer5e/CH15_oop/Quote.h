//
// Created by aaab on 8/24/22.
//

#ifndef CPPBASIC_QUOTE_H
#define CPPBASIC_QUOTE_H

#include <string>


class Quote{
public:
    Quote()= default;
    Quote(const double price,const std::string& bookNo):price(price),bookNo(bookNo){}
    virtual double net_price(std::size_t n) const;
    virtual ~Quote()= default;

    virtual Quote* clone() const & {
        return new Quote(*this);
    }
    virtual Quote* clone() && {
        return new Quote(std::move(*this));
    }
    std::string isbn() const {
        return bookNo;
    }

protected:
    double price;
private:
    std::string bookNo;
};
double Quote::net_price(std::size_t n) const {
    return 0.0;
}

class Bulk_quote:public Quote{
public:
    Bulk_quote()= default;
    Bulk_quote(std::size_t min_quantity,double discount,double price,const std::string& bookNo):
            Quote(price,bookNo),min_quantity(min_quantity),discount(discount){

    }
    ~Bulk_quote(){};

    virtual double net_price(std::size_t n) const override ;
    Bulk_quote* clone() const & {return new Bulk_quote(*this);}
    Bulk_quote* clone() && {return new Bulk_quote(std::move(*this));}


private:
    std::size_t min_quantity;
    double discount;

};
double Bulk_quote::net_price(std::size_t n) const {
//    std::cout<<Quote::price<<std::endl;
//    std::cout<<Bulk_quote::price<<std::endl;
//    std::cout<<this->price<<std::endl;
//    std::cout<<price<<std::endl;

    return 0.0;
}


double print_total(std::ostream &, const Quote&, std::size_t){
    return 0.0;
}

#endif //CPPBASIC_QUOTE_H
