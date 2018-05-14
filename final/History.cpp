// Kyle Loyka Brandon Donohue
// CSCE 113
// Project 1

// History.cpp

#include <string>
#include <ctime>
#include <iostream>
#include "History.h"


using namespace std;

// output overloading
ostream& operator<<(ostream& os, History& h){
  return os<<"Date: "<< h.date()<<"\n"
           <<"Amount: "<< h.amount()<<"\n";
}

// input overloading
istream& operator>>(istream& is, History& h){
  //temp objects
  string a,b,c,d;
  int n;

  //take input
  is >> a >> b >> c >> d >> n;

  //checking inputs
  if(!is) return is;
  if(a !="Date:" || d !="Amount:" ){
    is.clear(ios_base::failbit);
    return is;
  }

  h.loadData(b+c,n);
  return is;

}

// use for loading (prevous) data into a History object
void History::loadData(string ss, double dd){
  this->s = ss;
  this->d = dd;
}

// use for new transactions
void History::newData(double dd){
  this->s = current_time();
  this->d = dd;
}

// finds current system time
//http://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
string current_time(){
  time_t raw;
  struct tm * timedata;
  char buffer[80];

  time (&raw);
  timedata = localtime(&raw);

  // strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo); //this gives date and time
  strftime(buffer,80,"%Y-%m-%d",timedata);              // this only gives date
  string output(buffer);

  return output;
}
