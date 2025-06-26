#include "ReportService.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

ReportService::ReportService(shared_ptr<IWalletDAO> wDao,
                             shared_ptr<IMovementDAO> mDao,
                             shared_ptr<IOracleDAO> oDao)
    : walletDao(wDao), movementDao(mDao), oracleDao(oDao) {}

void ReportService::listWalletsById() {
    auto wallets = walletDao->getAllWallets();
    
     cout << "\n--- Wallets Ordered by ID ---\n";

     if (wallets.empty()) {
        cout << "\nNo wallets found.\n\n";
        return;
    }
    
    sort(wallets.begin(), wallets.end(), [](const Wallet& a, const Wallet& b) {
        return a.getId() < b.getId();
    });

    for (const auto& w : wallets) {
        cout << "ID: " << w.getId() << " | Name: " << w.getOwnerName() << " | Broker: " << w.getBroker() << endl;
    }
	cout << endl;
}

void ReportService::listWalletsByName() {
    auto wallets = walletDao->getAllWallets();
    
     cout << "\n--- Wallets Ordered by Name ---\n";

     if (wallets.empty()) {
        cout << "\nNo wallets found.\n\n";
        return;
    }
    
    sort(wallets.begin(), wallets.end(), [](const Wallet& a, const Wallet& b) {
        return a.getOwnerName() < b.getOwnerName();
    });

    for (const auto& w : wallets) {
        cout << "ID: " << w.getId() << " | Name: " << w.getOwnerName() << " | Broker: " << w.getBroker() << endl;
    }
	cout << endl;
}

void ReportService::showWalletBalance() {
    int walletId;
    cout << "Enter Wallet ID: ";
    cin >> walletId;

    double coinBalance = 0.0;
    auto movements = movementDao->getMovementsByWalletId(walletId);

    for (const auto& m : movements) {
        if (m.getType() == 'C') coinBalance += m.getQuantity();
        if (m.getType() == 'V') coinBalance -= m.getQuantity();
    }

    // Last cotation
    auto quotes = oracleDao->getAllQuotes();
    if (quotes.empty()) {
        cout << "No quotes available in oracle.\n";
        return;
    }

    const Oracle& latestQuote = quotes.back();
    double coinPrice = latestQuote.getPrice();
    double totalValue = coinBalance * coinPrice;

    cout << fixed << setprecision(2);
    cout << "\n--- Wallet Balance ---\n";
    cout << "Coin balance: " << coinBalance << " coins\n";
    cout << "Latest price: R$ " << coinPrice << " per coin\n";
    cout << "Total balance: R$ " << totalValue << endl << endl;
}

void ReportService::showWalletHistory() {
    int walletId;
    cout << "Enter Wallet ID: ";
    cin >> walletId;

    auto movements = movementDao->getMovementsByWalletId(walletId);

    if (movements.empty()) {
        cout << "No movements found for this wallet.\n";
        return;
    }

    cout << "\n--- Movement History for Wallet ID " << walletId << " ---\n";
    for (const auto& m : movements) {
        string typeStr = m.getType() == 'C' ? "Buy " : "Sell";
        cout << "ID: " << m.getMovementId()
             << " | Date: " << m.getDate()
             << " | Type: " << typeStr
             << " | Qty: " << m.getQuantity()
             << endl << endl;
    }
}

void ReportService::showWalletProfitOrLoss() {
    int walletId;
    cout << "Enter Wallet ID: ";
    cin >> walletId;

    auto movements = movementDao->getMovementsByWalletId(walletId);
    if (movements.empty()) {
        cout << "No movements found for this wallet.\n";
        return;
    }

    double totalBuy = 0.0;
    double totalSell = 0.0;
    double coinBalance = 0.0;

    for (const auto& m : movements) {
    	Oracle* quotePtr = oracleDao->getQuoteByDate(m.getDate());

		if (!quotePtr) {
    		cout << "Warning: No quote for date " << m.getDate() << ", skipping.\n";
    		continue;
		}

		double quote = quotePtr->getPrice();
        double value = m.getQuantity() * quote;

        if (m.getType() == 'C') {
            totalBuy += value;
            coinBalance += m.getQuantity();
        } else if (m.getType() == 'V') {
            totalSell += value;
            coinBalance -= m.getQuantity();
        }
    }

    // Last Cotation
    auto quotes = oracleDao->getAllQuotes();
    double currentValue = 0.0;
    if (!quotes.empty()) {
        currentValue = coinBalance * quotes.back().getPrice();
    }

    double result = (totalSell + currentValue) - totalBuy;

    cout << fixed << setprecision(2);
    cout << "\n--- Profit/Loss for Wallet ID " << walletId << " ---\n";
    cout << "Total Bought: R$ " << totalBuy << endl;
    cout << "Total Sold: R$ " << totalSell << endl;
    cout << "Current Coins Value (not sold): R$ " << currentValue << endl;

    if (result > 0)
        cout << "🔼 Profit: R$ " << COR_VERDE << result << RESET_COR << endl << endl;
    else if (result < 0)
        cout << "🔽 Loss: R$ -" << COR_VERMELHA << (result * -1) << RESET_COR << endl << endl;
    else
        cout << "No profit or loss (break-even).\n" << endl;
}

