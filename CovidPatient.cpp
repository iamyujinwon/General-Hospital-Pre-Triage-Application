/*
Final Project Milestone 4
Name : Yujin Won
Email: ywon9@myseneca.ca
Student ID: 153565197
Date: 2020/11/23

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include "CovidPatient.h"
using namespace std;
namespace sdds
{
  int nextCovidTicket = 1;

  CovidPatient::CovidPatient() : Patient(nextCovidTicket) {
    nextCovidTicket++;
  }
  char CovidPatient::type()const {
    return 'C';
  }
  ostream& CovidPatient::csvWrite(ostream& ostr)const {
    Patient::csvWrite(ostr);
    return ostr;
  }
  istream& CovidPatient::csvRead(istream& istr) {
    Patient::csvRead(istr);
    nextCovidTicket = number() + 1;
    return istr;
  }
  ostream& CovidPatient::write(ostream& ostr)const {
    if (fileIO()) {
      csvWrite(ostr);
    }
    else {
      ostr << "COVID TEST" << endl;
      Patient::write(ostr) << endl;
    }
    return ostr;
  }
  istream& CovidPatient::read(istream& istr) {
    if (fileIO()) {
      csvRead(istr);
    }
    else {
      Patient::read(istr);
    }
    return istr;
  }
}