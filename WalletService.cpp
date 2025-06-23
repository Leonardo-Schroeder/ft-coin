#include "WalletService.h"
#include <iostream>

using namespace std;

WalletService::WalletService(shared_ptr<IWalletDAO> dao) : dao(dao) {}

void WalletService::createWallet() {
    int id;
    string name, broker;

    cout << "\n--- Create Wallet ---\n";
    
    // Validation ID
    bool validId = false;
    while (!validId) {
		string idInput;
		
        cout << "Enter wallet ID: ";
        getline(cin, idInput);
        
        //  only digits
        bool isNumeric = true;
        for (char c : idInput) {
            if (!isdigit(c)) {
                isNumeric = false;
                break;
            }
        }
        
        if (!isNumeric) {
            cout << "Error: ID must be a numeric value.\n\n";
            continue;
        }
        
        // Int validation
        try {
            id = stoi(idInput);
        } catch (...) {
            cout << "Error: Invalid ID format.\n\n";
            continue;
        }
        
        // ID alredy exist
        if (dao->getWalletById(id) != nullptr) {
            cout << "Error: A wallet with this ID already exists.\n\n";
        } else {
            validId = true;
        }
    }
    
    // Validation Name
	do {
    	cout << "Enter owner name: ";
    	getline(cin, name);

    	if (name.empty()) 
        	cout << "Error: Owner name cannot be empty.\n\n";
    } while(name.empty());

    // Validation Broker name
	do {
    	cout << "Enter broker: ";
    	getline(cin, broker);

     	if(broker.empty()) 
        	cout << "Error: Broker name cannot be empty.\n\n";
    } while(broker.empty());

    dao->addWallet(Wallet(id, name, broker));
    cout << "Wallet successfully created!\n\n";
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
