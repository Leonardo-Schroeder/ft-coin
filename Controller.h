#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <memory>
#include <vector>
#include <string>
#include "WalletService.h"
#include "IWalletDAO.h"
#include "HelpService.h"
#include "./Oracle/IOracleDAO.h"
#include "./Oracle/OracleDAOMemory.h"

using namespace std;

enum class DataBaseSelector {
    MEMORY,
    MARIADB
};

class Controller {
private:
    shared_ptr<IWalletDAO> memoryDBConnection;
    shared_ptr<IWalletDAO> serverDBConnection;
    shared_ptr<IOracleDAO> oracleDAO = make_shared<OracleDAOMemory>();
    unique_ptr<WalletService> walletService;
    HelpService helpService;
    void launchActions(string title, vector<string> menuItems, vector<void (Controller::*)()> functions);

public:
    Controller(DataBaseSelector dbSelector);
    ~Controller();

    void start();

    void walletMenu();
    void movementMenu();
    void reportsMenu();
    void helpMenu();
};

#endif