#pragma once

#include "../IWalletDAO.h"
#include "../Movement/IMovementDAO.h"
#include "../Oracle/IOracleDAO.h"
#include <memory>

class ReportService {
private:
    std::shared_ptr<IWalletDAO> walletDao;
    std::shared_ptr<IMovementDAO> movementDao;
    std::shared_ptr<IOracleDAO> oracleDao;

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
