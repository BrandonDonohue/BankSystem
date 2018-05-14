// Kyle Loyka Brandon Donohue
// CSCE 113
// Project 1

// Bank.h

#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <string>
#include <vector>
#include "Customer.h"

using namespace std;

class Bank {
	private:
		vector<Customer> accounts;

	public:
		Bank(vector<Customer> c) {	// copy constructor
			accounts = c;
		}
		Bank():											// default constructor
		accounts() {}

		void readData();
		void writeData();
		void close_account(int num);
		bool check_acc(int ii);

		double totalDeposits();
		double avgBalance();
		void new_account(Customer c);
		void rewriteAccount(int num, Customer& c);
		Customer search(int num);
		int numberOfCustomers();
};

int randomPIN();
int randomACC(Bank& b);






























#endif
