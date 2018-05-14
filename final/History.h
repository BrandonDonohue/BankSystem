// Kyle Loyka Brandon Donohue
// CSCE 113
// Project 1

// History.h

#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include <string>
using namespace std;

class History {
public:
      History(string ss, double dd):s(ss), d(dd){}
      History():
        s("--"),        //default constructor
        d(0){}

      string date() {return s;}   // basic functions to access private members
      double amount() {return d;}

      void newData(double dd);
      void loadData(string ss, double dd);

private:
      string s;          // date
      double d;          // transaction amount
};

ostream& operator<<(ostream& os, History& h);
istream& operator>>(istream& is, History& h);

string current_time();


#endif
