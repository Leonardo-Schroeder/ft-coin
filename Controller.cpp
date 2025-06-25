#include "Controller.h"
#include "Menu.h"
#include <iostream>
#include "./Oracle/OracleDAOMemory.h"
#include "Wallet/WalletDAOMemory.h"

using namespace std;

Controller::Controller(DataBaseSelector dbSelector)
{
    switch (dbSelector)
    {
        case DataBaseSelector::MEMORY:
            memoryDBConnection = make_shared<WalletDAOMemory>();
            movementDBConnection = make_shared<MovementDAOMemory>();
            
            // Create and populate oracle
            oracleDAO = make_shared<OracleDAOMemory>();
			oracleDAO->populateMockData();
			
			walletService = make_unique<WalletService>(memoryDBConnection);
            movementService = make_unique<MovementService>(movementDBConnection, memoryDBConnection, oracleDAO);
			reportService = make_unique<ReportService>(memoryDBConnection, movementDBConnection, oracleDAO);

            break;

        case DataBaseSelector::MARIADB:
            // Future implementation
            break;

        default:
            throw invalid_argument("Unknown database option.");
    }
}

Controller::~Controller() {}

void Controller::start()
{
    vector<string> menuItems = {
        "Wallet",
        "Movement",
        "Reports",
        "Help",
        "Exit"
    };

    vector<void (Controller::*)()> functions = {
        &Controller::walletMenu,
        &Controller::movementMenu,
        &Controller::reportsMenu,
        &Controller::helpMenu
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
        }
    }
}

void Controller::walletMenu()
{
    vector<string> menuItems = {
        "Create Wallet",
        //"List Wallets",
        "Search Wallet by ID",
        "Edit Wallet",
        "Delete Wallet",
        "Back"
    };

    vector<void (WalletService::*)()> actions = {
        &WalletService::createWallet,
        //&WalletService::listWallets,
        &WalletService::findWalletById,
        &WalletService::updateWallet,
        &WalletService::deleteWallet
    };

    Menu menu(menuItems, "Wallet Menu", "Choose an option: ");
    menu.setSymbol(">>");

    while (int choice = menu.getChoice()) {
        if (choice >= 1 && choice <= 5)
            (walletService.get()->*actions.at(choice - 1))();
    }
}

void Controller::movementMenu()
{
    vector<string> menuItems = {
        "Register Buy",
        "Register Sell",
        //"Show Wallet Movement History", Function for Debug
        "Back"
    };

    vector<void (MovementService::*)()> actions = {
        &MovementService::registerBuy,
        &MovementService::registerSell,
        //&MovementService::showWalletHistory Function for Debug
    };

    Menu menu(menuItems, "Movement Menu", "Select an option: ");
    menu.setSymbol(">>");

    while (int choice = menu.getChoice()) {
        if (choice >= 1 && choice <= 3)
            (movementService.get()->*actions.at(choice - 1))();
    }
}

void Controller::reportsMenu()
{
    vector<string> menuItems = {
        "List Wallets by ID",
        "List Wallets by Name",
        "Show Wallet Balance",
        "Show Wallet History",
        "Show Wallet Profit/Loss",
        "Back"
    };

    vector<void (ReportService::*)()> actions = {
        &ReportService::listWalletsById,
        &ReportService::listWalletsByName,
        &ReportService::showWalletBalance,
        &ReportService::showWalletHistory,
        &ReportService::showWalletProfitOrLoss
    };

    Menu menu(menuItems, "Reports Menu", "Select an option: ");
    menu.setSymbol(">>");

    while (int choice = menu.getChoice()) {
        if (choice >= 1 && choice <= 5)
            (reportService.get()->*actions.at(choice - 1))();
    }
}

void Controller::helpMenu()
{
    std::vector<std::string> menuItems = {
        "Help Text",
        "Credits",
        "Back"
    };

    Menu menu(menuItems, "Help Menu", "Choose an option: ");
    menu.setSymbol(">>");

    while (int choice = menu.getChoice())
    {
        switch (choice)
        {
            case 1:
                helpService.printHelpText();
                break;
            case 2:
                helpService.printCredits();
                break;
            case 3:
                return;
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    }
}