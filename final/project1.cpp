/****************************
  Project #1 CSCE 113-502
	Names: Donohue, Brandon     Loyka, Kyle
	Login:  bdonohue             kloyka

*****************************/
/*
	This project entails designing a program that works like
a bank teller. Customers can add/delete accounts, withdraw/deposit
money or look up previous transactions. There is also an admin function
to look at the total amount in the bank and the list of current
customers.
*/

#include "Customer.h"
#include "Bank.h"
#include "History.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

void welcome();
void menu_new_account(Bank& b);
void menu_close_account(Bank& b);
void menu_withdraw(Bank& b);
void menu_deposit(Bank& b);
void menu_account_balance(Bank& b);
void menu_transaction_history(Bank& b);
void menu_statistics(Bank& b);
void checkInput();

int main() {
	int menu;
	Bank b;
	b.readData();
	while (1){
		try{
			welcome();
			cin >> menu;
			checkInput();

			if(menu == 1) menu_new_account(b);					// open new account
			if(menu == 2) menu_close_account(b);				// close account
			if(menu == 3) menu_withdraw(b);							// withdraw from account
			if(menu == 4) menu_deposit(b);							// deposit to account
			if(menu == 5) menu_account_balance(b);			// display customer's account balance
			if(menu == 6) menu_transaction_history(b); 	// display customer's transactions
			if(menu == 7) menu_statistics(b);					// admin bank statistics
			if(menu == 8) break;												// quits program
		}

		catch (exception& e) {
			cerr << "error: " << e.what() << '\n';
			cin.clear();
		}
	}
	b.writeData();
	return 0;
}



void welcome(){
	cout << "\n\n*****************************\n";
	cout << "*            MENU           *\n";
	cout << "*****************************\n";
	cout<<endl<<endl;
	cout << "This is your Piggy Bank. Welcome valued customer." << endl
		<< "Please select one of these options:" << endl
		<< "1: Open a new account\n"
		<< "2: Close an existing account\n"
		<< "3: Withdraw\n"
		<< "4: Deposit\n"
		<< "5: Account Balance\n"
		<< "6: Last 10 transactions\n"
		<< "7: Statistical Info\n"
		<< "8: quit\n"<< endl;
}

void menu_new_account(Bank& b){
	cout << "\033[2J\033[1;1H";
	cout << "\n------- Create An Account -------\n\n";

	Customer user;
	string name1, name2;
	double balance;
	cout << "Enter your first and last name. " << endl;
	cin >> name1 >> name2;
	cout << "Please enter initial deposit amount. (no dollar signs)"<< endl;
	cin >> balance;
	checkInput();
	if (balance < 1000 ) {
		cout << "Minimum deposit of atleast $1000 required. Account was not created."<<endl;
		return;
	}

	int pin = randomPIN();
	int acc = randomACC(b);

	user.newData(name1 + " " + name2, acc, pin, balance);

	b.new_account(user);
	cout <<"\naccount created\n\n";
	cout<<"-------------\n";
	cout <<"Account Number: "<< acc <<endl;
	cout <<"PIN Number: "<< pin<< endl;
	cout<<"-------------\n";
	b.writeData();


}

void menu_close_account(Bank& b){
	cout << "\033[2J\033[1;1H";
	cout << "\n------- Close An Account -------\n\n";
	int choice = 0;
	int acc = 0;
	int pin = 0;

	while(1){
	 cout << "Are you sure you want to close your account?" << endl
	 << "1: yes   2: no" << endl;
	 cin >> choice;
	 checkInput();

	 if(choice == 1) {
		 cout << "Enter your account number." << endl;
		 cin >> acc;
		 cout << "Enter your PIN." << endl;
		 cin >> pin;
		 checkInput();

		 Customer user;
		 if ( b.check_acc(acc) ){
				user = b.search(acc);
			}

		 else{
				cout <<"Invalid Account Number."<<endl;
				return;
			}

		 if (user.pin() == pin ){
				double ddd = user.balance();
		 		b.close_account( user.acc_num() );
				if (ddd < 500) cout << "$"<< ddd << " withdrawn";
				if (ddd > 500) cout << "$500 MAX withdrawn, please see cashier";
		 		cout << "\n\nAccount Closed.\n\n";
				b.writeData();
				return;
		 }
		 else {
			cout << "Invalid PIN.\n";
		 	return;
			}
		} // if (choice == 1)

		else if (choice == 2) {
			cout << "\n\nCancelled.\n\n";
			return;
		} // else if (choice == 2)

		else{
			cout<<"Invalid Entry.\n";
		}

	} // while(1)

} // menu_close_account

void menu_withdraw(Bank& b){
	cout << "\033[2J\033[1;1H";
	cout << "\n------- Withdraw -------\n\n";
	Customer user;
	int pin, acc;

	cout << "Notice: A $10 maintenance fee will be applied if your account balance falls below $1000." << endl;
	cout << "Max withdraw of $500:\n\n";

	cout << "Enter your account number." << endl;
	cin >> acc;
	checkInput();
	cout << "Enter your PIN." << endl;
	cin >> pin;
	checkInput();
	if ( b.check_acc(acc) ){
		user = b.search(acc);
	}

	else{
		cout <<"Invalid Account Number."<<endl;
		return;
	}

	if (user.pin() == pin ){
		double amount = 0;
		cout << "Please enter the amount of money you would like to withdraw (no dollar sign)\n";
		cin >> amount;
		checkInput();

		if ( -500 < amount && amount < 500 ){
			user.withdraw(amount);
			b.rewriteAccount(acc, user);
			b.writeData();
			cout << "Withdraw Complete.\n";
			if (user.balance() < 1000 ){
				cout<< "Account balance is below $1000. $10 fee was charged.\n";
				user.withdraw(10);
				b.rewriteAccount(acc, user);
				b.writeData();
				}
			if (user.balance() < 50 ){
				cout << "Account balance is below minimum value. Account is closed.\n";
				b.close_account( user.acc_num() );
				b.writeData();
			}
			return;
		}
		else {
			cout << "Invalid withdraw amount. Please see cashier.\n";
			return;
		}
	}

	else {
		cout << "Invalid PIN.\n";
		return;
	}
}

void menu_deposit(Bank& b){
	cout << "\033[2J\033[1;1H";
	cout << "\n------- Deposit -------\n\n";
	Customer user;
	int pin, acc;

	cout << "Enter your account number." << endl;
	cin >> acc;
	checkInput();
	cout << "Enter your PIN." << endl;
	cin >> pin;
	checkInput();
	if ( b.check_acc(acc) ){
		user = b.search(acc);
	}

	else{
		cout <<"Invalid Account Number."<<endl;
		return;
	}

	if (user.pin() == pin ){
		double amount = 0;
		cout << "Please enter the amount of money you would like to deposit (no dollar sign)\n";
		cin >> amount;
		checkInput();
		if (amount < 0){
			cout<<"Invalid deposit.\n";
			return;
		}
		user.deposit(amount);
		b.rewriteAccount(acc, user);
		b.writeData();
		cout << "Deposit Complete.\n";
		return;
		}

	else {
		cout << "Invalid PIN.\n";
		return;
	}
	b.writeData();
}

void menu_account_balance(Bank& b){
	cout << "\033[2J\033[1;1H";
	cout << "\n------- Account Balance -------\n\n";
	Customer user;
	int pin, acc;
	cout << "Enter your account number." << endl;
	cin >> acc;
	checkInput();
	cout << "Enter your PIN." << endl;
	cin >> pin;
	checkInput();

	if ( b.check_acc(acc) ){
		user = b.search(acc);
	}
	else{
		cout <<"Invalid Account Number."<<endl;
		return;
	}

	if (user.pin() == pin ){
		print(cout, user);
	}
	else {
		cout << "Invalid PIN.\n";
		return;
	}
}

void menu_transaction_history(Bank& b){
	cout << "\033[2J\033[1;1H";
	cout << "\n------- Transaction History -------\n\n";
	Customer user;
	int pin,acc;
	cout << "Enter your account number." << endl;
	cin >> acc;
	checkInput();
	cout << "Enter your PIN." << endl;
	cin >> pin;
	checkInput();

	if ( b.check_acc(acc) ){
		user = b.search(acc);
	}
	else{
		cout <<"Invalid Account Number."<<endl;
		return;
	}

	if (user.pin() == pin ){
		user.printTransaction();
	}
	else {
		cout << "Invalid PIN.\n";
		return;
	}
	b.writeData();
}

void menu_statistics(Bank& b){
	cout << "\033[2J\033[1;1H";
	cout << "\n------- Admin Access -------\n\n";
	const int admin = 123;	// admin password
	int pass;
		cout << "Enter your admin password. (admin password: 123 )" << endl;
		cin >> pass;
		checkInput();

		if(pass == admin){
			int choice2;

			cout << "Please choose an option:" << endl
				<< "1: Total number of customers\t"
				<< "2: Total amount of deposits\t"
				<< "3: Average current balance" << endl;
			cin >> choice2;
			checkInput();

			if(choice2 == 1){
				cout<< "Number of Customers: " << b.numberOfCustomers() << endl;
			}
			if(choice2 == 2){
				cout<< "Total Deposits: " << b.totalDeposits() << endl;
			}
			if(choice2 == 3){
				cout << "Average Balance: " << b.avgBalance() << endl;
			}
		}
		else cout << "Incorrect Password.\n";
		b.writeData();
}

void checkInput(){
	if (cin.fail() ) {
		cin.clear();
		cin.ignore(1);
		throw invalid_argument("invalid input");
	}
}
