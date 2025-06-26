#ifndef WALLETDAOMARIADB_H_
#define WALLETDAOMARIADB_H_

#include "IWalletDAO.h"
#include "../DatabaseConnection.h"

class WalletDAOMariaDB : public IWalletDAO {
private:
    MYSQL* _conn;

public:
    WalletDAOMariaDB();
    virtual ~WalletDAOMariaDB() = default;

    int addWallet(const Wallet& wallet) override;
    Wallet* getWalletById(int id) override;
    vector<Wallet> getAllWallets() override;
    bool updateWallet(const Wallet& wallet) override;
    bool deleteWallet(int id) override;
};

#endif /* WALLETDAOMARIADB_H_ */
