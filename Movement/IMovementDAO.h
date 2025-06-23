#ifndef IMOVEMENTDAO_H
#define IMOVEMENTDAO_H

#include "Movement.h"
#include <vector>

using namespace std;

class IMovementDAO {
public:
    virtual ~IMovementDAO() = default;

    virtual void addMovement(Movement movement) = 0;
    virtual vector<Movement> getMovementsByWalletId(int walletId) = 0;
    virtual vector<Movement> getAllMovements() = 0;

    virtual int getNextId() = 0;
};

#endif
