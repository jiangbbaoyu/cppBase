#ifndef BASKET_H
#define BASKET_H

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <utility>
#include <cstddef>
#include <stdexcept>
#include <memory>
#include "Quote.h"
class Basket {
public:
	void add_item(const Quote& sale){
	    items.insert(std::shared_ptr<Quote>(sale.clone()));
	}

	void add_item(Quote&& sale){
	    items.insert( std::shared_ptr<Quote>(std::move(sale).clone()));
	}

    double total_receipt(std::ostream&) const;
private:
	// function to compare shared_ptrs needed by the multiset member
	static bool compare(const std::shared_ptr<Quote> &lhs,
	                    const std::shared_ptr<Quote> &rhs){
	    return lhs->isbn() < rhs->isbn();
	}

	// multiset to hold multiple quotes, ordered by the compare member
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*>  items{compare};
};

#endif
