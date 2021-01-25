// Withdrawal.h
// Withdrawal class definition. Represents a withdrawal transaction.
#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include <vector> // class uses vector to store Account objects
using namespace std;
#include "Account.h" // Account class definition

class Withdrawal
{
public:
	Withdrawal( int userAccountNumber, vector< Account > &atmAccounts, int &atmRemainingBills );
	void execute(); // perform the withdrawal transaction
private:
	int accountNumber; // indicates account involved
	vector< Account > &accounts; // reference to the vector of the bank's Accounts
	int amount; // amount to withdraw
	int &remainingBills;

	// get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
	Account * getAccount( int accountNumber, vector< Account > &accounts );

	// display a menu of withdrawal amounts and the option to cancel;
	// return the chosen amount or 0 if the user chooses to cancel
	int displayMenuOfAmounts() const;
}; // end class Withdrawal

Withdrawal::Withdrawal( int userAccountNumber, vector< Account > &atmAccounts, int &atmRemainingBills )
:	accountNumber(userAccountNumber),
	accounts(atmAccounts),
	remainingBills(atmRemainingBills)
{
}

void Withdrawal::execute()
{
	enum withdrawOption { _20Dollars = 1, _40Dollars, _60Dollars, _100Dollars, _200Dollars, Exit };
	Account * ac = getAccount(accountNumber, accounts);
	while(1)
	{
		int choice = displayMenuOfAmounts();
		switch(choice)
		{
		case _20Dollars:
			if(remainingBills >= 1 && ac->getAvailableBalance() >= 20.0)
			{
				remainingBills--;
				ac->debit(20.0);
				cout << "\nPlease take your cash from the cash dispenser." << endl;
				return;
			}			
		case _40Dollars:
			if(remainingBills >= 2 && ac->getAvailableBalance() >= 40.0)
			{
				remainingBills -= 2;
				ac->debit(40.0);
				cout << "\nPlease take your cash from the cash dispenser." << endl;
				return;
			}		
		case _60Dollars:
			if(remainingBills >= 3 && ac->getAvailableBalance()>= 60.0)
			{
				remainingBills -= 3;
				ac->debit(60.0);
				cout << "\nPlease take your cash from the cash dispenser." << endl;
				return;
			}
		case _100Dollars:
			if(remainingBills >= 5 && ac->getAvailableBalance() >= 100.0)
			{
				remainingBills -= 5;
				ac->debit(100.0);
				cout << "\nPlease take your cash from the cash dispenser." << endl;
				return;
			}
		case _200Dollars:
			if(remainingBills >= 10 && ac->getAvailableBalance() >= 200.0)
			{
				remainingBills -= 10;
				ac->debit(200.0);
				cout << "\nPlease take your cash from the cash dispenser." << endl;
				return;
			}
			cout << "\nFailed to withdraw. Please try again.\n\nThe posible reason:\n - Not enough available balance.\n - Not enough bill to provide." << endl;
			break;
		case Exit:
			return;
		default:
			cout << "\nInvalid input. Please try again." << endl;
		}
	}
}

int Withdrawal::displayMenuOfAmounts() const
{
	int choice;
	cout << "\nWithdrawal options:\n1 - $20\n2 - $40\n3 - $60\n4 - $100\n5 - $200\n6 - Cancel transaction\n\nChoose a withdrawal option (1-6): ";
	cin >> choice;
	return choice;
}

Account *Withdrawal::getAccount( int accountNumber, vector< Account > &accounts )
{
	for( size_t i = 0; i < accounts.size(); i++ )
		if( accounts[i].getAccountNumber() == accountNumber )
			return &accounts[ i ];
	
	return NULL;
}

#endif // WITHDRAWAL_H