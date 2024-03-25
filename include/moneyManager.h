#ifndef MONEYMANAGER_H
#define MONEYMANAGER_H

class MoneyManager{
    private:
        int money;
    
    public:
        MoneyManager();

        // Decreases money by amount.
        // Returns true if transaction is successful (sufficient funds), false otherwise.
        bool spendMoney(int amount);

        void gainMoney(int amount);
        int getMoney() const;
};

#endif