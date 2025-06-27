#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <vector>
#include <string>

#include "./Oracle/IOracleDAO.h"
#include "./Movement/IMovementDAO.h"
#include "./Wallet/IWalletDAO.h"
#include "./Movement/MovementService.h"
#include "./Report/ReportService.h"
#include "./Wallet/WalletService.h"
#include "./Help/HelpService.h"

#include "./Oracle/OracleDAOMemory.h"
#include "./Movement/MovementDAOMemory.h"
#include "./Wallet/WalletDAOMemory.h"

#ifndef MEMORY_ONLY
#include "Wallet/WalletDAOMariaDB.h"
#include "Movement/MovementDAOMariaDB.h"
#include "Oracle/OracleDAOMariaDB.h"
#endif

using namespace std;

enum class DataBaseSelector {
    MEMORY,
    MARIADB
};

class Controller {
private:
    shared_ptr<IWalletDAO> memoryWalletDAO;
    shared_ptr<IMovementDAO> memoryMovementDAO;

	#ifndef MEMORY_ONLY
    shared_ptr<IWalletDAO> serverWalletDAO;
    shared_ptr<IMovementDAO> serverMovementDAO;
	#endif

    shared_ptr<IOracleDAO> oracleDAO;

    unique_ptr<WalletService> walletService;
    unique_ptr<MovementService> movementService;
    unique_ptr<ReportService> reportService;
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
