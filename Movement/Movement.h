#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <string>

using namespace std;

class Movement {
private:
    int movementId;
    int walletId;
    string date;
    char type; // 'C' for buy(compra), 'V' for sell (venda)
    double quantity;

public:
    Movement();
    Movement(int movementId, int walletId, const string& date, char type, double quantity);

    int getMovementId() const;
    int getWalletId() const;
    string getDate() const;
    char getType() const;
    double getQuantity() const;

    void setMovementId(int id);
    void setWalletId(int id);
    void setDate(const string& newDate);
    void setType(char newType);
    void setQuantity(double newQuantity);

    string toString() const;
};

#endif
