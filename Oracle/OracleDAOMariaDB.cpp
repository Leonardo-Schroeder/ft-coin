#include "OracleDAOMariaDB.h"
#include <stdexcept>
#include <iostream>
#include <cstring>

OracleDAOMariaDB::OracleDAOMariaDB() {
    _conn = DatabaseConnection::getInstance().getConnection();
}

void OracleDAOMariaDB::addQuote(const Oracle& quote) {
    const char* query = "INSERT INTO ORACULO (Data, Cotacao) VALUES (STR_TO_DATE(?, '%Y-%m-%d'), ?) ON DUPLICATE KEY UPDATE Cotacao = VALUES(Cotacao)";

    MYSQL_STMT* stmt = mysql_stmt_init(_conn);
    if (!stmt) throw std::runtime_error("mysql_stmt_init() failed");

    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    MYSQL_BIND params[2];
    memset(params, 0, sizeof(params));

    string dateStr = quote.getDate();
    string priceStr = to_string(quote.getPrice());

    params[0].buffer_type = MYSQL_TYPE_STRING;
    params[0].buffer = (char*)dateStr.c_str();
    params[0].buffer_length = dateStr.length();

    params[1].buffer_type = MYSQL_TYPE_DECIMAL;
    params[1].buffer = (char*)priceStr.c_str();
    params[1].buffer_length = priceStr.length();

    if (mysql_stmt_bind_param(stmt, params) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    if (mysql_stmt_execute(stmt) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    mysql_stmt_close(stmt);
} //Not accessible to the user

Oracle* OracleDAOMariaDB::getQuoteByDate(const string& date) {
    const char* query = "SELECT DATE_FORMAT(Data, '%Y-%m-%d'), Cotacao FROM ORACULO WHERE Data = STR_TO_DATE(?, '%Y-%m-%d')";

    MYSQL_STMT* stmt = mysql_stmt_init(_conn);
    if (!stmt) throw std::runtime_error("mysql_stmt_init() failed");

    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    MYSQL_BIND param[1];
    memset(param, 0, sizeof(param));
    param[0].buffer_type = MYSQL_TYPE_STRING;
    param[0].buffer = (char*)date.c_str();
    param[0].buffer_length = date.length();

    if (mysql_stmt_bind_param(stmt, param) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    if (mysql_stmt_execute(stmt) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    char result_date[11];
    double result_price;
    MYSQL_BIND result_bind[2];
    memset(result_bind, 0, sizeof(result_bind));

    result_bind[0].buffer_type = MYSQL_TYPE_STRING;
    result_bind[0].buffer = result_date;
    result_bind[0].buffer_length = sizeof(result_date);

    result_bind[1].buffer_type = MYSQL_TYPE_DOUBLE;
    result_bind[1].buffer = &result_price;

    if (mysql_stmt_bind_result(stmt, result_bind) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }
    if (mysql_stmt_store_result(stmt) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    Oracle* oracle = nullptr;
    if (mysql_stmt_fetch(stmt) == 0) {
        oracle = new Oracle(string(result_date), result_price);
    }

    mysql_stmt_close(stmt);
    return oracle;
}

vector<Oracle> OracleDAOMariaDB::getAllQuotes() {
    vector<Oracle> quotes;
    const char* query = "SELECT DATE_FORMAT(Data, '%Y-%m-%d'), Cotacao FROM ORACULO ORDER BY Data";

    if (mysql_query(_conn, query)) {
        throw std::runtime_error(mysql_error(_conn));
    }

    MYSQL_RES* result = mysql_store_result(_conn);
    if (result == nullptr) {
        throw std::runtime_error(mysql_error(_conn));
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        string date = row[0] ? row[0] : "";
        double price = row[1] ? stod(row[1]) : 0.0;
        quotes.emplace_back(date, price);
    }

    mysql_free_result(result);
    return quotes;
}

void OracleDAOMariaDB::populateMockData() {
    std::cout << "Ok" << std::endl;
} //Debug Function
