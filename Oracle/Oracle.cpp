#include "Oracle.h"
#include <sstream>

Oracle::Oracle() : date(""), price(0.0) {}

Oracle::Oracle(const string& date, double price) : date(date), price(price) {}

string Oracle::getDate() const {
    return date;
}

double Oracle::getPrice() const {
    return price;
}

void Oracle::setDate(const string& newDate) {
    date = newDate;
}

void Oracle::setPrice(double newPrice) {
    price = newPrice;
}

string Oracle::toString() const {
    ostringstream oss;
    oss << "Date: " << date << " | Price: " << price;
    return oss.str();
}
