#ifndef MOVEMENT_DAO_MEMORY_H
#define MOVEMENT_DAO_MEMORY_H

#include "IMovementDAO.h"
#include <vector>

class MovementDAOMemory : public IMovementDAO {
private:
    vector<Movement> movements;
    int nextId = 1; // ID incremental

public:
    void addMovement(Movement movement) override;
    vector<Movement> getMovementsByWalletId(int walletId) override;
    vector<Movement> getAllMovements() override;
    int getNextId() override;
};

#endif
