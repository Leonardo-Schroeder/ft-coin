#ifndef IORACLEDAO_H
#define IORACLEDAO_H

#include "Oracle.h"
#include <vector>

using namespace std;

class IOracleDAO {
public:
    virtual ~IOracleDAO() = default;

    virtual void addQuote(const Oracle& quote) = 0;
    virtual Oracle* getQuoteByDate(const string& date) = 0;
    virtual vector<Oracle> getAllQuotes() = 0;
    virtual void populateMockData() = 0;
};

#endif
