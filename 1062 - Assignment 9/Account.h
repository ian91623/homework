#ifndef _ACCOUNT
#define _ACCOUNT

#include <string>

using namespace std;

class Account
{
public:
	Account(string account = "00000", string pin = "00000", double available = 0.0, double total = 0.0);
	~Account();
	Account& withdraw(double amount);
	Account& deposit(double amount);
	const double& getAvailableBalance();
	const double& getTotalBalance();
	const string& getPassword();
private:
	string accountNumber;
	string password;
	double availableBalance;
	double totalBalance;
};
#endif

Account::Account(string account, string pin, double available, double total)
:accountNumber(account), password(pin), availableBalance(available), totalBalance(total)
{	
}

Account::~Account()
{
}

Account& Account::withdraw(double amount)
{
	availableBalance -= amount;
	totalBalance -= amount;
	return *this;
}

Account& Account::deposit(double amount)
{
	totalBalance += amount;
	return *this;
}

const double& Account::getAvailableBalance()
{
	return availableBalance;
}

const double& Account::getTotalBalance()
{
	return totalBalance;
}

const string& Account::getPassword()
{
	return password;
}