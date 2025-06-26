#ifndef ORACLEDAOMARIADB_H_
#define ORACLEDAOMARIADB_H_

#include "IOracleDAO.h"
#include "../DatabaseConnection.h"

class OracleDAOMariaDB : public IOracleDAO {
private:
    MYSQL* _conn;

public:
    OracleDAOMariaDB();
    virtual ~OracleDAOMariaDB() = default;

    void addQuote(const Oracle& quote) override;
    Oracle* getQuoteByDate(const string& date) override;
    vector<Oracle> getAllQuotes() override;
    void populateMockData() override;
};

#endif /* ORACLEDAOMARIADB_H_ */
