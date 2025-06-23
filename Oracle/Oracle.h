#ifndef ORACLE_H
#define ORACLE_H

#include <string>

using namespace std;

class Oracle {
private:
    string date;
    double price;

public:
    Oracle();
    Oracle(const string& date, double price);

    string getDate() const;
    double getPrice() const;

    void setDate(const string& newDate);
    void setPrice(double newPrice);

    string toString() const;
};

#endif
