#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>

enum class DataBaseSelector { MEMORY, MARIADB };

class Controller
{
public:
    Controller(DataBaseSelector dbSelector = DataBaseSelector::MEMORY);
    ~Controller();

    void start(); // Starts the main menu

private:
    // Future database connection placeholders
    void* memoryDBConnection;
    void* serverDBConnection;

    // Menu navigation
    void launchActions(std::string title, std::vector<std::string> menuItems, std::vector<void (Controller::*)()> functions);

    // Main menu actions
    void walletMenu();
    void movementMenu();
    void reportsMenu();
    void helpMenu();
};

#endif // CONTROLLER_H
