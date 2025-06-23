#ifndef ORACLE_DAO_MEMORY_H
#define ORACLE_DAO_MEMORY_H

#include "IOracleDAO.h"

class OracleDAOMemory : public IOracleDAO {
private:
    vector<Oracle> quotes;

public:
    void addQuote(const Oracle& quote) override;
    void populateMockData();
    Oracle* getQuoteByDate(const string& date) override;
    vector<Oracle> getAllQuotes() override;
};

#endif
