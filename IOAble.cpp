/*
Final Project Milestone 2
Name : Yujin Won
Email: ywon9@myseneca.ca
Student ID: 153565197
Date: 2020/11/14

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include <iostream>
#include "IOAble.h"
using namespace std;
namespace sdds
{
  ostream& operator<<(ostream& os, const IOAble& I) {
    return I.write(os);
  }

  istream& operator>>(istream& istr, IOAble& I) {
    return I.read(istr);
  }
}