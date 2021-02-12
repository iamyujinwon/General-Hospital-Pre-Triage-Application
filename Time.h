/*
Final Project Milestone 1
Name : Yujin Won
Email: ywon9@myseneca.ca
Student ID: 153565197
Date: 2020/11/12

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_TIME_H
#define SDDS_TIME_H
#include <iostream>
namespace sdds
{
  class Time
  {
    unsigned int m_min;
  public:
    Time& reset();
    Time(unsigned int min = 0);
    std::ostream& write(std::ostream& ostr) const;
    std::istream& read(std::istream& istr);
    operator int()const;
    Time& operator *= (int val);
    Time& operator-=(const Time& D);
  
    //add for M5
    Time operator-(const Time& ROperand);
  };
  // helper operator << and >> prototypes
  std::ostream& operator<<(std::ostream& os, const Time& T);
  std::istream& operator>>(std::istream& istr, Time& T);
}
#endif // !SDDS_TIME_H

