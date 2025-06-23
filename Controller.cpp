#include "Controller.h"
#include "Menu.h"
#include <iostream>
#include "WalletDAOMemory.h"
#include "./Oracle/OracleDAOMemory.h"

using namespace std;

Controller::Controller(DataBaseSelector dbSelector)
{
    switch (dbSelector)
    {
        case DataBaseSelector::MEMORY:
            memoryDBConnection = make_shared<WalletDAOMemory>();
            walletService = make_unique<WalletService>(memoryDBConnection);
            
            // Create and populate oracle
            oracleDAO = make_shared<OracleDAOMemory>();
			oracleDAO->populateMockData();

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

void Controller::movementMenu() {
    cout << "\n[Movement Menu] – Under construction.\n";
}

void Controller::reportsMenu() {
    cout << "\n[Reports Menu] – Under construction.\n";
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