/*
Final Project Milestone 4
Name : Yujin Won
Email: ywon9@myseneca.ca
Student ID: 153565197
Date: 2020/11/23

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "TriagePatient.h"
using namespace std;
namespace sdds
{
  int nextTriageTicket = 1;

  TriagePatient::TriagePatient() : Patient(nextTriageTicket) {
    symptoms = nullptr;
    nextTriageTicket++;
  }
  TriagePatient::~TriagePatient() {
    delete[] symptoms;
  }
  char TriagePatient::type()const {
    return 'T';
  }
  ostream& TriagePatient::csvWrite(ostream& ostr)const {
    Patient::csvWrite(ostr);
    ostr << ',' << symptoms;
    return ostr;
  }
  istream& TriagePatient::csvRead(istream& istr) {
    char string[511];

    delete[] symptoms;
    Patient::csvRead(istr);
    istr.ignore(1000, ',');
    istr.get(string, 511, '\n');
    symptoms = new char[strlen(string) + 1];
    strcpy(symptoms, string);
    nextTriageTicket = number() + 1;

    return istr;
  }
  ostream& TriagePatient::write(ostream& ostr)const {
    if (fileIO()) {
      csvWrite(ostr);
    }
    else {
      ostr << "TRIAGE" << endl;
      Patient::write(ostr) << endl;
      ostr << "Symptoms: " << symptoms << endl;
    }
    return ostr;
  }
  istream& TriagePatient::read(istream& istr) {
    char string[511];

    if (fileIO()) {
      csvRead(istr);
    }
    else {
      delete[] symptoms;
      Patient::read(istr);
      cout << "Symptoms: ";
      istr.get(string, 511, '\n');
      symptoms = new char[strlen(string) + 1];
      strcpy(symptoms, string);
      istr.ignore(1000, '\n');
    }
    return istr;
  }
}