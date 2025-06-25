#include "./Wallet.h"

#include <sstream>

using namespace std;

// Default constructor
Wallet::Wallet() : id(0), ownerName(""), broker("") {}

// Parametrized constructor
Wallet::Wallet(int id, const string& ownerName, const string& broker)
    : id(id), ownerName(ownerName), broker(broker) {}

// Getters
int Wallet::getId() const {
    return id;
}

string Wallet::getOwnerName() const {
    return ownerName;
}

string Wallet::getBroker() const {
    return broker;
}

// Setters
void Wallet::setId(int newId) {
    id = newId;
}

void Wallet::setOwnerName(const string& newOwnerName) {
    ownerName = newOwnerName;
}

void Wallet::setBroker(const string& newBroker) {
    broker = newBroker;
}

// Utility
string Wallet::toString() const {
    ostringstream oss;
    oss << "Wallet ID: " << id
        << " | Owner: " << ownerName
        << " | Broker: " << broker;
    return oss.str();
}
