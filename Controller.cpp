#include "Controller.h"
#include "Menu.h"
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

Controller::Controller(DataBaseSelector dbSelector)
{
    memoryWalletDAO = make_shared<WalletDAOMemory>();
    memoryMovementDAO = make_shared<MovementDAOMemory>();

	#ifndef MEMORY_ONLY
    serverWalletDAO = make_shared<WalletDAOMariaDB>();
    serverMovementDAO = make_shared<MovementDAOMariaDB>();
    #endif

    shared_ptr<IWalletDAO> chosenWalletDAO;
    shared_ptr<IMovementDAO> chosenMovementDAO;

    switch (dbSelector)
    {
        case DataBaseSelector::MEMORY:
            chosenWalletDAO = memoryWalletDAO;
            chosenMovementDAO = memoryMovementDAO;
            oracleDAO = make_shared<OracleDAOMemory>();
            oracleDAO->populateMockData();
            //cout << "Controller started with database in memory." << endl;
            break;

		#ifndef MEMORY_ONLY
        	case DataBaseSelector::MARIADB:
        		chosenWalletDAO = serverWalletDAO;
        		chosenMovementDAO = serverMovementDAO;
        		oracleDAO = make_shared<OracleDAOMariaDB>();
        		cout << "Controller started with database in MariaDB." << endl;
        		break;
        #endif

        default:
            throw invalid_argument("Problem with Database");
    }

    walletService.reset(new WalletService(chosenWalletDAO));
    movementService.reset(new MovementService(chosenMovementDAO, chosenWalletDAO, oracleDAO));
    reportService.reset(new ReportService(chosenWalletDAO, chosenMovementDAO, oracleDAO));
}

Controller::~Controller() {}

void Controller::start()
{
    vector<string> menuItems = { "Wallet", "Movement", "Reports", "Help", "Exit" };
    vector<void (Controller::*)()> functions = {
        &Controller::walletMenu, &Controller::movementMenu, &Controller::reportsMenu, &Controller::helpMenu
    };
    launchActions("Main Menu", menuItems, functions);
}

void Controller::launchActions(string title, vector<string> menuItems, vector<void (Controller::*)()> functions)
{
    Menu menu(menuItems, title, "Your choice: ");
    menu.setSymbol("*");

    while (int choice = menu.getChoice()) {
        if (choice > 0 && choice <= static_cast<int>(functions.size())) {
            (this->*functions.at(choice - 1))();
        } else {
            break;
        }
    }
}

void Controller::walletMenu()
{
    vector<string> menuItems = { "Create Wallet", "Search Wallet by ID", "Edit Wallet", "Delete Wallet", "Back" };
    vector<void (WalletService::*)()> actions = {
        &WalletService::createWallet, &WalletService::findWalletById, &WalletService::updateWallet, &WalletService::deleteWallet
    };
    Menu menu(menuItems, "Wallet Menu", "Choose an option: ");
    menu.setSymbol(">>");

    while (int choice = menu.getChoice()) {
        if (choice >= 1 && choice <= 4)
            (walletService.get()->*actions.at(choice - 1))();
        else
            break;
    }
}

void Controller::movementMenu()
{
    vector<string> menuItems = { "Register Buy", "Register Sell", "Back" };
    vector<void (MovementService::*)()> actions = { &MovementService::registerBuy, &MovementService::registerSell };
    Menu menu(menuItems, "Movement Menu", "Select an option: ");
    menu.setSymbol(">>");

    while (int choice = menu.getChoice()) {
        if (choice >= 1 && choice <= 2)
            (movementService.get()->*actions.at(choice - 1))();
        else
            break;
    }
}

void Controller::reportsMenu()
{
    vector<string> menuItems = {
        "List Wallets by ID", "List Wallets by Name", "Show Wallet Balance",
        "Show Wallet History", "Show Wallet Profit/Loss", "Back"
    };
    vector<void (ReportService::*)()> actions = {
        &ReportService::listWalletsById, &ReportService::listWalletsByName, &ReportService::showWalletBalance,
        &ReportService::showWalletHistory, &ReportService::showWalletProfitOrLoss
    };
    Menu menu(menuItems, "Reports Menu", "Select an option: ");
    menu.setSymbol(">>");

    while (int choice = menu.getChoice()) {
        if (choice >= 1 && choice <= 5)
            (reportService.get()->*actions.at(choice - 1))();
        else
            break;
    }
}

void Controller::helpMenu()
{
    vector<string> menuItems = { "Help Text", "Credits", "Back" };
    Menu menu(menuItems, "Help Menu", "Choose an option: ");
    menu.setSymbol(">>");

    while (int choice = menu.getChoice())
    {
        switch (choice) {
            case 1: helpService.printHelpText(); break;
            case 2: helpService.printCredits(); break;
            default: return;
        }
    }
}
