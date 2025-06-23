#include "MovementDAOMemory.h"

void MovementDAOMemory::addMovement(Movement movement) {
    movements.push_back(movement);
}

vector<Movement> MovementDAOMemory::getMovementsByWalletId(int walletId) {
    vector<Movement> result;
    for (const auto& m : movements) {
        if (m.getWalletId() == walletId)
            result.push_back(m);
    }
    return result;
}

vector<Movement> MovementDAOMemory::getAllMovements() {
    return movements;
}

int MovementDAOMemory::getNextId() {
    return nextId++;
}
