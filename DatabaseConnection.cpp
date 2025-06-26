#include "DatabaseConnection.h"
#include <iostream>

DatabaseConnection& DatabaseConnection::getInstance() {
    static DatabaseConnection instance;
    return instance;
}

DatabaseConnection::DatabaseConnection() {
    const char* DB_HOST = "143.106.243.64";
    const char* DB_USER = "PooI_25_B10";
    const char* DB_PASS = "602XMAgB2V";
    const char* DB_NAME = "PooI_25_B10";
    const unsigned int DB_PORT = 3306;

    _connection = mysql_init(nullptr);
    if (_connection == nullptr) {
        throw std::runtime_error("Failed to initialize MariaDB connection handler.");
    }

    if (mysql_real_connect(_connection, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, nullptr, 0) == nullptr) {
        std::string error_msg = "Failed to connect to database:";
        error_msg += mysql_error(_connection);
        mysql_close(_connection);
        throw std::runtime_error(error_msg);
    }

    //For Debug
    //std::cout << "-> MariaDB database connection successfully established!" << std::endl;
}

DatabaseConnection::~DatabaseConnection() {
    if (_connection != nullptr) {
        mysql_close(_connection);
        //For Debug
        //std::cout << "-> Connection to MariaDB database closed." << std::endl;
    }
}

MYSQL* DatabaseConnection::getConnection() {
    return _connection;
}
