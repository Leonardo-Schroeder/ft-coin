#include "./WalletDAOMemory.h"

WalletDAOMemory::WalletDAOMemory() : nextId(1) {}

int WalletDAOMemory::addWallet(const Wallet& wallet) {
	Wallet walletToAdd = wallet;
	walletToAdd.setId(nextId);
	wallets.push_back(walletToAdd);
	return nextId++;
}

Wallet* WalletDAOMemory::getWalletById(int id) {
    for (auto& wallet : wallets) {
        if (wallet.getId() == id) {
            return &wallet;
        }
    }
    return nullptr;
}

vector<Wallet> WalletDAOMemory::getAllWallets() {
    return wallets;
}

bool WalletDAOMemory::updateWallet(const Wallet& wallet) {
    for (auto& w : wallets) {
        if (w.getId() == wallet.getId()) {
            w.setOwnerName(wallet.getOwnerName());
            w.setBroker(wallet.getBroker());
            return true;
        }
    }
    return false;
}

bool WalletDAOMemory::deleteWallet(int id) {
    for (auto it = wallets.begin(); it != wallets.end(); ++it) {
        if (it->getId() == id) {
            wallets.erase(it);
            return true;
        }
    }
    return false;
}
