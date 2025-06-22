#include "HelpService.h"

void HelpService::printHelpText() const {
    std::cout << "\n--- Help: FT_Coin Wallet System ---\n\n";
    std::cout << "This program allows you to manage virtual currency wallets,\n"
              << "register transactions, and generate reports.\n"
              << "You can create wallets, add buy/sell movements, and view\n"
              << "detailed summaries of your portfolio.\n\n"
              << "Use the menu options to navigate through the system.\n"
              << "Input the number corresponding to the option and press Enter.\n"
              << "For any questions, contact support@example.com\n\n";
}

void HelpService::printCredits() const {
    std::cout << "\n--- Credits ---\n\n";
    std::cout << "FT_Coin System v1.0\n"
              << "Authors: Your Team\n"
              << "Copyright (c) 2025\n"
              << "Developed at Your Institution\n"
              << "Date: June 2025\n\n";
}
