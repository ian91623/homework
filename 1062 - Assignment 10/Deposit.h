// Deposit.h
// Deposit class definition. Represents a deposit transaction.
#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <vector> // class uses vector to store Account objects
#include <chrono>
#include <thread>
using namespace std;
#include "Account.h" // Account class definition

class Deposit
{
public:
   Deposit( int userAccountNumber, vector< Account > &atmAccounts );
   void execute(); // perform the deposit transaction
private:
   int accountNumber; // indicates account involved
   vector< Account > &accounts; // reference to the vector of the bank's Accounts
   double amount; // amount to deposit

   // get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
   Account * getAccount( int accountNumber, vector< Account > &accounts ); 
   double promptForDepositAmount() const; // prompt user to enter a deposit amount in cents 
}; // end class Deposit

Deposit::Deposit( int userAccountNumber, vector< Account > &atmAccounts )
:	accountNumber(userAccountNumber),
	accounts(atmAccounts)
{
}

void Deposit::execute()
{
	Account* ac = getAccount(accountNumber, accounts);
	amount = promptForDepositAmount();
	cout << "\nPlease insert a deposit envelope containing $" << fixed << setprecision(2) << amount << " in the deposit slot." << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << "\nYour envelope has been received.\nNOTE: The money deposited will not be available until we\nverify the amount of any enclosed cash, and any enclosed checks clear." << endl;
	ac->credit(amount);
}

double Deposit::promptForDepositAmount() const
{
	double tmp;
	cout << "\nPlease enter a deposit amount in CENTS (or 0 to cancel): ";
	cin >> tmp;
	tmp /= 100.0;
	return tmp;
}

Account *Deposit::getAccount( int accountNumber, vector< Account > &accounts )
{
	for( size_t i = 0; i < accounts.size(); i++ )
		if( accounts[i].getAccountNumber() == accountNumber )
			return &accounts[ i ];
	
	return NULL;
}

#endif // DEPOSIT_H