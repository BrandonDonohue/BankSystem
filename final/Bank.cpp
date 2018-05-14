// Kyle Loyka Brandon Donohue
// CSCE 113
// Project 1

// Bank.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Customer.h"
#include "Bank.h"
#include "History.h"

using namespace std;

// creating new user account
void Bank::new_account(Customer c) {
	this->accounts.push_back(c);
}

// closing account, takes account number as an argument
void Bank::close_account(int num) {
	for(int n = 0; n < this->accounts.size(); ++n) {
		if(this->accounts[n].acc_num() == num)
			this->accounts.erase( this->accounts.begin() + n );
	}
}

// random PIN number generator
int randomPIN(){
	int pin = rand() % 10000 + 999; // 4 digits long
	bool ready = false;
	while(!ready){
		if (pin < 999) pin = pin*10;
		else if (pin > 9999) pin = pin/10;
		else ready = true;
	}
	return pin;
}

// account number generator, ensures no duplicate account numbers
int randomACC(Bank& b){
	bool run = true;
	int acc=0;
	while(run){
	acc = rand() % 999999;	// 6 digits long
	run = b.check_acc(acc);
	}
	return acc;
}

// reading data from the the data file
void Bank::readData() {
	ifstream file;
	file.open ("data.txt");

	while(!file.eof() ){
	  Customer temp;
	  inputCustomer(file, temp);
	  this->accounts.push_back(temp);
	}// while

	file.close();
}

// writing data to the data file
void Bank::writeData() {
	ofstream file;
	//remove( "data.txt");
	file.open("data.txt", ofstream::out | ofstream::trunc);
	for (int i=0; i<this->accounts.size(); ++i ){
			this->accounts[i].outputCustomer(file);
	}

	file.close();
}

// overwrites an account's data with new data
void Bank::rewriteAccount(int num, Customer& c){
	for(int i=0; i < this->accounts.size(); ++i) {
		if(this->accounts[i].acc_num() == num){
				this->accounts[i] = c;
		}
	}
}

// search for a Customer account given the account number
Customer Bank::search(int num) {
		for(int i=0; i < this->accounts.size(); ++i) {
			if(this->accounts[i].acc_num() == num) return this->accounts[i];
		}
		Customer c;
		return c;           // just to remove warnings, input account number
							// should be clean before this so this return is not necessary.
							// however, just in case, it will return a blank Customer class
	}

// computes total number of customers in Bank
int Bank::numberOfCustomers(){
	return this->accounts.size()-1;
}

// check to see if account number & account exists
bool Bank::check_acc(int ii) {
	for(int i=0; i < this->accounts.size(); ++i){
		if(this->accounts[i].acc_num() == ii) return true;
	} //for
	return false;
}//check_acc

// computes total number of deposits in Bank
double Bank::totalDeposits(){
	double deposit = 0;

	for (int j = 0; j < this->accounts.size() ; ++j){
		Customer user = this->accounts[j];
		vector<History>temp;
		temp = user.transactionList();

		for (int i = 0; i<10; ++i){
		 	if (temp[i].amount() > 0) deposit = deposit + temp[i].amount();
		}
	}
	return deposit;
}

// computes average balance of all bank customers
double Bank::avgBalance(){
	double balance = 0;

	for (int j = 0; j < this->accounts.size() ; ++j){
		balance = balance + this->accounts[j].balance();
	}
	balance = balance / this->numberOfCustomers();
	return balance;
}
