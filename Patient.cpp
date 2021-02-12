/*
Final Project Milestone 3
Name : Yujin Won
Email: ywon9@myseneca.ca
Student ID: 153565197
Date: 2020/11/18

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Patient.h"
#include "utils.h"
using namespace std;
namespace sdds
{
  Patient::Patient(int ticketNum, bool flag) : m_ticket(ticketNum) {
    m_fileIO = flag;
  }

  Patient::~Patient() {
    delete[] m_patientName;
  }

  bool Patient::fileIO()const {
    return m_fileIO;
  }

  void Patient::fileIO(bool flag) {
    m_fileIO = flag;
  }

  bool Patient::operator==(const char ch)const {
    return ch == type();
  }

  bool Patient::operator==(const Patient& P)const {
    return type() == P.type();
  }

  void Patient::setArrivalTime() {
    m_ticket.resetTime();
  }

  Patient::operator Time()const {
    return Time(m_ticket);
  }

  int Patient::number()const {
    return m_ticket.number();
  }

  ostream& Patient::csvWrite(ostream& ostr)const {
    ostr << type() << ',' << m_patientName << ',' << m_ohipNum << ',';
    m_ticket.csvWrite(ostr);
    return ostr;
  }

  istream& Patient::csvRead(istream& istr) {
    char string[51];

    istr.get(string, 51, ',');
    delete[] m_patientName;
    m_patientName = new char[strlen(string) + 1];
    strcpy(m_patientName, string);
    istr.ignore(1000, ',');
    istr >> m_ohipNum;
    istr.ignore(1000, ',');
    m_ticket.csvRead(istr);

    return istr;
  }

  ostream& Patient::write(ostream& ostr)const {
    m_ticket.write(ostr) << endl;
    ostr << m_patientName << ", OHIP: " << m_ohipNum;
    return ostr;
  }

  istream& Patient::read(istream& istr) {
    char name[51];
    int number;
    bool ok = false;

    cout << "Name: ";
    istr.get(name, 51, '\n');
    delete[] m_patientName;
    m_patientName = new char[strlen(name) + 1];
    strcpy(m_patientName, name);
    istr.ignore(1000, '\n');

    cout << "OHIP: ";
    while (!ok) {
      istr >> number;
      if (istr.fail()) {
        cout << "Bad integer value, try again: ";
        cin.clear();
        cin.ignore(1000, '\n');
      }
      else {
        if (number >= 100000000 && number <= 999999999) {
          m_ohipNum = number;
          cin.ignore(1000, '\n');
          ok = true;
        }
        else {
          cout << "Invalid value enterd, retry[100000000 <= value <= 999999999]: ";
          cin.ignore(1000, '\n');
        }
      }
    }

    return istr;
  }
}