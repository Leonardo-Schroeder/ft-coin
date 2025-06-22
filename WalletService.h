#ifndef WALLET_SERVICE_H
#define WALLET_SERVICE_H

#include "Wallet.h"
#include "IWalletDAO.h"
#include <memory>
#include <vector>

using namespace std;

class WalletService {
private:
    shared_ptr<IWalletDAO> dao;

public:
    WalletService(shared_ptr<IWalletDAO> dao);

    void createWallet();
    void listWallets();
    void findWalletById();
    void updateWallet();
    void deleteWallet();
};

#endif 
