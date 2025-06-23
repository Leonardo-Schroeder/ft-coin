#ifndef WALLET_DAO_MEMORY_H
#define WALLET_DAO_MEMORY_H

#include "IWalletDAO.h"

class WalletDAOMemory : public IWalletDAO {
private:
    vector<Wallet> wallets;

public:
    void addWallet(const Wallet& wallet) override;
    Wallet* getWalletById(int id) override;
    vector<Wallet> getAllWallets() override;
    bool updateWallet(const Wallet& wallet) override;
    bool deleteWallet(int id) override;
};

#endif

