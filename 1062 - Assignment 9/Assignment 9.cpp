#include <iostream>
#include <map>
#include <iomanip>
#include <thread>
#include <chrono>
#include "Account.h"

using namespace std;

void menu(Account&);
void viewMyBalance(Account&);
void withdrawCash(Account&);
void depositFunds(Account&);

int cashInATM = 500;

int main()
{
	Account account01("12345", "54321", 1000.0, 1200.0), account02("98765", "56789", 200.0, 200.0);
	map< string, Account > information;
	information["12345"] = account01;
	information["98765"] = account02;
	while(1)
	{
		if(!cin)
			return 0;
		string sign, code;
		cout << "\nWelcome!\n\nPlease enter your account number: ";
		cin >> sign;
		if(information.find(sign) != information.end())
		{
			cout << "\nEnter your PIN: ";
			cin >> code;
			if(code == information[sign].getPassword())
				menu(information[sign]);
			else
				cout << "\nInput the wrong PIN! Please retry." << endl;
		}
		else
			cout << "\nInexistent account! please retry." << endl;
	}
}

void menu(Account& ac)
{
	int choice;
	while(1)
	{
		cout << "\nMain menu:\n1 - View my balance\n2 - Withdraw cash\n3 - Deposit funds\n4 - Exit\n\nEnter a choice: ";
		cin >> choice;
		switch(choice)
		{
		case 1:
			viewMyBalance(ac);
			break;
		case 2:
			withdrawCash(ac);
			break;
		case 3:
			depositFunds(ac);
			break;
		case 4:
			cout << "\nExiting the system...\n\nThank you! Goodbye!" << endl;
			return;
		default:
			cout << "\nInvalid input. Please try again." << endl;
		}
	}
}

void viewMyBalance(Account& ac)
{
	cout << "\nBalance Information:" << endl;
	cout << " - Available balance: $" << fixed << setprecision(2) << ac.getAvailableBalance() << endl;
	cout << " - Total balance:     $" << ac.getTotalBalance() << endl;
}

void withdrawCash(Account& ac)
{
	int choice;
	while(1)
	{
		cout << "\nWithdrawal options:\n1 - $20\n2 - $40\n3 - $60\n4 - $100\n5 - $200\n6 - Cancel transaction\n\nChoose a withdrawal option (1-6): ";
		cin >> choice;
		switch(choice)
		{
		case 1:
			if(cashInATM >= 1 && ac.getAvailableBalance() >= 20.0)
			{
				cashInATM--;
				ac.withdraw(20.0);
				cout << "\nPlease take your cash from the cash dispenser." << endl;
				return;
			}			
		case 2:
			if(cashInATM >= 2 && ac.getAvailableBalance() >= 40.0)
			{
				cashInATM -= 2;
				ac.withdraw(40.0);
				cout << "\nPlease take your cash from the cash dispenser." << endl;
				return;
			}		
		case 3:
			if(cashInATM >= 3 && ac.getAvailableBalance()>= 60.0)
			{
				cashInATM -= 3;
				ac.withdraw(60.0);
				cout << "\nPlease take your cash from the cash dispenser." << endl;
				return;
			}
		case 4:
			if(cashInATM >= 5 && ac.getAvailableBalance() >= 100.0)
			{
				cashInATM -= 5;
				ac.withdraw(100.0);
				cout << "\nPlease take your cash from the cash dispenser." << endl;
				return;
			}
		case 5:
			if(cashInATM >= 10 && ac.getAvailableBalance() >= 200.0)
			{
				cashInATM -= 10;
				ac.withdraw(200.0);
				cout << "\nPlease take your cash from the cash dispenser." << endl;
				return;
			}
			cout << "\nFailed to withdraw. Please try again.\n\nThe posible reason:\n - Not enough available balance.\n - Not enough bill to provide." << endl;
			break;
		case 6:
			return;
		default:
			cout << "\nInvalid input. Please try again." << endl;
		}
	}
}

void depositFunds(Account& ac)
{
	double amount;
	cout << "\nPlease enter a deposit amount in CENTS (or 0 to cancel): ";
	cin >> amount;
	amount /= 100.0;
	cout << "\nPlease insert a deposit envelope containing $" << fixed << setprecision(2) << amount << " in the deposit slot." << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << "\nYour envelope has been received.\nNOTE: The money deposited will not be available until we\nverify the amount of any enclosed cash, and any enclosed checks clear." << endl;
	ac.deposit(amount);
}