#include "WalletDAOMariaDB.h"
#include <stdexcept>
#include <cstring>
#include <vector>

WalletDAOMariaDB::WalletDAOMariaDB() {
    _conn = DatabaseConnection::getInstance().getConnection();
}

int WalletDAOMariaDB::addWallet(const Wallet& wallet) {
    const char* query = "INSERT INTO CARTEIRA (Titular, Corretora) VALUES (?, ?)";

    MYSQL_STMT* stmt = mysql_stmt_init(_conn);
    if (!stmt) {
        throw std::runtime_error("Error in mysql_stmt_init()");
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
        std::string error_msg = "Error in mysql_stmt_prepare(): ";
        error_msg += mysql_stmt_error(stmt);
        mysql_stmt_close(stmt);
        throw std::runtime_error(error_msg);
    }

    MYSQL_BIND params[2];
    memset(params, 0, sizeof(params));

    string ownerName = wallet.getOwnerName();
    string broker = wallet.getBroker();

    params[0].buffer_type = MYSQL_TYPE_STRING;
    params[0].buffer = (char*)ownerName.c_str();
    params[0].buffer_length = ownerName.length();

    params[1].buffer_type = MYSQL_TYPE_STRING;
    params[1].buffer = (char*)broker.c_str();
    params[1].buffer_length = broker.length();

    if (mysql_stmt_bind_param(stmt, params) != 0) {
        std::string error_msg = "Error in mysql_stmt_bind_param(): ";
        error_msg += mysql_stmt_error(stmt);
        mysql_stmt_close(stmt);
        throw std::runtime_error(error_msg);
    }

    if (mysql_stmt_execute(stmt) != 0) {
        std::string error_msg = "Error in mysql_stmt_execute(): ";
        error_msg += mysql_stmt_error(stmt);
        mysql_stmt_close(stmt);
        throw std::runtime_error(error_msg);
    }

    int newId = mysql_insert_id(_conn);

    mysql_stmt_close(stmt);

    return newId;
}

Wallet* WalletDAOMariaDB::getWalletById(int id) {
    const char* query = "SELECT IdCarteira, Titular, Corretora FROM CARTEIRA WHERE IdCarteira = ?";

    MYSQL_STMT* stmt = mysql_stmt_init(_conn);
    if (!stmt) throw std::runtime_error("Error in mysql_stmt_init()");

    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    MYSQL_BIND param[1];
    memset(param, 0, sizeof(param));
    param[0].buffer_type = MYSQL_TYPE_LONG;
    param[0].buffer = &id;

    if (mysql_stmt_bind_param(stmt, param) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    if (mysql_stmt_execute(stmt) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    MYSQL_BIND result[3];
    memset(result, 0, sizeof(result));

    int result_id;
    char result_owner[51], result_broker[51];
    unsigned long length[3];

    result[0].buffer_type = MYSQL_TYPE_LONG;
    result[0].buffer = &result_id;

    result[1].buffer_type = MYSQL_TYPE_STRING;
    result[1].buffer = result_owner;
    result[1].buffer_length = sizeof(result_owner);
    result[1].length = &length[1];

    result[2].buffer_type = MYSQL_TYPE_STRING;
    result[2].buffer = result_broker;
    result[2].buffer_length = sizeof(result_broker);
    result[2].length = &length[2];

    if (mysql_stmt_bind_result(stmt, result) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }
    if (mysql_stmt_store_result(stmt) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    Wallet* wallet = nullptr;
    if (mysql_stmt_fetch(stmt) == 0) {
        wallet = new Wallet(result_id, result_owner, result_broker);
    }

    mysql_stmt_close(stmt);
    return wallet;
}

vector<Wallet> WalletDAOMariaDB::getAllWallets() {
    const char* query = "SELECT IdCarteira, Titular, Corretora FROM CARTEIRA";

    MYSQL_STMT* stmt = mysql_stmt_init(_conn);
    if (!stmt) throw std::runtime_error("Error in mysql_stmt_init()");

    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }
    if (mysql_stmt_execute(stmt) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    vector<Wallet> wallets;
    int result_id;
    char result_owner[51], result_broker[51];
    unsigned long length[3];
    MYSQL_BIND result[3];
    memset(result, 0, sizeof(result));

    result[0].buffer_type = MYSQL_TYPE_LONG;
    result[0].buffer = &result_id;
    result[1].buffer_type = MYSQL_TYPE_STRING;
    result[1].buffer = result_owner;
    result[1].buffer_length = sizeof(result_owner);
    result[1].length = &length[1];
    result[2].buffer_type = MYSQL_TYPE_STRING;
    result[2].buffer = result_broker;
    result[2].buffer_length = sizeof(result_broker);
    result[2].length = &length[2];

    if (mysql_stmt_bind_result(stmt, result) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }
    if (mysql_stmt_store_result(stmt) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    while (mysql_stmt_fetch(stmt) == 0) {
        wallets.emplace_back(result_id, result_owner, result_broker);
    }

    mysql_stmt_close(stmt);
    return wallets;
}

bool WalletDAOMariaDB::updateWallet(const Wallet& wallet) {
    const char* query = "UPDATE CARTEIRA SET Titular = ?, Corretora = ? WHERE IdCarteira = ?";

    MYSQL_STMT* stmt = mysql_stmt_init(_conn);
    if (!stmt) throw std::runtime_error("Error in mysql_stmt_init()");

    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    MYSQL_BIND params[3];
    memset(params, 0, sizeof(params));

    string ownerName = wallet.getOwnerName();
    string broker = wallet.getBroker();
    int id = wallet.getId();

    params[0].buffer_type = MYSQL_TYPE_STRING;
    params[0].buffer = (char*)ownerName.c_str();
    params[0].buffer_length = ownerName.length();

    params[1].buffer_type = MYSQL_TYPE_STRING;
    params[1].buffer = (char*)broker.c_str();
    params[1].buffer_length = broker.length();

    params[2].buffer_type = MYSQL_TYPE_LONG;
    params[2].buffer = &id;

    if (mysql_stmt_bind_param(stmt, params) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    if (mysql_stmt_execute(stmt) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    bool success = mysql_stmt_affected_rows(stmt) > 0;
    mysql_stmt_close(stmt);
    return success;
}

bool WalletDAOMariaDB::deleteWallet(int id) {
    const char* query = "DELETE FROM CARTEIRA WHERE IdCarteira = ?";

    MYSQL_STMT* stmt = mysql_stmt_init(_conn);
    if (!stmt) throw std::runtime_error("Error in mysql_stmt_init()");

    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    MYSQL_BIND param[1];
    memset(param, 0, sizeof(param));
    param[0].buffer_type = MYSQL_TYPE_LONG;
    param[0].buffer = &id;

    if (mysql_stmt_bind_param(stmt, param) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    if (mysql_stmt_execute(stmt) != 0) {
        throw std::runtime_error(mysql_stmt_error(stmt));
    }

    bool success = mysql_stmt_affected_rows(stmt) > 0;
    mysql_stmt_close(stmt);
    return success;
}
