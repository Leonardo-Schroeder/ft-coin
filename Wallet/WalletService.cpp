#include "./WalletService.h"

#include <iostream>

using namespace std;

WalletService::WalletService(shared_ptr<IWalletDAO> dao) : dao(dao) {}

void WalletService::createWallet() {
    string name, broker;

    cout << "\n--- Create Wallet ---\n";

    do {
        cout << "Enter owner name: ";
        getline(cin, name);
        if (name.empty())
            cout << "Error: Owner name cannot be empty.\n\n";
    } while(name.empty());

    do {
        cout << "Enter broker: ";
        getline(cin, broker);
        if(broker.empty())
            cout << "Error: Broker name cannot be empty.\n\n";
    } while(broker.empty());

    Wallet newWallet(0, name, broker); //ID come from DAO

    int generatedId = dao->addWallet(newWallet);

    cout << "Wallet successfully created with ID: " << generatedId << "!\n\n";
}

// Function for depuration
void WalletService::listWallets() {
    cout << "\n--- List of Wallets ---\n";
    for (const auto& w : dao->getAllWallets()) {
        cout << w.toString() << endl ;
    }
}

void WalletService::findWalletById() {
    int id;
    cout << "\n--- Search Wallet ---\nEnter wallet ID: ";
    cin >> id;

    Wallet* w = dao->getWalletById(id);
    if (w) {
        cout << "Found: " << w->toString() << endl << endl;
    } else {
        cout << "Wallet not found.\n\n";
    }
}

void WalletService::updateWallet() {
    int id;
    string name, broker;

    cout << "\n--- Update Wallet ---\nEnter wallet ID to update: ";
    cin >> id;
    cin.ignore(); // flush newline

    Wallet* existing = dao->getWalletById(id);
    if (!existing) {
        cout << "Wallet not found.\n";
        return;
    }

    cout << "Enter new owner name: ";
    getline(cin, name);
    cout << "Enter new broker: ";
    getline(cin, broker);

    Wallet updated(id, name, broker);
    if (dao->updateWallet(updated)) {
        cout << "Wallet updated successfully.\n\n";
    } else {
        cout << "Update failed.\n\n";
    }
}

void WalletService::deleteWallet() {
    int id;
    cout << "\n--- Delete Wallet ---\nEnter wallet ID to delete: ";
    cin >> id;

    if (dao->deleteWallet(id)) {
        cout << "Wallet deleted.\n\n";
    } else {
        cout << "Wallet not found.\n\n";
    }
}
