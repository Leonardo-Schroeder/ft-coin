#include "OracleDAOMemory.h"
#include <cstdlib>  // rand()
#include <ctime>    // time()
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

void OracleDAOMemory::addQuote(const Oracle& quote) {
    quotes.push_back(quote);
}

Oracle* OracleDAOMemory::getQuoteByDate(const string& date) {
    for (auto& q : quotes) {
        if (q.getDate() == date)
            return &q;
    }
    return nullptr;
}

vector<Oracle> OracleDAOMemory::getAllQuotes() {
    return quotes;
}

void OracleDAOMemory::populateMockData() {
    quotes.clear();

    // Seed para valores pseudoaleatórios (opcional)
    srand(static_cast<unsigned int>(time(nullptr)));

    double price = 100.0;

    for (int day = 1; day <= 30; ++day) {
        ostringstream oss;
        oss << "2025-06-" << setw(2) << setfill('0') << day;
        string date = oss.str();

        double delta = (rand() % 2001 - 1000) / 100.0; // -10.00 a +10.00
        price += delta;
        if (price < 1.0) price = 1.0;

        quotes.emplace_back(date, price);
    }

    // cout << "[OracleDAO] Mock data populated with 30 quotes.\n"; Line for debug
}
