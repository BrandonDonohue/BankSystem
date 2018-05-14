// Kyle Loyka Brandon Donohue
// CSCE 113
// Project 1

// Customer.h

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include <vector>
#include "History.h"

using namespace std;

class Customer {
public:
      Customer(string ss, int aa, int pp, double bb):s(ss),
       a(aa), p(pp), b(bb) {}
      Customer():                           //default constructor
        s("Customer Name"),
        a(0),
        p(0),
        b(0){}

      string name() { return s;}            //some basic functions to
      int acc_num() { return a;}            // access private objects
      int pin() {return p;}
      double balance() {return b;}

      void printTransaction();
      void withdraw(double n);
      void deposit(double n);
      void transactions();
      void newData(string ss, int aa, int pp, double bb);
      void newTransaction(double dd);
      void outputCustomer(ostream& os);
      void loadTransaction(string ss, double dd, int ii);
      vector<History> transactionList();

private:
      string s; // name
      int a;    // account number
      int p;    // pin
      double b; // balance
      History transaction[10];  // array of transaction histories
};


ostream& operator<<(ostream& os, Customer& c);
istream& operator>>(istream& is, Customer& cc);

void print(ostream& os, Customer c);
void inputCustomer(istream& is, Customer& c);

#endif
