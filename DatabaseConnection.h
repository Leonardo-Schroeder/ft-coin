#ifndef DATABASECONNECTION_H_
#define DATABASECONNECTION_H_

#include <mysql/mysql.h>
#include <string>
#include <stdexcept>

class DatabaseConnection {
public:
    static DatabaseConnection& getInstance();
    MYSQL* getConnection();

    DatabaseConnection(const DatabaseConnection&) = delete;
    void operator=(const DatabaseConnection&) = delete;

private:
    DatabaseConnection();
    ~DatabaseConnection();

    MYSQL* _connection;
};

#endif /* DATABASECONNECTION_H_ */
