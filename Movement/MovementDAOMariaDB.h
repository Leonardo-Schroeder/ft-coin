#ifndef MOVEMENTDAOMARIADB_H_
#define MOVEMENTDAOMARIADB_H_

#include "./IMovementDAO.h"
#include "../DatabaseConnection.h"

class MovementDAOMariaDB : public IMovementDAO {
private:
    MYSQL* _conn;

public:
    MovementDAOMariaDB();
    virtual ~MovementDAOMariaDB() = default;

    void addMovement(Movement movement) override;
    vector<Movement> getMovementsByWalletId(int walletId) override;
    vector<Movement> getAllMovements() override;
    int getNextId() override;
};

#endif /* MOVEMENTDAOMARIADB_H_ */
