#include "MovementDAOMariaDB.h"
#include <stdexcept>
#include <cstring>
#include <iostream>
#include <vector>

MovementDAOMariaDB::MovementDAOMariaDB() {
    _conn = DatabaseConnection::getInstance().getConnection();
}

void MovementDAOMariaDB::addMovement(Movement movement) {
    const char* query = "INSERT INTO MOVIMENTACAO (IdCarteira, Data, TipoOperacao, Quantidade) VALUES (?, STR_TO_DATE(?, '%Y-%m-%d'), ?, ?)";

    MYSQL_STMT* stmt = mysql_stmt_init(_conn);
    if (!stmt) throw std::runtime_error("mysql_stmt_init() failed");

    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
        std::string err = "mysql_stmt_prepare() failed: " + std::string(mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        throw std::runtime_error(err);
    }

    MYSQL_BIND params[4];
    memset(params, 0, sizeof(params));

    int walletId = movement.getWalletId();
    string dateStr = movement.getDate();
    string opTypeStr(1, movement.getType());
    double quantity = movement.getQuantity();
    string quantityStr = to_string(quantity);

    params[0].buffer_type = MYSQL_TYPE_LONG;
    params[0].buffer = &walletId;

    params[1].buffer_type = MYSQL_TYPE_STRING;
    params[1].buffer = (char*)dateStr.c_str();
    params[1].buffer_length = dateStr.length();

    params[2].buffer_type = MYSQL_TYPE_STRING;
    params[2].buffer = (char*)opTypeStr.c_str();
    params[2].buffer_length = opTypeStr.length();

    params[3].buffer_type = MYSQL_TYPE_DECIMAL;
    params[3].buffer = (char*)quantityStr.c_str();
    params[3].buffer_length = quantityStr.length();

    if (mysql_stmt_bind_param(stmt, params) != 0) {
        std::string err = "mysql_stmt_bind_param() failed: " + std::string(mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        throw std::runtime_error(err);
    }

    if (mysql_stmt_execute(stmt) != 0) {
        std::string err = "mysql_stmt_execute() failed: " + std::string(mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        throw std::runtime_error(err);
    }

    mysql_stmt_close(stmt);
}

vector<Movement> MovementDAOMariaDB::getMovementsByWalletId(int walletId) {
    const char* query = "SELECT IdMovimento, IdCarteira, DATE_FORMAT(Data, '%Y-%m-%d'), TipoOperacao, Quantidade FROM MOVIMENTACAO WHERE IdCarteira = ? ORDER BY Data DESC";

    MYSQL_STMT* stmt = mysql_stmt_init(_conn);
    if (!stmt) throw std::runtime_error("mysql_stmt_init() failed");

    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
         throw std::runtime_error(mysql_stmt_error(stmt));
    }

    MYSQL_BIND param[1];
    memset(param, 0, sizeof(param));
    param[0].buffer_type = MYSQL_TYPE_LONG;
    param[0].buffer = &walletId;

    if (mysql_stmt_bind_param(stmt, param) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    if (mysql_stmt_execute(stmt) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    vector<Movement> movements;
    int movId, wId;
    char dateBuffer[11], typeBuffer[2];
    double quantity;
    MYSQL_BIND result[5];
    memset(result, 0, sizeof(result));

    result[0].buffer_type = MYSQL_TYPE_LONG;
    result[0].buffer = &movId;
    result[1].buffer_type = MYSQL_TYPE_LONG;
    result[1].buffer = &wId;
    result[2].buffer_type = MYSQL_TYPE_STRING;
    result[2].buffer = dateBuffer;
    result[2].buffer_length = sizeof(dateBuffer);
    result[3].buffer_type = MYSQL_TYPE_STRING;
    result[3].buffer = typeBuffer;
    result[3].buffer_length = sizeof(typeBuffer);
    result[4].buffer_type = MYSQL_TYPE_DOUBLE;
    result[4].buffer = &quantity;

    if (mysql_stmt_bind_result(stmt, result) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }
    if (mysql_stmt_store_result(stmt) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    while (mysql_stmt_fetch(stmt) == 0) {
        movements.emplace_back(movId, wId, string(dateBuffer), typeBuffer[0], quantity);
    }

    mysql_stmt_close(stmt);
    return movements;
}


vector<Movement> MovementDAOMariaDB::getAllMovements() {
    const char* query = "SELECT IdMovimento, IdCarteira, DATE_FORMAT(Data, '%Y-%m-%d'), TipoOperacao, Quantidade FROM MOVIMENTACAO ORDER BY IdCarteira, Data DESC";

    MYSQL_STMT* stmt = mysql_stmt_init(_conn);
    if (!stmt) throw std::runtime_error("mysql_stmt_init() failed");

    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
         throw std::runtime_error(mysql_stmt_error(stmt));
    }

    if (mysql_stmt_execute(stmt) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    vector<Movement> movements;
    int movId, wId;
    char dateBuffer[11], typeBuffer[2];
    double quantity;
    MYSQL_BIND result[5];
    memset(result, 0, sizeof(result));

    result[0].buffer_type = MYSQL_TYPE_LONG;
    result[0].buffer = &movId;
    result[1].buffer_type = MYSQL_TYPE_LONG;
    result[1].buffer = &wId;
    result[2].buffer_type = MYSQL_TYPE_STRING;
    result[2].buffer = dateBuffer;
    result[2].buffer_length = sizeof(dateBuffer);
    result[3].buffer_type = MYSQL_TYPE_STRING;
    result[3].buffer = typeBuffer;
    result[3].buffer_length = sizeof(typeBuffer);
    result[4].buffer_type = MYSQL_TYPE_DOUBLE;
    result[4].buffer = &quantity;

    if (mysql_stmt_bind_result(stmt, result) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }
    if (mysql_stmt_store_result(stmt) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    while (mysql_stmt_fetch(stmt) == 0) {
        movements.emplace_back(movId, wId, string(dateBuffer), typeBuffer[0], quantity);
    }

    mysql_stmt_close(stmt);
    return movements;
}

int MovementDAOMariaDB::getNextId() {
    const char* dbName = "Pool_25_B10";
    string query = "SELECT AUTO_INCREMENT FROM information_schema.TABLES WHERE TABLE_SCHEMA = '";
    query += dbName;
    query += "' AND TABLE_NAME = 'MOVIMENTACAO'";

    if (mysql_query(_conn, query.c_str())) {
        throw std::runtime_error(mysql_error(_conn));
    }

    MYSQL_RES* result = mysql_store_result(_conn);
    if (!result) {
        throw std::runtime_error(mysql_error(_conn));
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (!row || !row[0]) {
        mysql_free_result(result);
        return 1;
    }

    int nextId = stoi(row[0]);
    mysql_free_result(result);

    return nextId;
}
