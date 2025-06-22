#include "WalletService.h"
#include <iostream>

using namespace std;

WalletService::WalletService(shared_ptr<IWalletDAO> dao) : dao(dao) {}

void WalletService::createWallet() {
    int id;
    string name, broker;

    cout << "\n--- Create Wallet ---\n";
    cout << "Enter wallet ID: ";
    cin >> id;
    cin.ignore(); // flush newline
    cout << "Enter owner name: ";
    getline(cin, name);
    cout << "Enter broker: ";
    getline(cin, broker);

    dao->addWallet(Wallet(id, name, broker));
    cout << "Wallet successfully created!\n";
}

void WalletService::listWallets() {
    cout << "\n--- List of Wallets ---\n";
    for (const auto& w : dao->getAllWallets()) {
        cout << w.toString() << endl;
    }
}

void WalletService::findWalletById() {
    int id;
    cout << "\n--- Search Wallet ---\nEnter wallet ID: ";
    cin >> id;

    Wallet* w = dao->getWalletById(id);
    if (w) {
        cout << "Found: " << w->toString() << endl;
    } else {
        cout << "Wallet not found.\n";
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
        cout << "Wallet updated successfully.\n";
    } else {
        cout << "Update failed.\n";
    }
}

void WalletService::deleteWallet() {
    int id;
    cout << "\n--- Delete Wallet ---\nEnter wallet ID to delete: ";
    cin >> id;

    if (dao->deleteWallet(id)) {
        cout << "Wallet deleted.\n";
    } else {
        cout << "Wallet not found.\n";
    }
}
