#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Account {
private:
    int accountNumber;
    string name;
    double balance;

public:
    Account(int accNum, string accName, double initialBalance)
        : accountNumber(accNum), name(accName), balance(initialBalance) {}

    int getAccountNumber() const {
        return accountNumber;
    }

    string getName() const {
        return name;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. New balance: $" << balance << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: $" << balance << endl;
        } else {
            cout << "Invalid or insufficient funds for withdrawal!" << endl;
        }
    }

    void transfer(Account &toAccount, double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            toAccount.deposit(amount);
            cout << "Transfer successful! New balance: $" << balance << endl;
        } else {
            cout << "Transfer failed. Check the amount or balance." << endl;
        }
    }
};

class BankSystem {
private:
    vector<Account> accounts;

public:
    void createAccount() {
        int accountNumber;
        string name;
        double initialBalance;

        cout << "Enter account number: ";
        cin >> accountNumber;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter initial balance: ";
        cin >> initialBalance;

        accounts.emplace_back(accountNumber, name, initialBalance);
        cout << "Account created successfully!" << endl;
    }

    Account* findAccount(int accountNumber) {
        for (auto &account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }

    void performTransaction() {
        int accountNumber;
        cout << "Enter account number: ";
        cin >> accountNumber;

        Account* account = findAccount(accountNumber);
        if (account == nullptr) {
            cout << "Account not found!" << endl;
            return;
        }

        int choice;
        cout << "1. Check Balance\n2. Deposit\n3. Withdraw\n4. Transfer\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Current balance: $" << account->getBalance() << endl;
                break;
            case 2: {
                double amount;
                cout << "Enter deposit amount: ";
                cin >> amount;
                account->deposit(amount);
                break;
            }
            case 3: {
                double amount;
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                account->withdraw(amount);
                break;
            }
            case 4: {
                int toAccountNumber;
                double amount;
                cout << "Enter recipient account number: ";
                cin >> toAccountNumber;
                cout << "Enter transfer amount: ";
                cin >> amount;

                Account* toAccount = findAccount(toAccountNumber);
                if (toAccount == nullptr) {
                    cout << "Recipient account not found!" << endl;
                } else {
                    account->transfer(*toAccount, amount);
                }
                break;
            }
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    void displayAccounts() {
        if (accounts.empty()) {
            cout << "No accounts available." << endl;
            return;
        }

        cout << "List of accounts:" << endl;
        for (const auto &account : accounts) {
            cout << "Account Number: " << account.getAccountNumber()
                 << ", Name: " << account.getName()
                 << ", Balance: $" << account.getBalance() << endl;
        }
    }
};

int main() {
    BankSystem bank;
    int choice;

    while (true) {
        cout << "\n1. Create Account\n2. Perform Transaction\n3. Display Accounts\n4. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.performTransaction();
                break;
            case 3:
                bank.displayAccounts();
                break;
            case 4:
                cout << "Exiting system. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
}