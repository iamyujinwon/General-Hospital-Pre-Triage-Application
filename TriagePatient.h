/*
Final Project Milestone 4
Name : Yujin Won
Email: ywon9@myseneca.ca
Student ID: 153565197
Date: 2020/11/23

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_TRIAGE_H
#define SDDS_TIRAGE_H
#include <iostream>
#include "Patient.h"
namespace sdds
{
  class TriagePatient : public Patient
  {
    char* symptoms;
  public:
    TriagePatient();
    ~TriagePatient();
    char type()const;
    std::ostream& csvWrite(std::ostream& ostr)const;
    std::istream& csvRead(std::istream& istr);
    std::ostream& write(std::ostream& ostr)const;
    std::istream& read(std::istream& istr);
  };
}
#endif // !SDDS_


