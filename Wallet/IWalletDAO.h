#ifndef IWALLETDAO_H
#define IWALLETDAO_H

#include <vector>
#include "./Wallet.h"

using namespace std;

class IWalletDAO {
public:
    virtual ~IWalletDAO() = default;

    virtual int addWallet(const Wallet& wallet) = 0;
    virtual Wallet* getWalletById(int id) = 0;
    virtual vector<Wallet> getAllWallets() = 0;
    virtual bool updateWallet(const Wallet& wallet) = 0;
    virtual bool deleteWallet(int id) = 0;
};

#endif
