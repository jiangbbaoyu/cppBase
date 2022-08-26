
#include <cstddef>
using std::size_t;

#include <set>
using std::multiset; 

#include <string>
using std::string; 

#include <iostream>
using std::ostream; using std::endl; 
using std::cout;

#include "Basket.h"

double Basket::total_receipt(ostream &os) const
{
    double sum = 0.0;    // holds the running total 


    for (auto iter = items.cbegin();
              iter != items.cend();
              iter = items.upper_bound(*iter)) {
        sum += print_total(os, **iter, items.count(*iter));
    } 
	os << "Total Sale: " << sum << endl; // print the final overall total
    return sum;
}

