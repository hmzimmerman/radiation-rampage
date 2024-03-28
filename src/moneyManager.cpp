#include "moneyManager.h"
#include "constants.h"

MoneyManager::MoneyManager(){
    using namespace moneyManager;
    money = moneyManager::startAmount;
}

bool MoneyManager::spendMoney(int amount){
    if ((money - amount) >= 0){
        money-=amount;
        return true;
    }else{
        return false;
    }
}

void MoneyManager::gainMoney(int amount){
    money+=amount;
}

int MoneyManager::getMoney() const{
    return money;
}