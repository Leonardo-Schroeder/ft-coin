#pragma once

#include "../Movement/IMovementDAO.h"
#include "../Oracle/IOracleDAO.h"
#include <memory>
#include "../Wallet/IWalletDAO.h"

class ReportService {
private:
    std::shared_ptr<IWalletDAO> walletDao;
    std::shared_ptr<IMovementDAO> movementDao;
    std::shared_ptr<IOracleDAO> oracleDao;
    const std::string COR_VERDE = "\033[1;32m";
    const std::string COR_VERMELHA = "\033[1;31m";
    const std::string RESET_COR = "\033[0m";
public:
    ReportService(std::shared_ptr<IWalletDAO> wDao,
                  std::shared_ptr<IMovementDAO> mDao,
                  std::shared_ptr<IOracleDAO> oDao);

    void listWalletsById();
    void listWalletsByName();
    void showWalletBalance();
    void showWalletHistory();
    void showWalletProfitOrLoss();
};
