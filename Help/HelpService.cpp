#include "HelpService.h"

void HelpService::printHelpText() const {
    std::cout << "\n--- Help: FT Coin Wallet System ---\n\n";
    std::cout << "This program allows you to manage virtual currency wallets,\n"
              << "register transactions, and generate reports.\n"
              << "You can create wallets, add buy/sell movements, and view\n"
              << "detailed summaries of your portfolio.\n\n"
              << "Use the menu options to navigate through the system.\n"
              << "Input the number corresponding to the option and press Enter.\n\n";
}

void HelpService::printCredits() const {
    std::cout << "\n--- Credits ---\n\n";
    std::cout << "FT Coin v1.0\n"
              << "Authors Group B-10: \n"
              << "Leonardo Bonfá Schroeder - 289156\n"
              << "Felipe Amadio Vaccari - 206115\n"
              << "Gabriel Aleksandro De Paula - 198327\n"
              << "Pedro Coelho Terossi - 225883\n"
              << "Copyright (c) 2025\n"
              << "Developed at School of Tecnology UNICAMP\n"
              << "Date: June 2025\n\n";
}
