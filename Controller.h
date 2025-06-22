#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "WalletService.h"
#include "IWalletDAO.h"
#include <memory>
#include <vector>
#include <string>

using namespace std;

enum class DataBaseSelector {
    MEMORY,
    MARIADB
};

class Controller {
private:
    shared_ptr<IWalletDAO> memoryDBConnection;
    shared_ptr<IWalletDAO> serverDBConnection;
    unique_ptr<WalletService> walletService;

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
