#include "Movement.h"
#include <sstream>

Movement::Movement() : movementId(0), walletId(0), date(""), type('C'), quantity(0.0) {}

Movement::Movement(int movementId, int walletId, const string& date, char type, double quantity)
    : movementId(movementId), walletId(walletId), date(date), type(type), quantity(quantity) {}

int Movement::getMovementId() const { return movementId; }
int Movement::getWalletId() const { return walletId; }
string Movement::getDate() const { return date; }
char Movement::getType() const { return type; }
double Movement::getQuantity() const { return quantity; }

void Movement::setMovementId(int id) { movementId = id; }
void Movement::setWalletId(int id) { walletId = id; }
void Movement::setDate(const string& newDate) { date = newDate; }
void Movement::setType(char newType) { type = newType; }
void Movement::setQuantity(double newQuantity) { quantity = newQuantity; }

string Movement::toString() const {
    ostringstream oss;
    oss << "ID: " << movementId
        << " | Wallet ID: " << walletId
        << " | Date: " << date
        << " | Type: " << (type == 'C' ? "C" : "V")
        << " | Quantity: " << quantity;
    return oss.str();
}
