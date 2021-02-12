/*
Final Project Milestone 1
Name : Yujin Won
Email: ywon9@myseneca.ca
Student ID: 153565197
Date: 2020/11/12

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include "Time.h"
#include "utils.h"
using namespace std;
namespace sdds
{
  Time Time::operator-(const Time& ROperand) {
    Time LOperand = *this;
    LOperand -= ROperand;
    return LOperand;
  }

  Time& Time::reset() {
    m_min = getTime();
    return *this;
  }

  Time::Time(unsigned int min) {
    m_min = min;
  }

  ostream& Time::write(ostream& ostr) const {
    int hour = m_min / 60;
    int min = m_min % 60;

    ostr << setw(2) << setfill('0') << right << hour << ":";
    ostr << setw(2) << setfill('0') << right << min;

    return ostr;
  }

  istream& Time::read(istream& istr) {
    int hourTemp;
    char singleChar = '\0';
    int minTemp;

    istr >> hourTemp;
    singleChar = istr.get();
    if (singleChar == ':') {
      istr >> minTemp;

      m_min = hourTemp * 60 + minTemp;
    }
    else {
      istr.setstate(ios::failbit);
    }
    return istr;
  }

  Time::operator int()const {
    return m_min;
  }

  Time& Time::operator *= (int val) {
    m_min *= val;

    return *this;
  }

  Time& Time::operator-=(const Time& D) {
    int diff = m_min - D.m_min;

    if (diff < 0) {
      m_min += 1440;
      m_min -= D.m_min;
    }
    else {
      m_min = diff;
    }
    return *this;
  }

  ostream& operator<<(ostream& os, const Time& T) {
    return T.write(os);
  }

  istream& operator>>(istream& istr, Time& T) {
    return T.read(istr);
  }
}