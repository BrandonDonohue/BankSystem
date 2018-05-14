// Kyle Loyka Brandon Donohue
// CSCE 113
// Project 1

// Customer.cpp

#include "Customer.h"
#include "History.h"
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

// output operator overloading
ostream& operator<<(ostream& os,Customer& d){
  if (d.name() == "Customer Name") return os<<"";
  return os<<"Name:           "<< d.name()<<"\n"
           <<"Account Number: "<<setfill('0')<<setw(6)<< d.acc_num()<<"\n"
           <<"PIN:            "<<setfill('0')<<setw(4)<<d.pin()<<'\n'
           <<"Balance:        "<<setprecision(2)<<fixed<< d.balance()<<'\n';
}

// input operator overloading
istream& operator>>(istream& is, Customer& cc){
  //make some temp variables
  string s;
  int i,p;
  double b;
  string ch1, ch2, ch3, ch4;

  //take input
  is>> ch1 >> s >> ch2 >> i >> ch3 >> p >> ch4 >> b;

  //checking inputs
  if(!is) return is;
  if(ch1 !="customer" || ch2 != "account" || ch3 !="PIN" || ch4 !="balance"){
    is.clear(ios_base::failbit);
    return is;
  }

  //putting user inputs into a "Customer"
  cc.newData(s,i,p,b);
  return is;

}

// function to output Customer data in an elegant format
void Customer::outputCustomer(ostream& os){
  if (this->name() == "Customer Name") return;
  os << "[ ";
  os << "customer " << this->name()<<'\n';
  os << "account "  <<setfill('0')<<setw(6)<< this->acc_num()<<'\n';
  os << "PIN " <<setfill('0')<<setw(4)<<  this->pin()<<'\n';
  os << "balance " << setprecision(2)<<fixed<< this->balance()<<'\n';
  os << "transactions { ";
  for (int i = 0; i<10; ++i){
    os <<"( "<< transaction[i].date() <<" "<< transaction[i].amount()<<" ) ";
  }
  os << "} " << '\n'<<"]"<<'\n';
}

// read helper function to load customer data from a file
void inputCustomer(istream& is, Customer& c){
  string s1,s2,s3,s4,s5,s6,s7,s8,s9,s10;
  string first_name, last_name;
  string d0[10];
  double j[10];
  char ch1, ch2, ch3, ch4;
  char ch5[20];
  int account_number, pin_number;
  double amount_number;



  is >> ch1 >> s1 >> first_name >> last_name >> s2 >> account_number >> s3
    >> pin_number >> s4 >> amount_number >> s5 >> ch2
    >> ch5[0] >> d0[0] >> j[0] >> ch5[1]
    >> ch5[2]>> d0[1] >> j[1]>> ch5[3]
    >> ch5[4]>> d0[2] >> j[2]>> ch5[5]
    >> ch5[6]>> d0[3] >> j[3]>> ch5[7]
    >> ch5[8]>> d0[4] >> j[4]>> ch5[9]
    >> ch5[10]>> d0[5] >> j[5]>> ch5[11]
    >> ch5[12]>> d0[6] >> j[6]>> ch5[13]
    >> ch5[14]>> d0[7] >> j[7]>> ch5[15]
    >> ch5[16]>> d0[8] >> j[8]>> ch5[17]
    >> ch5[18]>> d0[9] >> j[9]>> ch5[19]
    >> ch3 >> ch4;

  if(!is) return;
  if(ch1 !='['|| s1 != "customer" || s2 !="account" || s3 !="PIN" ||
      s4 !="balance" || s5!="transactions" || ch2!= '{' || ch3!='}' || ch4!=']'){
    is.clear(ios_base::failbit);
    return;
  }

  c.newData(first_name+" "+last_name, account_number, pin_number, amount_number);
  for (int i = 0; i < 10; ++i){
    c.loadTransaction( d0[i], j[i], i);
  }

}

// helper function to load transaction data from a file
void Customer::loadTransaction(string ss, double dd, int ii){
  transaction[ii].loadData(ss,dd);
}

// another print customer function. Just another formatting option....
// honestly a bit redundant
void print(ostream& os, Customer c){
  if (c.name() == "Customer Name") return;
  os << '\n';
  os << "-- ACCOUNT INFORMATION: --";
  os << '\n';
  os << c << endl;
  os << "--  TRANSACTION HISTORY:  --"<< '\n'<<'\n';
  c.printTransaction();
}

// withdraw from account
void Customer::withdraw(double m){
  this->b = this->b - abs(m);
  this->newTransaction(-abs(m) );
}

// deposit into account
void Customer::deposit(double m){
  this->b = this->b + abs(m);
  this->newTransaction(abs(m) );
}

// for writing data to a NEW customer
void Customer::newData(string ss, int aa, int pp, double bb){
  this->s = ss;
  this->a = aa;
  this->p = pp;
  this->b = bb;
  this->newTransaction(bb);
}

// updating transaction history
void Customer::newTransaction(double dd){
  History temp;
  temp.newData(dd);
  transaction[9] = transaction[8];
  transaction[8] = transaction[7];
  transaction[7] = transaction[6];
  transaction[6] = transaction[5];
  transaction[5] = transaction[4];
  transaction[4] = transaction[3];
  transaction[3] = transaction[2];
  transaction[2] = transaction[1];
  transaction[1] = transaction[0];
  transaction[0] = temp;
}

// print only transaction history for a customer
void Customer::printTransaction() {
  for (int i = 0; i<10; ++i){
    cout<<transaction[i]<<'\n';
  }
}

// return a list of all transactions
vector<History> Customer::transactionList(){
  vector<History>h;
  for (int i = 0; i<10; ++i){
    h.push_back(this->transaction[i]);
  }
  return h;
}
