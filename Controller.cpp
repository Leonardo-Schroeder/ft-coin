#include "Controller.h"
#include "Menu.h"
#include <iostream>

using namespace std;

Controller::Controller(DataBaseSelector dbSelector)
{
    // Placeholder for future database setup
    memoryDBConnection = nullptr;
    serverDBConnection = nullptr;

    switch (dbSelector)
    {
        case DataBaseSelector::MEMORY:
            // Setup in-memory database connection (future implementation)
            break;

        case DataBaseSelector::MARIADB:
            // Setup MariaDB database connection (future implementation)
            break;

        default:
            throw invalid_argument("Unknown database option selected.");
    }
}

Controller::~Controller()
{
    // Future cleanup of database resources if needed
    memoryDBConnection = nullptr;
    serverDBConnection = nullptr;
}

void Controller::start()
{
    vector<string> menuItems = {
        "Wallet",
        "Movement",
        "Reports",
        "Help",
        "Exit"
    };

    // Note: No need to bind an action for "Exit" – menu.getChoice() will return 0 on exit
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
    try
    {
        Menu menu(menuItems, title, "Your choice: ");
        menu.setSymbol("*");

        while (int choice = menu.getChoice())
        {
            (this->*functions.at(choice - 1))();
        }
    }
    catch (const exception& e)
    {
        cout << "Unexpected error when launching menu: " << e.what() << endl;
    }
}

// Placeholder implementations for each submenu

void Controller::walletMenu()
{
    cout << "\n[Wallet Menu] – Feature under construction.\n\n";
}

void Controller::movementMenu()
{
    cout << "\n[Movement Menu] – Feature under construction.\n\n";
}

void Controller::reportsMenu()
{
    cout << "\n[Reports Menu] – Feature under construction.\n\n";
}

void Controller::helpMenu()
{
    cout << "\n[Help Menu] – Feature under construction.\n\n";
}
