#include "moneyManager.h"

MoneyManager::MoneyManager(){
    //TODO make this a constant
    money = 100;
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

void MoneyManager::getMoney(){
    return money;
}