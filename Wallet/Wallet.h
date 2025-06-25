#ifndef WALLET_H
#define WALLET_H

#include <string>

using namespace std;

class Wallet {
private:
    int id;
    string ownerName;
    string broker;

public:
    // Constructors
    Wallet();
    Wallet(int id, const string& ownerName, const string& broker);

    // Getters
    int getId() const;
    string getOwnerName() const;
    string getBroker() const;

    // Setters
    void setId(int newId);
    void setOwnerName(const string& newOwnerName);
    void setBroker(const string& newBroker);

    // Utilities
    string toString() const;
};

#endif