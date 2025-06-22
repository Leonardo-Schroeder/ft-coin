#include <iostream>
#include <memory>
#include <exception>

#include "Controller.h"

using namespace std;

// Display welcome message
void welcome()
{
    cout << "==========================================" << endl;
    cout << " Welcome to the FT Coin " << endl;
    cout << "==========================================" << endl;
    cout << endl;
}

// Display goodbye message
void goodbye()
{
    cout << "\nThanks for using the system!" << endl;
    cout << "Exiting now...\n" << endl;
}

int main()
{
    welcome();

    try
    {
        // Using MEMORY as the default for now — MariaDB can be added later
        unique_ptr<Controller> controller = make_unique<Controller>(DataBaseSelector::MEMORY);
        controller->start();
    }
    catch (const exception& e)
    {
        cerr << "Unexpected error. Program aborted.\nReason: " << e.what() << endl;
        return 1;
    }
    
    goodbye();
    return 0;
}
