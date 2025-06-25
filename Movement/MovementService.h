#ifndef MOVEMENT_SERVICE_H
#define MOVEMENT_SERVICE_H

#include "IMovementDAO.h"
#include "../Oracle/IOracleDAO.h"

#include <memory>
#include "../Wallet/IWalletDAO.h"

class MovementService {
private:
    shared_ptr<IMovementDAO> movementDao;
    shared_ptr<IWalletDAO> walletDao;
    shared_ptr<IOracleDAO> oracleDao;

public:
    MovementService(shared_ptr<IMovementDAO> mDao,
                    shared_ptr<IWalletDAO> wDao,
                    shared_ptr<IOracleDAO> oDao);

    void registerBuy();
    void registerSell();
    void showWalletHistory();
};

#endif