#ifndef MONEYMANAGER_H
#define MONEYMANAGER_H

class MoneyManager{
    private:
        int money;
    
    public:
        MoneyManager();
        void spendMoney(int amount);
        void gainMoney(int amount);
        int getMoney();
};

#endif