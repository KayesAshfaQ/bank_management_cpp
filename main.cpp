#include <iostream>
#include <string>
using namespace std;

// user class is an example of encapsulation
// user model class
class User
{
private:
    // user properties
    string username;
    string phone;
    string address;
    string email;
    string profession;

public:
    // constructor
    User(string username, string phone, string address, string email, string profession)
    {
        this->username = username;
        this->phone = phone;
        this->address = address;
        this->email = email;
        this->profession = profession;
    }

    // getters and setters
    string getUsername() { return username; }
    void setUsername(string username) { this->username = username; }

    string getPhone() { return phone; }
    void setPhone(string phone) { this->phone = phone; }

    string getAddress() { return address; }
    void setAddress(string address) { this->address = address; }

    string getEmail() { return email; }
    void setEmail(string email) { this->email = email; }

    string getProfession() { return profession; }
    void setProfession(string profession) { this->profession = profession; }

    // show user info
    void displayInfo()
    {
        cout << "Username: " << username << endl;
        cout << "Phone: " << phone << endl;
        cout << "Address: " << address << endl;
        cout << "Email: " << email << endl;
        cout << "Profession: " << profession << endl;
    }
};

// Account class is an example of abstraction
// with pure virtual functions
//
// Abstract Base class
class Account
{
protected:
    // Account properties
    string accountNumber;
    double balance;

public:
    // Constructor
    Account(string accNum, double initialBalance)
    {
        accountNumber = accNum;
        balance = initialBalance;
    }

    // Abstract methods
    virtual void processTransaction(double amount, int type) = 0;

    virtual void displayInfo()
    {
        cout << "Account Number: " << accountNumber << "\nBalance: $" << balance << endl;
    }
};

// SavingsAccount class is an example of inheritance
// with polymorphism
// it is a derived from abstract class Account
class SavingsAccount : public Account
{
    // property for savings account
    double interestRate;

public:
    // User pointer for savings account holder
    User *user;

    // Constructor
    SavingsAccount(string accNum, double initialBalance, double rate, User *user) : Account(accNum, initialBalance)
    {
        this->interestRate = rate;
        this->user = user;
    }

    // example of polymorphism
    // override method from base class Account
    //
    // overloaded method for process transaction
    //
    // method for process transaction
    // type = 1 means deposit, type = 2 means withdrawal
    void processTransaction(double amount, int type) override
    {
        if (type == 1)
        {
            balance += amount;
        }
        else
        {
            balance -= amount;
        }
    }

    // example of polymorphism
    // overloaded method for process transaction
    //
    // method for process transaction with description
    void processTransaction(double amount, int type, string description)
    {
        processTransaction(amount, type);
        cout << description << endl;
    }

    // method for calculate interest
    void calculateInterest()
    {
        double interest = balance * (interestRate / 100);
        processTransaction(interest, 1);
    }

    // method for display account info
    void displayInfo() override
    {
        cout << "Savings ";
        cout << "Account Holder: " << user->getUsername() << endl;
        Account::displayInfo();
    }
};

// DepositAccount class is an example of inheritance
// with polymorphism
// it is a derived from abstract class Account
class DepositAccount : public Account
{
    // properties for deposit account
    double monthlyDeposit;
    int completedMonths;
    int totalMonths;

public:
    // constructor
    DepositAccount(string accNum, double initialBalance, double monthlyDeposit, int completedMonths, int totalMonths) : Account(accNum, initialBalance)
    {
        this->monthlyDeposit = monthlyDeposit;
        this->completedMonths = completedMonths;
        this->totalMonths = totalMonths;
    }

    // example of polymorphism
    // override method from base class Account
    //
    // type = 1 for deposit, type = 2 for withdrawal
    void processTransaction(double amount, int type) override
    {
        if (type == 1)
        {
            balance += amount;
        }
        else
        {
            balance -= amount;
        }
    }

    // example of polymorphism
    // overloaded method for process transaction
    //
    // method for process transaction with description
    void processTransaction(double amount, int type, string description)
    {
        processTransaction(amount, type);
        cout << description << endl;
    }

    // method for pay monthly deposit
    void payDeposit()
    {
        if (completedMonths < totalMonths)
        {
            processTransaction(monthlyDeposit, 1);
            completedMonths++;
        }
        else
        {
            cout << "Deposit Completed." << endl;
        }
    }

    // method for withdraw deposit
    void withdrawDeposit()
    {
        if (completedMonths < totalMonths)
        {
            cout << "Deposit is not completed yet." << endl;
        }
        else
        {
            processTransaction(balance, 2);
            cout << "Deposit Withdrawn." << endl;
        }
    }

    // method for calculate anticipated amount after deposit completed
    void totalDepositAmount()
    {
        cout << "Total Deposit for " << totalMonths / 12 << " Year. Amount: " << monthlyDeposit * totalMonths << " taka." << endl;
    }

    // method for display account info & deposit info
    void displayInfo() override
    {
        Account::displayInfo();
        cout << "Deposited amount : " << completedMonths * monthlyDeposit << endl;
    }
};

// the main function
int main()
{

    User user("Kayes Ashfaq", "555-555-5555", "123 Dhaka", "asfak7074@gmail.com", "Software Engineer");
    // user.displayInfo();

    SavingsAccount savings("SA123456", 1000.0, 5.0, &user);

    savings.displayInfo();

    savings.processTransaction(500.0, 2, "Withdrawal");
    savings.displayInfo();

    savings.calculateInterest();
    savings.displayInfo();

    DepositAccount deposit("DA123456", 1000.0, 500.0, 0, 12);
    deposit.displayInfo();
    deposit.payDeposit();
    deposit.displayInfo();

    return 0;
}
