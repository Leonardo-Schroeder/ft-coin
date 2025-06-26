#include "MovementService.h"
#include <iostream>
#include <limits>

using namespace std;

MovementService::MovementService(shared_ptr<IMovementDAO> mDao,
                                 shared_ptr<IWalletDAO> wDao,
                                 shared_ptr<IOracleDAO> oDao)
    : movementDao(mDao), walletDao(wDao), oracleDao(oDao) {}

void MovementService::registerBuy() {
    int walletId;
    string date;
    double quantity;

    cout << "\n--- Register Buy ---\n";
    cout << "Enter wallet ID: ";
    cin >> walletId;

    if (!walletDao->getWalletById(walletId)) {
        cout << "Wallet not found.\n";
        return;
    }

    cout << "Enter date (YYYY-MM-DD): ";
    cin >> date;

    if (!oracleDao->getQuoteByDate(date)) {
        cout << "No quote available for that date.\n";
        return;
    }

    cout << "Enter quantity: ";
    cin >> quantity;

    if (quantity <= 0) {
        cout << "Quantity must be positive.\n";
        return;
    }

    int id = movementDao->getNextId();
    Movement m(id, walletId, date, 'C', quantity);
    movementDao->addMovement(m);

    cout << "Buy registered successfully.\n";
}

void MovementService::registerSell() {
    int walletId;
    string date;
    double quantity;

    cout << "\n--- Register Sell ---\n";
    cout << "Enter wallet ID: ";
    cin >> walletId;

    if (!walletDao->getWalletById(walletId)) {
        cout << "Wallet not found.\n";
        return;
    }

    cout << "Enter date (YYYY-MM-DD): ";
    cin >> date;

    if (!oracleDao->getQuoteByDate(date)) {
        cout << "No quote available for that date.\n";
        return;
    }

    cout << "Enter quantity: ";
    cin >> quantity;

    if (quantity <= 0) {
        cout << "Quantity must be positive.\n";
        return;
    }

    // Validation
    vector<Movement> history = movementDao->getMovementsByWalletId(walletId);
	double saldo = 0.0;

	for (const auto& m : history) {
    	if (m.getDate() <= date) {
        	if (m.getType() == 'C') saldo += m.getQuantity();
        	else if (m.getType() == 'V') saldo -= m.getQuantity();
    	}
	}

    if (quantity > saldo) {
        cout << "Insufficient balance. You only have " << saldo << " coins.\n\n";
        return;
    }

    int id = movementDao->getNextId();
    Movement m(id, walletId, date, 'V', quantity);
    movementDao->addMovement(m);

    cout << "Sell registered successfully.\n\n";
}

void MovementService::showWalletHistory() {
    int walletId;

    cout << "\n--- Wallet Movement History ---\n";
    cout << "Enter wallet ID: ";
    cin >> walletId;

    if (!walletDao->getWalletById(walletId)) {
        cout << "Wallet not found.\n";
        return;
    }

    vector<Movement> list = movementDao->getMovementsByWalletId(walletId);

    if (list.empty()) {
        cout << "No movements found.\n";
        return;
    }

    for (const auto& m : list) {
        cout << m.toString() << "\n";
    }
}
